#include "PlayScene.h"
#include <iostream>
#include <fstream>
#include "SampleKeyEventHandler.h"
#include "Debug.h"
#include "Utils.h"
#include "AssetID.h"
#include "GameObject.h"
#include "Playablechracter.h"
#include "Blackfoot.h"
#include "Sunami.h"
#include "Eyelet.h"
#include "Bellbomber.h"
#include  "SmallJason.h"
#include "Ground.h"
#include "HealUp.h"
using namespace std;
PlayScene::PlayScene(int id, LPCWSTR filePath) :Scene(id, filePath)
{
	player = NULL;
	key_handler = new SampleKeyEventHandler(this);
	quadtree = NULL;
}
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_QUADTREE	3
#define SCENE_SECTION_BACKGROUND 4
#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024
void PlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = Textures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	Sprites::GetInstance()->Add(ID, l, t, r, b, tex);
}
void PlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}
void PlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new Animation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}
	DebugOut(L"Animation Loaded %d\n", ani_id);
	Animations::GetInstance()->Add(ani_id, ani);
}
void PlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	Gameobject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_JASON:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] JASON object was created before!\n");
			return;
		}

		obj = new Playablechracter(x, y);
		player = (Playablechracter*)obj;
		//if (player->states->mPlayerstate == nullptr)
			//player->states->mPlayerstate = new JasonBigIdle(player->states);


		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_SMALLJASON:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] JASON object was created before!\n");
			return;
		}

		obj = new SmallJason(x, y);
		player = (SmallJason*)obj;
		//if (player->states->mPlayerstate == nullptr)
			//player->states->mPlayerstate = new JasonBigIdle(player->states);


		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_BLACKFOOT: obj = new Blackfoot(x, y); break;
	case OBJECT_TYPE_SUNAMI: obj = new Sunami(x, y); break;
	case OBJECT_TYPE_EYELET: obj = new Eyelet(x, y); break;
	case OBJECT_TYPE_HEALUP: obj = new HealUp(x, y); break;
	//case OBJECT_TYPE_BELLBOMBER: obj = new Bellbomber(x, y); break;
	case OBJECT_TYPE_GROUND: {
		int w = atoi(tokens[4].c_str());
		int h = atoi(tokens[5].c_str());
		obj = new Ground(x, y, w, h);
		//objects.push_back((Ground*)obj);
		//DebugOut(L"them gach");
		break;
	}
	//case OBJECT_TYPE_SMALLJASON : obj = new SmallJason(x, y); break;
		//case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
		//case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;

		//case OBJECT_TYPE_PLATFORM:
		//{

			/*float cell_width = (float)atof(tokens[3].c_str());
			float cell_height = (float)atof(tokens[4].c_str());
			int length = atoi(tokens[5].c_str());
			int sprite_begin = atoi(tokens[6].c_str());
			int sprite_middle = atoi(tokens[7].c_str());
			int sprite_end = atoi(tokens[8].c_str());

			obj = new CPlatform(
				x, y,
				cell_width, cell_height, length,
				sprite_begin, sprite_middle, sprite_end
			);

			break;*/
			//}

			//case OBJECT_TYPE_PORTAL:
			//{
			//	float r = (float)atof(tokens[3].c_str());
			//	float b = (float)atof(tokens[4].c_str());
			//	int scene_id = atoi(tokens[5].c_str());
			//	obj = new CPortal(x, y, r, b, scene_id);
			//}
			//break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}
void PlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}
void PlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);
	if (isloaded == false)
	{
		ifstream f;
		f.open(sceneFilePath);

		// current resource section flag
		int section = SCENE_SECTION_UNKNOWN;

		char str[MAX_SCENE_LINE];
		while (f.getline(str, MAX_SCENE_LINE))
		{
			string line(str);
			DebugOut(L"[INFO] Parsing line: %s\n", ToWSTR(line).c_str());
			if (line[0] == '#') continue;	// skip comment lines	
			if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
			if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
			if (line == "[BACKGROUND]") {
				DebugOut(L"[INFO] BACKGROUND section detected\n");
				section = SCENE_SECTION_BACKGROUND;
				continue;
			}
			if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

			//
			// data section
			//
			switch (section)
			{
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_BACKGROUND:
				_ParseSectionBackGround(line);
				break;
			}
		}

		f.close();
		isloaded = true;
	}
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}
void PlayScene::Update(DWORD dt)
{
	// We know that Jason is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	if (quadtree != NULL)
	{
		quadtree->deletequadtree();
	}
	vector<LPGAMEOBJECT>Owithoutplayer;
	for (int i = 1; i < objects.size(); i++)
	{
		Owithoutplayer.push_back(objects[i]);
	}
	Quadtreenode* root = new Quadtreenode(0, x, y, width, height, Owithoutplayer);
	if (root == NULL)
	{
		DebugOut(L"root is null\n");
	}
	
	quadtree = new Quadtree(root);
	vector<LPGAMEOBJECT> Otorender = quadtree->traversal();
	vector<LPGAMEOBJECT>coObjects;
	for (size_t i = 0; i < Otorender.size(); i++)
	{
		if (Otorender[i] != NULL&&Otorender[i]->IsCollidable()==1)
		coObjects.push_back(Otorender[i]);
	}
	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->alwaysrender)
			Otorender.push_back(objects[i]);
	}
	this->player->Update(dt, &coObjects);
	for (size_t i = 0; i < Otorender.size(); i++)
	{
		Otorender[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Jason::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow jason
	float cx, cy;
	player->GetPosition(cx, cy);
	Game* game = Game::GetInstance();

	cx -=  game->GetBackBufferWidth()/2  ; //w 23 h 31
	cy += game->GetBackBufferHeight() /2  ;
	
	//if(cx < 0) cx = 0;
	//if (cy < 0) cy = 0;


	Game::GetInstance()->GetCamera()->SetCamPos(cx, cy);
	//if cx> bufferwidth()/2 -> cx=player->x-bufferwidth/2
	// -> xplayer luon = bufferwidth/2 -> luon render player tai vi tri co toa do la buffer width/2
	// -> xo-cx=xo-xp+bufferwidth/2 xhqc=xo-xp
	//if xo rat lon -> neu xp du lon thi xhequychieuplayer+bufferwidth/2 < bufferwidth()-> he quy chieu dong theo player.
	//neu xo du nho-> tuong tu (>0)
	PurgeDeletedObjects();
}
void PlayScene::Render()
{
	vector<LPGAMEOBJECT> Otorender = quadtree->traversal();
	if(background!=NULL)
		background->Draw(0, 0);
	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->alwaysrender)
			Otorender.push_back(objects[i]);
	}
	player->render();
	for (int i = 0; i < Otorender.size(); i++)
	{
		Otorender[i]->render();
	}
}
void PlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}
void PlayScene::Unload()
{
	if (isloaded == true)
	{
		for (int i = 0; i < objects.size(); i++)
			delete objects[i];

		objects.clear();
		player = NULL;
	}
	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool PlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }
void PlayScene::_ParseSectionBackGround(string line)
{
	vector<string> tokens = split(line);
	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int b = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int t = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());
	DebugOut(L"enter back ground %d,%d,%d,%d,%d,%d \n", ID, l, t, r, b, texID);
	width = r - l;
	height = t - b;
	DebugOut(L"PLayscencesize:%f,%f\n", width, height);
	x = 0-width/2;
	y=0+height/2;
	LPTEXTURE tex = Textures::GetInstance()->Get(30);
	background = new Sprite(ID, l, b, r, t, tex);
}
void PlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), PlayScene::IsGameObjectDeleted),
		objects.end());
}

void PlayScene::AddObject(Gameobject* obj) {
	objects.push_back(obj);
}

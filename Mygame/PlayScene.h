#pragma once
#include "Game.h"
#include "Scene.h"
#include "Playerdata.h"
#include "Gameobject.h"
#include "Textures.h"
#include "unordered_map"
#include "Quadtree.h"
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024
class PlayScene : public Scene
{
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;
	Quadtree* quadtree;
	std::unordered_map<int, bool> keyboardstate;
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_QUADTREE(string line);
	void LoadAssets(LPCWSTR assetFile);

public:
	PlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};
typedef PlayScene* LPPLAYSCENE;

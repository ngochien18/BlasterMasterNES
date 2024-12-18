#include "HUD.h"

void HUD::Update(DWORD dt, vector<Gameobject*>* coObjects)
{

	SetState(this->state);
	Game::GetInstance()->GetCamera()->GetCamPos(x, y);
	x += 20;
	y -= 150;
	Gameobject::Update(dt, coObjects);
	//Colision::GetInstance()->process(this, dt, coObjects);
}

void HUD::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - JASON_BIG_BBOX_WIDTH / 2;
	top = y + JASON_BIG_BBOX_HEIGHT / 2;
	right = left + JASON_BIG_BBOX_WIDTH;
	bottom = top - JASON_BIG_BBOX_HEIGHT;
}
void HUD::render() {

	int aniID = HUD_ANI_100;

	switch (player->GetHealth())
	{
	case 100:
		aniID = HUD_ANI_100;
		break;
	case 90:
		aniID = HUD_ANI_90;
		break;

	case 80:
		aniID = HUD_ANI_80;
		break;

	case 70:
		aniID = HUD_ANI_70;
		break;

	case 60:
		aniID = HUD_ANI_60;
		break;

	case 50:
		aniID = HUD_ANI_50;
		break;

	case 40:
		aniID = HUD_ANI_40;
		break;

	case 30:
		aniID = HUD_ANI_30;
		break;

	case 20:
		aniID = HUD_ANI_20;
		break;

	case 10:
		aniID = HUD_ANI_10;
		break;

	default:
		break;
	}

	Animations::GetInstance()->Get(aniID)->Render(x, y);
}

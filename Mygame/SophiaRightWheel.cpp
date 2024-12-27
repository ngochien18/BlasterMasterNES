#include "SophiaRightWheel.h"

SophiaRightWheel::SophiaRightWheel(Sophia* sophia)
{
	this->base = sophia;

}
SophiaRightWheel::~SophiaRightWheel() {}

void SophiaRightWheel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = base->GetDirection();
	Gameobject::Update(dt, coObjects);
}

void SophiaRightWheel::render() {
	int aniID = SOPHIA_ANI_LEFT_WALK;
	float transX = 7.0, transY = 0;

	if (base->GetState() == SOPHIA_STATE_IDLE) {
		aniID = SOPHIA_ANI_STANDING;
	}
	else if (base->GetState() == SOPHIA_STATE_WALKING_RIGHT) {
		aniID = SOPHIA_ANI_RIGHT_WALK;
	}
	else if (base->GetState() == SOPHIA_STATE_WALKING_LEFT) {
		aniID = SOPHIA_ANI_LEFT_WALK;
	}
	

	float WheelX, WheelY;
	base->GetPosition(WheelX, WheelY);

	WheelX += SOPHIA_BIG_BBOX_WIDTH / 2;
	WheelY -= SOPHIA_BIG_BBOX_HEIGHT / 2;

	Animations::GetInstance()->Get(aniID)->Render(WheelX + transX, WheelY + transY);
}

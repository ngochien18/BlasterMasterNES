#include "SophiaMiddle.h"

SophiaMiddle::SophiaMiddle(Sophia* sophia)
{
	this->base = sophia;

}

SophiaMiddle::~SophiaMiddle() {}

void SophiaMiddle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	nx = base->GetDirection();
	Gameobject::Update(dt, coObjects);
}

void SophiaMiddle::render() {
	int aniID = SOPHIA_ANI_MIDDLE;
	float transX = 0, transY = 0;

	if (base->GetState() == SOPHIA_STATE_DIE) {
		return;
	}
	else {

		transX = 0;
		transY = 0;
	}

	float MiddleX, MiddleY;
	base->GetPosition(MiddleX, MiddleY);

	MiddleX += SOPHIA_BIG_BBOX_WIDTH / 2;
	MiddleY -= SOPHIA_BIG_BBOX_HEIGHT / 2;

	Animations::GetInstance()->Get(aniID)->Render(MiddleX + transX, MiddleY + transY);
}

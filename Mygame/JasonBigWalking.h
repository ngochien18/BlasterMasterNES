#pragma once
#include "PlayerState.h"
#define JASON_ACCEL_WALK 0.0005f
#define JASON_WALKING_SPEED 0.1f

// Animation IDs
#define ID_ANI_JASON_WALKING_RIGHT 500
#define ID_ANI_JASON_WALKING_LEFT 501
#define ID_ANI_JASON_WALKING_DOWN 600
#define ID_ANI_JASON_WALKING_UP 601

class PlayerData;

class JasonBigWalking : public PlayerState
{
public:
    JasonBigWalking(Player* data);
    ~JasonBigWalking();

    void HandleKeyBoard(int Keycode) override;
    StateName GetState() override;
};



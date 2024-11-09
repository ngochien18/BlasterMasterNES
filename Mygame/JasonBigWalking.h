#pragma once
#include "Game.h"
#include "PlayerState.h"
#include "Playerdata.h"
#include "Windows.h"
#define JASON_ACCEL_WALK	0.0005f
#define JASON_WALKING_SPEED		0.1f
#pragma region WALKING_ANIMATION_ID
#define ID_ANI_JASON_WALKING_RIGHT 500
#define ID_ANI_JASON_WALKING_LEFT 501

#define ID_ANI_JASON_WALKING_DOWN 600
#define ID_ANI_JASON_WALKING_UP 601
class Playerdata;
class JasonBigWalking :
    public PlayerState
{
public:

    JasonBigWalking(Player* data):PlayerState(data)
    {
        if (data->mPlayerdata != nullptr) {
            data->mPlayerdata->SetMaxSpeed(JASON_WALKING_SPEED);
            data->mPlayerdata->SetAccel(JASON_ACCEL_WALK);
        }
    }
    ~JasonBigWalking();
    StateName GetState()
    {
        StateName name = StateName::BigWalking;
        return name;
    }
    void HandleKeyBoard(int Keycode)
    {
        if (Keycode == DIK_W)
        {
            this->data->mPlayerdata->SetDirect(0, -1);
            this->data->mPlayerdata->SetId(ID_ANI_JASON_WALKING_DOWN);
        }
        else if (Keycode == DIK_S)
        {
            this->data->mPlayerdata->SetDirect(0, 1);
            this->data->mPlayerdata->SetId(ID_ANI_JASON_WALKING_UP);
        }
        else if (Keycode == DIK_A)
        {

            this->data->mPlayerdata->SetDirect(-1, 0);
            this->data->mPlayerdata->SetId(ID_ANI_JASON_WALKING_LEFT);
        }
        else if (Keycode == DIK_D)
        {
            this->data->mPlayerdata->SetDirect(1, 0);
            this->data->mPlayerdata->SetId(ID_ANI_JASON_WALKING_RIGHT);
        }
        else
        {

        }
    }
};


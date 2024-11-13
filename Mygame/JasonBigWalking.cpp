#include "JasonBigWalking.h"
#include "JasonBigIdle.h"
#include "Player.h"
#include "PlayerData.h"

JasonBigWalking::JasonBigWalking(Player* data) : PlayerState(data)
{
    if (data->mPlayerdata != nullptr) {
        data->mPlayerdata->SetMaxSpeed(JASON_WALKING_SPEED);
        data->mPlayerdata->SetAccel(JASON_ACCEL_WALK);
    }
}

JasonBigWalking::~JasonBigWalking()
{
    // Optional cleanup, if needed (but PlayerState should handle cleanup)
}

StateName JasonBigWalking::GetState()
{
    return StateName::BigWalking;  // Return the correct state
}

void JasonBigWalking::HandleKeyBoard(int Keycode)
{
    if (data->mPlayerdata == nullptr)
    {
        DebugOut(L"Nullptr \n");
    }
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
        // Transition to Idle state if no keys are pressed
        JasonBigIdle* idle = new JasonBigIdle(this->data);
        this->data->mPlayerdata->setstate(idle);
    }
}
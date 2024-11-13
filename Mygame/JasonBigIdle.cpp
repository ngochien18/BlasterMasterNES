#include "JasonBigIdle.h"
#include "JasonBigWalking.h"
#include "Player.h"
#include "PlayerData.h"

JasonBigIdle::JasonBigIdle(Player* data) : PlayerState(data)
{
    if (data->mPlayerdata != nullptr) {
        data->mPlayerdata->SetMaxSpeed(0);  // Set speed to 0 when idle
        data->mPlayerdata->SetAccel(0);  // Set acceleration to 0 when idle
        data->mPlayerdata->SetSpeed(0, 0);
    }
}

JasonBigIdle::~JasonBigIdle()
{
    // Optional cleanup, if needed
}

StateName JasonBigIdle::GetState()
{
    return StateName::BigIdle;  // Correct state return
}

void JasonBigIdle::HandleKeyBoard(int Keycode)
{
    // Check if any movement keys are pressed
    if (Keycode == DIK_W || Keycode == DIK_S || Keycode == DIK_A || Keycode == DIK_D)
    {
        // Transition to walking state when any movement key is pressed
        this->data->mPlayerdata->setstate(new JasonBigWalking(this->data));
    }
    else
    {
        // Set idle animation based on the direction the player was last facing
        float nx, ny;
        data->mPlayerdata->GetDirect(nx, ny);

        if (nx > 0)
        {
            data->mPlayerdata->SetId(ID_ANI_JASON_IDLE_RIGHT);
        }
        else if (nx < 0)
        {
            data->mPlayerdata->SetId(ID_ANI_JASON_IDLE_LEFT);
        }
        else if (ny > 0)
        {
            data->mPlayerdata->SetId(ID_ANI_JASON_IDLE_DOWN);
        }
        else if (ny < 0)
        {
            data->mPlayerdata->SetId(ID_ANI_JASON_IDLE_UP);
        }
    }
}
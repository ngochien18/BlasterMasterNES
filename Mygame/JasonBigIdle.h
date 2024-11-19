#pragma once
#include "PlayerState.h"

// Animation IDs
#define ID_ANI_JASON_IDLE_RIGHT 400
#define ID_ANI_JASON_IDLE_LEFT 401
#define ID_ANI_JASON_IDLE_UP 402
#define ID_ANI_JASON_IDLE_DOWN 403

class PlayerData;
class JasonBigWalking;

class JasonBigIdle : public PlayerState
{
public:
    JasonBigIdle(Player* data);  // Constructor
    ~JasonBigIdle();  // Destructor
    void HandleKeyBoard(int Keycode) override;  // Corrected method name
    StateName GetState() override;  // Corrected return value
};

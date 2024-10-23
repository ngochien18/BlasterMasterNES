#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Jason.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CJason* jason = (CJason*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		jason->SetState(JASON_STATE_SIT);
		break;
	case DIK_S:
		jason->SetState(JASON_STATE_JUMP);
		break;
	case DIK_1:
		jason->SetLevel(JASON_LEVEL_SMALL);
		break;
	case DIK_2:
		jason->SetLevel(JASON_LEVEL_BIG);
		break;
	case DIK_0:
		jason->SetState(JASON_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CJason* jason = (CJason*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		jason->SetState(JASON_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		jason->SetState(JASON_STATE_SIT_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CJason* jason = (CJason*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
			jason->SetState(JASON_STATE_RUNNING_RIGHT);
		else
			jason->SetState(JASON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
			jason->SetState(JASON_STATE_RUNNING_LEFT);
		else
			jason->SetState(JASON_STATE_WALKING_LEFT);
	}
	else
		jason->SetState(JASON_STATE_IDLE);
}
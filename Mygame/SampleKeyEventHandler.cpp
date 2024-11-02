#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Playablechracter.h"
#include "PlayScene.h"
void SampleKeyEventHandler::OnKeyDown(int KeyCode)
{
	Playablechracter* jason = (Playablechracter *)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	if (jason == nullptr) {
		DebugOut(L"[ERROR] Player object not found!\n");
		return;
	}
	DebugOut(L"KeyCode received: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_W:
		jason->SetState(JASON_STATE_WALK_UP);
		break;
	case DIK_S:
		jason->SetState(JASON_STATE_WALK_DOWN);
		break;
	case DIK_D:
		jason->SetState(JASON_STATE_WALK_RIGHT);
		break;
	case DIK_A:
		jason->SetState(JASON_STATE_WALK_LEFT);
		break;
	default:
		DebugOut(L"No key called\n");
	}
}
void SampleKeyEventHandler::KeyState(BYTE* states)
{
	LPGAME game = game->GetInstance();
	Playablechracter* jason = (Playablechracter*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	if (game->IsKeyDown(DIK_S))
	{
		if (game->IsKeyDown(DIK_RSHIFT))
		{
			jason->SetState(JASON_STATE_DASHING);
		}
	}
	else if (game->IsKeyDown(DIK_A))
	{

	}
	else if (game->IsKeyDown(DIK_D))
	{

	}
	else if (game->IsKeyDown(DIK_W))
	{

	}
	else
	{
		jason->SetState(JASON_STATE_IDLE);
	}
}
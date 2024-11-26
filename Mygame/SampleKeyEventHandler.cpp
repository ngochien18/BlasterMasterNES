#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Playablechracter.h"
#include "PlayScene.h"
#include "SmallJason.h"
void SampleKeyEventHandler::OnKeyDown(int KeyCode)
{
	Playablechracter* jason = (Playablechracter*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	if (jason== nullptr) {
		DebugOut(L"[ERROR] Player object not found!\n");
		return;
	}
	
	jason->OnkeyDown(KeyCode);
}
void SampleKeyEventHandler::KeyState(BYTE* state)
{
	Playablechracter* jason = (Playablechracter*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	LPGAME game = game->GetInstance();
	float x, y;
	jason->GetPosition(x, y);
	if (game->IsKeyDown(DIK_1))
	{
		((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->Setplayerstate(new SmallJason(x, y));
	}
	jason->Keystate(state);
}
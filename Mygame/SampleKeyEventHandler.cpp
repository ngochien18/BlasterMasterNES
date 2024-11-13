#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Playablechracter.h"
#include "PlayScene.h"
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
	jason->Keystate(state);
}
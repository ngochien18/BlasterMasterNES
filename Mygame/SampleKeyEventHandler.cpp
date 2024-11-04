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
	jason->OnkeyUP(KeyCode);
}
void SampleKeyEventHandler::KeyState(BYTE* states)
{
	
	Playablechracter* jason = (Playablechracter*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	jason->Keystate(states);
}
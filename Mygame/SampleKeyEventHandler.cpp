#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Playablechracter.h"
#include "PlayScene.h"
#include "Playerdata.h"
#include "PlayerState.h"
#include "Player.h"
#include "JasonBigWalking.h"
void SampleKeyEventHandler::OnKeyDown(int KeyCode)
{
	Playerdata* jason = (Playerdata*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	if (jason== nullptr) {
		DebugOut(L"[ERROR] Player object not found!\n");
		return;
	}
	if (jason->states->mPlayerstate == nullptr)
		jason->states->mPlayerstate = new JasonBigWalking(jason->states);
	jason->states->mPlayerstate->HandleKeyBoard(KeyCode);
}
void SampleKeyEventHandler::KeyState(BYTE* states)
{
	
	Playablechracter* jason = (Playablechracter*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	jason->Keystate(states);
}
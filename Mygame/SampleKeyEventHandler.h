#pragma once
#include "Scene.h"
using namespace std;
class SampleKeyEventHandler : public SceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states) override;
	virtual void OnKeyDown(int KeyCode) override;
	SampleKeyEventHandler(LPSCENE s) :SceneKeyHandler(s) {};
};



#pragma once
#include <Windows.h>
class KeyEventHandler
{
public:
	virtual void KeyState(BYTE* states)=0;
	virtual void OnKeyDown(int KeyCode)=0;
};
typedef KeyEventHandler* LPKEYEVENTHANDLER;

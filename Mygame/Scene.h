#pragma once
#include "KeyEventHandler.h"

class Scene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	Scene(int id, LPCWSTR filePath)
	{
		this->id = id;
		this->sceneFilePath = filePath;
		this->key_handler = NULL;
	}

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef Scene* LPSCENE;


class SceneKeyHandler : public KeyEventHandler
{
protected:
	Scene* scence;

public:
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void KeyState(BYTE* state) = 0;
	SceneKeyHandler(LPSCENE s) :KeyEventHandler() { scence = s; }
};

typedef SceneKeyHandler* LPSCENEKEYHANDLER;


#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <unordered_map>
#include <string>
#include "Debug.h"
#include <dinput.h>
#include "Camera.h"
#include "Texture.h"
#include "KeyEventHandler.h"
#include "Scene.h"
#define DIRECTINPUT_VERSION 0x0800
#define MAX_FRAME_RATE 100
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256
using namespace std;
class Camera;
class Game
{
	static Game* __instance;
	HWND hwnd;
	int BackBufferWidth = 0;
	int BackBufferHeight = 0;
	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10SamplerState* pPointSamplerState = NULL;
	LPD3DX10SPRITE spriteObject;
	ID3D10BlendState* pBlendStateAlpha;
	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 
	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	LPKEYEVENTHANDLER keyHandler;
	Camera* camera;
	HINSTANCE hInstance;
	unordered_map<int, LPSCENE> scenes;
	int current_scene;
	int next_scene = -1;
	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);
public:
	
	void InitDX(HWND hWnd, HINSTANCE hInstance);
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0);
	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b, float alpha = 1.0f, int sprite_width = 0, int sprite_height = 0)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect, alpha, sprite_width, sprite_height);
	}
	LPTEXTURE LoadTexture(LPCWSTR texturePath);
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) {
		keyHandler = handler;
		DebugOut(L"[INFO] Key handler set: %s\n", handler ? L"Valid" : L"NULL");
	}
	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; };
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; };
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; };

	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; };

	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };
	int GetBackBufferWidth() { return BackBufferWidth; }
	int GetBackBufferHeight() { return BackBufferHeight; }

	static Game* GetInstance();
	Camera* GetCamera()
	{
		return camera;
	};
	void SetPointSamplerState();
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void Load(LPCWSTR gameFile);
	void SwitchScene();
	void InitiateSwitchScene(int scene_id);

	void _ParseSection_TEXTURES(string line);
	~Game();
};
typedef Game* LPGAME;


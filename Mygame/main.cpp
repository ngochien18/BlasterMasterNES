//all lib
#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <comdef.h>
#include"Debug.h"
#include "Game.h"
#define GAME_Icon_PATH L"Blaster_master_icon.ico"
#define BACKGROUND_COLOR D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f)
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define MAX_FRAME_RATE 100
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
HWND InitWindow(HINSTANCE hInstance, int ncmdshow, int SCREENWIDTH, int SCREENHEIGHT)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, GAME_Icon_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"GAME";
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindow(
		L"GAME", L"Blaster Master",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREENWIDTH, SCREENHEIGHT,
		NULL, NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
	{
		OutputDebugString(L"[ERROR] CREATE WINDOW FAILED");
		DWORD Errcode = GetLastError();
		return FALSE;
	}
	ShowWindow(hwnd, ncmdshow);
	UpdateWindow(hwnd);
	return hwnd;
}

void Update(DWORD dt)
{
	Game::GetInstance()->GetCurrentScene()->Update(dt);
}

void Render()
{
	Game* g = Game::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	Game::GetInstance()->GetCurrentScene()->Render();

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}
int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = (DWORD)(now - frameStart);

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			Game::GetInstance()->ProcessKeyboard();
			Update(dt);
			Render();

			Game::GetInstance()->SwitchScene();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE prevhInstance,
	_In_ LPSTR cmdline,
	_In_ int cmdshow
)
{
	HWND hWnd = InitWindow(hInstance, cmdshow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	LPGAME game = Game::GetInstance();
	if (hInstance != NULL)
	{
		game->InitDX(hWnd, hInstance);
		game->InitKeyboard();
	}

	//IMPORTANT: this is the only place where a hardcoded file name is allowed ! 
	game->Load(L"Blastermaster.txt");

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	if (hInstance != NULL)
	{
		Run();
	}
	return 0;
}
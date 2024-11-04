#include "Textures.h"
#include <Windows.h>

#include "textures.h"
#include "Game.h"
#include "Debug.h"
Textures* Textures::__instance = NULL;

Textures::Textures()
{

}

Textures* Textures::GetInstance()
{
	if (__instance == NULL) __instance = new Textures();
	return __instance;
}

void Textures::Add(int id, LPCWSTR filePath)
{
	textures[id] = Game::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE Textures::Get(unsigned int i)
{
	LPTEXTURE t = textures[i];
	if (t == NULL)
		DebugOut(L"[ERROR] Texture Id %d not found !\n", i);

	return t;
}

/*
	Clear all loaded textures
*/
void Textures::Clear()
{
	for (auto x : textures)
	{
		LPTEXTURE tex = x.second;
		if (tex != NULL) delete tex;
	}

	textures.clear();
}
#pragma once
#include "Animation.h"
#include "Sprite.h"
class Animations
{
	static Animations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();

	static Animations* GetInstance();
};


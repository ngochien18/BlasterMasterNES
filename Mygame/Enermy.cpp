#include "Enermy.h"

float Enermy::distancewithplayer()
{
	Playerlevel* jason = (Playerlevel*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	float px, py;
	jason->GetPosition(px, py);
	float distance2 = (px - x) * (px - x) + (py - y) * (py - y);
	float distance = sqrtf(distance2);
	return distance;
}
float Enermy::distancewithplayerx()
{
	Playerlevel* player = (Playerlevel*)((LPPLAYSCENE)Game::GetInstance()->GetCurrentScene())->GetPlayer();
	float px, py;
	player->GetPosition(px, py);
	float distance = px - x;
	//float distance = sqrtf(distance2);
	return distance;
}

void Enermy::TakeDamage(int dame) {
	if (dame == 0)
		return;

	if (dame < health)
	{
		health -= dame;
	}
	else
	{
		health = 0;
	}
}

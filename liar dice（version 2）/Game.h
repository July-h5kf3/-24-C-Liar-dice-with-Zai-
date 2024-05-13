#pragma once
#include"UI.h"
#include"Player.h"
#include"ZAI.h"
class Game
{
public:
	Game(Player* player, ZAI* zai, UI* ui);
	void play();
private:
	Player* player;
	ZAI* zai;
	UI* ui;
};


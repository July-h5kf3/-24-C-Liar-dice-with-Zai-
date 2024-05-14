#include "Game.h"

Game::Game(Player* player, ZAI* zai, UI* ui)
{
	this->player = player;
	this->zai = zai;
	this->ui = ui;

	player->init(ui);
	zai->init(ui, 1.0);
}

void Game::play()
{
	ui->Init();
	ui->startUI();
	while (1)
	{
		ui->updateWindow();
		ui->whose_turn = 0;
		player->go();
		ui->updateWindow();
		Sleep(300);
		ui->whose_turn = 1;
		zai->go_test_only();
		ui->updateWindow();
	}
}

#include "Player.h"
#include<stdio.h>

void Player::init(UI* ui)
{
	this->ui = ui;
}

void Player::go()
{	
	IMAGE warming;
	loadimage(&warming, "res/warming.png");
	while (1)
	{
		ui->updateWindow();
		ExMessage msg;
		if (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x >= 590 && msg.x <= 590 + 40 && msg.y >= 700 && msg.y <= 700 + 40)
				{
					ui->count = min(ui->count++, 10);
				}
				if (msg.x >= 960 && msg.x <= 960 + 40 && msg.y >= 700 && msg.y <= 700 + 40)
				{
					ui->value = min(ui->value++, 6);
				}
				if (msg.x >= 590 && msg.x <= 590 + 40 && msg.y >= 830 && msg.y <= 830 + 40)
				{
					ui->count = max(ui->count--, 0);
				}
				if (msg.x >= 960 && msg.x <= 960 + 40 && msg.y >= 830 && msg.y <= 830 + 40)
				{
					ui->value = max(ui->value--, 0);
				}
			}
			
		}
		if (msg.message == WM_LBUTTONDOWN && msg.x >= 275 && msg.y >= 700 && msg.x <= 375 && msg.y <= 800)//说明是Guess操作
		{
			if (ui->checkGuess(ui->count,ui->value))
			{
				printf("human player make a guess:count = %d value = %d\n", ui->count, ui->value);
				ui->MakeGuess(ui->count,ui->value - 1);
				ui->pla.count = ui->count;
				ui->pla.value = ui->value;
				break;
			}
		}
		else if (msg.message == WM_LBUTTONDOWN && msg.x >= 1175 && msg.x <= 1275 && msg.y >= 700 && msg.y <= 800)//说明是liar操作
		{
			ui->checkover();
			break;
		}
	}	
}

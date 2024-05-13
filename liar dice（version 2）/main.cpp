#include<iostream>
#include"Game.h"
int main()
{
	Player player;
	UI ui;
	ZAI zai;
	Game game(&player, &zai, &ui);
	game.play();
	system("pause");
}
/*UI ui;
ui.Init();
ui.startUI();
while (1)
{
	ui.updateWindow();
	ui.userClick();
}*/
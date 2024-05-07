#include "game.h"
#include<iostream>
#include<limits>

const std::string PLAY_AGAIN_YES = "yes";
const std::string WELCOME_MESSAGE = "welcome to liar's Dice!\n";
const std::string GOODBYE_MESSAGE = "Thank you for playing Liar's Dice!\n";
const std::string PLAY_AGAIN_PROMPT = "Do you want to play again?(yes/no)";

int main()
{
	std::string playAgain;
	std::cout << WELCOME_MESSAGE;
	Game game;
	do
	{
		game.Init();
		std::cout << PLAY_AGAIN_PROMPT;
		std::cin >> playAgain;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}while (playAgain == PLAY_AGAIN_YES);
	std::cout << GOODBYE_MESSAGE;
	return 0;
}
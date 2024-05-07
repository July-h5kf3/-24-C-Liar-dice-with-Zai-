#include "player.h"
#include "InputException.h"
#include<iostream>
#include<sstream>
#include<utility>
#include<limits>
player::player(int id):id(id),dice(5)
{
	RollDice();
}

void player::RollDice()
{
	for (auto& die : dice)
	{
		die.Roll();
	}
}

void player::DisplayDice()
{
	std::cout << "Player " << id << ",your dice are:" << std::endl;
	for (const auto& die : dice)
	{
		std::cout << die.GetFaceValue() << ' ';
	}
	std::cout << '\n';
}

std::pair<int, int> player::MakeGuess()
{
	std::pair<int, int>guess;
	while (1)
	{
		std::cout << "Enter your guess in format(quantity,face_value):";
		std::string input;
		std::getline(std::cin, input);
		std::istringstream iss(input);
		int quantity, face_value;
		char comma;
		if (iss >> quantity >> comma >> face_value && comma == ',')
		{
			guess = { quantity,face_value };
			break;
		}
		std::cerr << "Invalid input:" << input << std::endl;
		std::cerr << "Please try again" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return guess;
}

bool player::CallLiar()
{
	std::cout << "Do you want to call liar?(yes/no)";
	std::string call_liar;
	std::getline(std::cin, call_liar);
	std::string judge = "yes";
	return judge == call_liar;
}

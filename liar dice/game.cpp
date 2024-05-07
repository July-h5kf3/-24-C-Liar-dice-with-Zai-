#include "game.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include"FileException.h"
#include<stdexcept>

const std::string INVALID_GUESS_MSG_GENERAL = "Invalid guess. You must either have more dice or a greater face value"
".\n";
const std::string INVALID_GUESS_MSG_FACE_VALUE = "Invalid guess. You have the same number of dice but the face value "
"is not greater.\n";
const std::string INVALID_GUESS_MSG_DICE_COUNT = "Invalid guess. You have fewer dice but the face value is not "
"greater than the last guess.\n";

Game::Game() : currentPlayIndex(0), lastGuess({0,0})
{
}

void Game::Init()
{
	try
	{
		rulesText = ReadRulesFromFile("./res/rules.txt");
		std::cout << rulesText;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Ensure 'res/rules.txt'exists in the same diretory as 'LiarsDice.exe'.";
		exit(EXIT_FAILURE);
	}
	SetupPlayer();
	PlayGame();
}

std::string Game::ReadRulesFromFile(const std::string& filename)
{
	std::string rulesContent;
	std::ifstream file_handle(filename);
	if (!file_handle)
	{
		throw FileException("Could not open rules.txt");
	}
	std::string line;
	while (std::getline(file_handle, line))
	{
		rulesContent += line + '\n';
	}
	return rulesContent;
}



void Game::SetupPlayer()
{
	std::cout << "Enter the number of players:";
	int num_players;
	GetSetupInput(num_players);
	while (num_players < 2)
	{
		std::cout << "Please enter a number greater than 1:";
		GetSetupInput(num_players);
	}
	players.reserve(num_players);
	for (int i = 1; i <= num_players; i++)
	{
		players.emplace_back(i);
	}
}

void Game::PlayGame()
{
	while (1)
	{
		system("cls");
		std::cout << rulesText;
		player& currentplayer = players[currentPlayIndex];
		displayCurrentState(currentplayer);
		auto guess = Guess(currentplayer.MakeGuess());
		std::string validationError = ValidateGuess(guess, lastGuess);
		if (!validationError.empty())
		{
			std::cout << validationError;
			continue;
		}
		lastGuess = guess;
		if (currentplayer.CallLiar())
		{
			std::string winner = CheckGuessAgainstDice(lastGuess);
			std::cout << "The winner is " << winner << "'\n";
			break;
		}
		updateCurrentPlayerIndex();
	}
}

std::string Game::ValidateGuess(const Guess& new_guess, const Guess& last_guess)
{
	std::stringstream errorMsg;
	if (last_guess.diceCount != 0 || last_guess.diceValue != 0)
	{
		errorMsg << "Last Guess was(" << last_guess.diceCount << "," << last_guess.diceValue << ")\n";
	}
	if (new_guess.diceCount < last_guess.diceCount && new_guess.diceValue <= last_guess.diceValue)
	{
		errorMsg << INVALID_GUESS_MSG_DICE_COUNT;
		return errorMsg.str();
	}
	if (new_guess.diceCount == last_guess.diceCount && new_guess.diceValue <= last_guess.diceValue) {
		errorMsg << INVALID_GUESS_MSG_FACE_VALUE;
		return errorMsg.str();
	}

	if (new_guess.diceCount <= last_guess.diceCount && new_guess.diceValue < last_guess.diceValue) {
		errorMsg << INVALID_GUESS_MSG_GENERAL;
		return errorMsg.str();
	}
	return "";
}

std::string Game::CheckGuessAgainstDice(const Guess& last_guess)
{
	int counter = 0;
	for (const auto& player : players)
	{
		for (const auto& die : player.GetDice())
		{
			if(die.GetFaceValue() == last_guess.diceValue)
			{
				++counter;
			}
		}
	}
	return (counter >= last_guess.diceCount) ? "Guessing Player" : "Calling Player";
}

void Game::updateCurrentPlayerIndex()
{
	++currentPlayIndex;
	if (currentPlayIndex >= players.size())
	{
		currentPlayIndex = 0;
	}
}

void Game::displayCurrentState(player& currentPlayer) const
{
	std::cout << "PLAYER " << currentPlayer.GetPlayerId() << "'s Turn:\n";
	if (lastGuess.diceCount != 0 || lastGuess.diceValue != 0)
	{
		std::cout << "Last Guess:" << lastGuess.diceCount << "," << lastGuess.diceValue << std::endl;
	}
	std::cout << "Your Dice:";
	currentPlayer.DisplayDice();
	std::cout << '\n';
}

void Game::GetSetupInput(int& num_players)
{
	std::cin >> num_players;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

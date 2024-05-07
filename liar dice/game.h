#pragma once
#include<vector>
#include<string>
#include<utility>
#include"player.h"

struct Guess
{
	int diceValue;
	int diceCount;

	explicit Guess(std::pair<int, int>guess_pair)
	{
		diceCount = guess_pair.first;
		diceValue = guess_pair.second;
	}
};

class Game
{
public:
	Game();
	void Init();
	std::string ReadRulesFromFile(const std::string& filename);
	void SetupPlayer();
	void PlayGame();
	std::string ValidateGuess(const Guess& new_guess, const Guess& last_guess);
	std::string CheckGuessAgainstDice(const Guess& last_guess);
private:
	std::vector<player>players;
	int currentPlayIndex;
	Guess lastGuess;
	std::string rulesText;
	void updateCurrentPlayerIndex();
	void displayCurrentState(player& currentPlayer) const;
	void GetSetupInput(int& num_players);
};
#pragma once

#include <vector>
#include "Dice.h"
class player
{
public:
	explicit player(int id);
	void RollDice();
	void DisplayDice();
	std::pair<int, int>MakeGuess();
	bool CallLiar();
	[[nodiscard]] const std::vector<Dice>& GetDice() const { return dice; }
	[[nodiscard]] int GetPlayerId() const { return id; };
private:
	int id;
	std::vector<Dice>dice;
};


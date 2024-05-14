#pragma once
#include<random>
class Dice
{
public:
	Dice();
	void Roll();
	[[nodiscard]] unsigned int GetFaceValue() const;
private:
	unsigned int face_value;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dis;
};


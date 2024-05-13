#pragma once
#include<graphics.h>
#include"tool.h"
#include<iostream>
#include<vector>
#include"Dice.h"
struct LassGuess
{
	int count, value;
};
class UI
{
public:
	IMAGE imgBg;
	IMAGE Dice_AI;
	IMAGE Dice_Type[7];
	IMAGE add_button;
	IMAGE del_button;
	IMAGE ROLL_key;
	IMAGE LIAR_key;
	IMAGE imgBegin;
	LOGFONT f;
	int count, value;
	LassGuess lassguess;
	LassGuess pla, aig;
	bool whose_turn;
	void Init();
	void updateWindow();
	void startUI();
	void userClick();
	void MakeGuess(int Count,int Value);
	void checkover();
	bool checkGuess(int Count,int Value);
	std::vector<int>dice_pla, dice_ai;
};


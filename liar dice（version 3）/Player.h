#pragma once
#include"UI.h"
#include<vector>
class Player
{
public:
	void init(UI* ui);	
	void go();
private:
	UI* ui;
};


#pragma once
#include"UI.h"
#include<vector>
#include<random>
class ZAI
{
public:
	void init(UI* ui,double conservativeness);
	void preprocess();
	void update_goodbid();
	void go();
	void go_test_only();

private:
	UI* ui;
	double conservativeness;
	double up_lim_factor;
	double aggressiveness;
	double stochastic;
	int intelligence;
	int dice[6];
	double std_0, std_1;
	double expected_dice[6];
	double bid_up_lim[6];
	std::vector<std::pair<int, int>>good_bid;
	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std::uniform_real_distribution<double> distr(0.0, 1.0);
};


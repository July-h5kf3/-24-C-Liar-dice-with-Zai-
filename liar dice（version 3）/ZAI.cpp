#include "ZAI.h"
#include<cmath>
double normal_cdf(double x, double mean = 0.0, double std_dev = 1.0)
{
	double const sqrt_2_pi = 2.5066282746310002;
	double const exp_factor = -0.5 * x * x / (std_dev * std_dev);
	double const cdf = 1.0 / (std_dev * sqrt_2_pi) * std::exp(exp_factor);
	return 0.5 * (1.0 + std::erf(x / (std_dev * std::sqrt(2.0))));
}
double transform(double x)
{
	if (x < 0)return 0;
	else if (x > 1)return 1;
	else return x;
}
void ZAI::init(UI* ui, double conservativeness)
{
	this->ui = ui;
	this->conservativeness = transform(conservativeness);
	this->up_lim_factor = 0.84 - 0.24 * this->conservativeness;
}
void ZAI::preprocess()
{
	//计算期望骰子点数
	// 可以证明当我们做决策时无需考虑前面的其他猜测也能达到相当高的正确率
	//当对手说出猜测[r,d]时我们采取如下策略（我们认为对方看我们的骰子分布是正常的）：
	//对方点数为r的骰子个数为d - 
	//点数为r的骰子我们认为对方有
	for (int i = 0; i < 5; i++)
		dice[ui->dice_ai[i]]++;
	expected_dice[0] = 1.0 * dice[0] + 5.0 / 6;
	for (int i = 1; i <= 5; i++)
	expected_dice[i] = dice[0] + 5.0 / 6 * 2;
	std_0 = sqrt(5.0 * 1 / 6 * 5 / 6);//计算点数为0的骰子个数的方差
	std_1 = sqrt(5.0 * 1 / 3 * 2 / 3);//计算其他点数的骰子个数的方差
	int maxx = 0;
	for (int i = 0; i < 6; i++)
	{
		bid_up_lim[i] = expected_dice[i] + (i == 0 ? std_0 : std_1) * up_lim_factor;//计算猜测上限
		maxx = max(maxx, (int)bid_up_lim[i]);
	}
	good_bid.push_back(std::pair<int, int>(1, 1));
	int num = 1;
	for (int i = num; i <= maxx; i++)
	{
		if (num % 2 == 0)
		{
			this->good_bid.push_back(std::pair<int,int>(0, num / 2));
			for (int j = 1; j < 6; j++)
			{
				if (bid_up_lim[j] >= num)this->good_bid.push_back(std::pair<int, int>(j, num));
			}
		}
		else
		{
			for (int j = 1; j < 6; j++)
			{
				if (bid_up_lim[j] >= num)this->good_bid.push_back(std::pair<int, int>(j, num));
			}
		}
	}
}

void ZAI::update_goodbid()
{
	std::vector<std::pair<int, int>>Rgood_bid;
	if (!good_bid.empty())
	{
		//舍去不合理的猜测
		for (const auto& x : good_bid)
		{
			if (ui->checkGuess(x.first,x.second))//
			{
				Rgood_bid.push_back(x);
			}
		}
	}
	good_bid.clear();
	good_bid = Rgood_bid;
}
struct Good_bid
{
	int count, value;
	double prob;
};
double threshold = 0.4;
double threshold2 = 0.1;
int C5_i[6] = { 1,5,10,10,5,1};
double caculate(double x,int type)
{
	double y = ceil(1.0 * x);
	if (y > 5)return 0.0;
	double pos = 0.0;
	if (type == 0)
	{
		for (int i = 0; i < y; i++)
			{
			pos += 1.0 * C5_i[i] * pow(1.0 / 6, 1.0 * i) * pow(5.0 / 6, 1.0 * (5 - i));
			}
		return 1.0 - pos;
	}
	else
	{
		for (int i = 0; i < y; i++)
		{
			pos += 1.0 * C5_i[i] * pow(1.0 / 3, 1.0 * i) * pow(2.0 / 3, 1.0 * (5 - i));
		}
		return 1.0 - pos;
	}
	
}
void ZAI::go()
{
	this->preprocess();
	if (this->good_bid.empty())
		ui->checkover();
	this->update_goodbid();
	std::vector<Good_bid>Bid;
	int sum = 0;
	for (int i = 0; i < 6; i++)
	{
		sum += dice[i] * (i + 1);
	}
	int neutral_position[6] = {sum / 6,sum / 3,sum / 3,sum / 3,sum / 3,sum / 3};
	double neutral_std = sqrt(2 * sum) / 3;
	double neutral_std_0 = sqrt(5 * sum) / 6;
	for (const auto& x : good_bid)
	{
		Good_bid X;
		double prob = 1.0;
		double s = 1.0 * (x.second - expected_dice[x.first] - 0.5) / (x.first == 0 ? std_0 : std_1);
		double S = 1.0 * (x.second + 0.5 - neutral_position[x.first]) / (x.first == 0 ? neutral_std_0 : neutral_std);
		X.count = x.second;
		X.value = x.first;
		prob = normal_cdf(s) * normal_cdf(S);
		X.prob = prob;
		Bid.push_back(X);
	}
	int COUNT = 0;
	int VALUE = 0;
	double max_prob = 0;
	for (const auto& x : Bid)
	{
		if (x.prob >= max_prob)
		{
			max_prob = x.prob;
			COUNT = x.count;
			VALUE = x.value;
		}
	}
	if (ui->checkGuess(COUNT, VALUE))
	{
		ui->MakeGuess(COUNT, VALUE);
		ui->aig.count = COUNT;
		ui->aig.value = VALUE;
	}
	else
	{
		ui->checkover();
	}
}

void ZAI::go_test_only()
{
	//先计算概率
	//printf("test prob = %lf", normal_cdf(1.0 - (5.0 / 6) / (25.0 / 36)));
	for (int i = 0; i < 5; i++)
		dice[ui->dice_ai[i]]++;
	double prob;
	for (int i = 0; i < 6; i++)
		printf("%d ", dice[i]);
	puts("");
	double chazhi = 1.0 * ui->lassguess.count - 1.0 * dice[ui->lassguess.value] - 1.0 * (ui->lassguess.value == 0 ? 0 : dice[0]);
	printf("COUNT = %d VALUE = %d chazhi = %lf", ui->lassguess.count, ui->lassguess.value, chazhi);
	if (ui->lassguess.value != 0)prob = caculate(chazhi,0);
	else prob = caculate(chazhi,1);
	printf("prob = %lf\n", prob);
	if (prob <= threshold2)ui->checkover();
	//枚举所有可能猜测
	std::vector<Good_bid>MaybeGuess;
	for(int COUNT = 2;COUNT <= 10;COUNT++)
		for (int VALUE = 0; VALUE < 6; VALUE++)
		{
			if (ui->checkGuess(COUNT, VALUE))
			{
				Good_bid x;
				x.count = COUNT;
				x.value = VALUE;
				x.prob = 0.0;
				MaybeGuess.push_back(x);
			}
		}
	//根据对方的猜测推测对方的结果分布
	double maybeDice[6];
	//若猜测的是1那么可以按照普通逻辑去认为
	if (ui->lassguess.value == 0)
	{
		if (ui->lassguess.count > dice[0])
		{
			maybeDice[0] = 1.0 * ui->lassguess.count - 1.0 * dice[0];
			for (int i = 1; i < 6; i++)maybeDice[i] = (5.0 - (ui->lassguess.count * 1.0 - dice[0] * 1.0)) / 5;
		}
		else
		{
			maybeDice[0] = ui->lassguess.count;
			for (int i = 1; i < 6; i++)maybeDice[i] = (5.0 - ui->lassguess.count) / 5;
		}
	}
	//若猜测不为1则要考虑点数为1的骰子的情况
	//依据概率最大的情况考虑我们认为点数为1的个数为1
	else
	{
		if (ui->lassguess.count > dice[ui->lassguess.value] + 1)
		{
			maybeDice[0] = 1;
			maybeDice[ui->lassguess.value] = 1.0 * ui->lassguess.count - 1.0 * dice[ui->lassguess.value] - 1.0;
			for (int i = 1; i < 6; i++)
			{
				if (i == ui->lassguess.value)continue;
				maybeDice[i] = (5.0 - 1.0 - (1.0 * ui->lassguess.count - 1.0 * dice[ui->lassguess.value] - 1.0)) / 4.0;
			}
		}
		else
		{
			maybeDice[0] = 1;
			maybeDice[ui->lassguess.value] = 1.0 * ui->lassguess.count - 1.0;
			for (int i = 1; i < 6; i++)
			{
				if (i == ui->lassguess.value)continue;
				maybeDice[i] = (5.0 - 1.0 * ui->lassguess.count) / 4.0;
			}
		}
	}
	for (int i = 0; i < 6; i++)
	{
		if (maybeDice[i] > 5)ui->checkover();
		printf("maybedice[%d] = %lf\n", i,maybeDice[i]);
	}
	double maxx = 0;
	int AI_COUNT = 0;
	int AI_VALUE = 0;
	for (const auto& x : MaybeGuess)
	{
		double s;
		double chazhi = 1.0 * x.count - maybeDice[x.value] - (x.value == 0 ? 0 : maybeDice[0]);
		if(x.value != 0)s = caculate(chazhi,1);
		else s = caculate(chazhi,0);
		printf("chazi = %lf\n",chazhi);
		printf("this is a guess: COUNT = %d VALUE = %d whose prob is :%lf\n", x.count, x.value, s);
		if (maxx < s && s >= threshold)
		{
			maxx = s;
			AI_COUNT = x.count;
			AI_VALUE = x.value;
		}
	}
	if (ui->checkGuess(AI_COUNT, AI_VALUE))
	{
		ui->aig.count = AI_COUNT;
		ui->aig.value = AI_VALUE + 1;
		ui->MakeGuess(AI_COUNT, AI_VALUE);
	}
	else ui->checkover();
}

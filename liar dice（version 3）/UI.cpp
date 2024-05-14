#include "UI.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include<random>
#define WIN_WEIGHT 1600
#define WIN_HEIGHT 900
void UI::Init()
{
	srand((unsigned int)time(NULL));
	dice_pla.clear();
	dice_ai.clear();
	for (int i = 1; i <= 5; i++)
	{
		int x = rand() % 6;
		dice_pla.push_back(x);
		int y = rand() % 6;
		dice_ai.push_back(y);
	}
	lassguess.count = 0;
	lassguess.value = 0;
	pla.count = 0;
	pla.value = 0;
	aig.count = 0;
	aig.value = 0;
	whose_turn = 0;
	HDC hdc;
	hdc = CreateCompatibleDC(NULL); 
	GetObject(GetCurrentObject(hdc, OBJ_FONT), sizeof(LOGFONT), &f);
	f.lfHeight = -400;
	f.lfWeight = FW_BOLD; 
	strcpy_s(f.lfFaceName, "Segoe UI Black");
	SelectObject(hdc, CreateFontIndirect(&f));
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255)); // 设置文本颜色为白色
	f.lfQuality = ANTIALIASED_QUALITY;
	loadimage(&imgBegin, "res/Begin.png");
	loadimage(&imgBg, "res/Board.png");
	loadimage(&Dice_AI, "res/dice_unknown.png");
	loadimage(&add_button, "res/add_button.png");
	loadimage(&del_button, "res/del_button.png");
	loadimage(&ROLL_key, "res/ROLL_key.png");
	loadimage(&LIAR_key, "res/LIAR_key.png");
	loadimage(&Dice_Type[0], "res/1.png");
	loadimage(&Dice_Type[1], "res/2.png");
	loadimage(&Dice_Type[2], "res/3.png");
	loadimage(&Dice_Type[3], "res/4.png");
	loadimage(&Dice_Type[4], "res/5.png");
	loadimage(&Dice_Type[5], "res/6.png");
	//for (int i = 0; i < 6; i++)
		//loadimage(&Dice_Type[i], "res/%d.png", i + 1);
	initgraph(WIN_WEIGHT, WIN_HEIGHT);

}

void UI::updateWindow()
{
	BeginBatchDraw();
	putimage(0, 0, &imgBg);
	putimagePNG(590, 700, &add_button);
	putimagePNG(960, 700, &add_button);
	putimagePNG(590, 830, &del_button);
	putimagePNG(960, 830, &del_button);
	putimagePNG(275, 700, &ROLL_key);
	putimagePNG(1175, 700, &LIAR_key);
	for (int i = 0; i < 5; i++)
		putimagePNG(325 + 200 * i, 450, &Dice_Type[dice_pla[i]]);
	char numText[8];
	char NumText[8];
	char plaCText[8];
	char plaVText[8];
	char aigCText[8];
	char aigVText[8];
	sprintf_s(numText, sizeof(numText), "%d", count);
	sprintf_s(NumText, sizeof(NumText), "%d",value);
	sprintf_s(plaCText, sizeof(plaCText), "%d", pla.count);
	sprintf_s(plaVText, sizeof(plaVText), "%d", pla.value);
	sprintf_s(aigCText, sizeof(aigCText), "%d", aig.count);
	sprintf_s(aigVText, sizeof(aigVText), "%d", aig.value);
	outtextxy(600, 780,numText);
	outtextxy(1000, 780, NumText);
	outtextxy(650, 90, plaCText);
	outtextxy(1100, 90, plaVText);
	outtextxy(620, 220, aigCText);
	outtextxy(1040, 220, aigVText);
	EndBatchDraw();
}

void UI::startUI()
{
		int flag = 0;
		while (1)
		{
			if (flag == 1) break;
			flag = 0;
			BeginBatchDraw();
			putimage(0, 0, &imgBegin);
			ExMessage msg;
			if(peekmessage(&msg))
			{
				if (msg.message == WM_LBUTTONDOWN)
				{
					// 检查点击是否在第一个按钮区域内
					if (msg.x >= 740 && msg.x <= 845 && msg.y >= 350 && msg.y <= 425)
					{
						printf("Fuck\n");
						flag = 1;
						break;
					}
					else if (msg.x >= 740 && msg.x <= 845 && msg.y >= 475 && msg.y <= 520)
					{
						flag = 2;
					}
				}
			}
			if (flag == 1)
			{
				EndBatchDraw();
				break;
			}
			if (flag == 2) 
			{
				IMAGE rule;
				loadimage(&rule, "res/rule.png");
				while (1) 
				{
					BeginBatchDraw();
					putimage(0, 0, &rule);
					EndBatchDraw();

					ExMessage MSG;
					if (peekmessage(&MSG))
					{
						if (MSG.message == WM_LBUTTONDOWN)
						{
							break;
						}
					}
				}
			}
			EndBatchDraw();
		}
}

void UI::userClick()
{
	ExMessage msg;
	if (peekmessage(&msg))
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= 590 && msg.x <= 590 + 40 && msg.y >= 700 && msg.y <= 700 + 40)
			{
				count = min(count++, 10);
			}
			if (msg.x >= 960 && msg.x <= 960 + 40 && msg.y >= 700 && msg.y <= 700 + 40)
			{
				value = min(value++, 6);
			}
			if (msg.x >= 590 && msg.x <= 590 + 40 && msg.y >= 830 && msg.y <= 830 + 40)
			{
				count = max(count--, 0);
			}
			if (msg.x >= 960 && msg.x <= 960 + 40 && msg.y >= 830 && msg.y <= 830 + 40)
			{
				value = max(value--, 0);
			}
		}
	}
}

void UI::MakeGuess(int Count,int Value)
{
	lassguess.count = Count;
	lassguess.value = Value;
}

void UI::checkover()
{
	for (int i = 0; i < 5; i++)
	{
		putimagePNG( 1220, i * 200, &Dice_Type[dice_ai[i]]);
	}
	printf("pla dice: %d %d %d %d %d", dice_pla[0], dice_pla[1], dice_pla[2], dice_pla[3], dice_pla[4]);
	printf("ai dice: %d %d %d %d %d", dice_ai[0], dice_ai[1], dice_ai[2], dice_ai[3], dice_ai[4]);
	int COUNT = 0;
	for (int i = 0; i < 5; i++)
	{
		printf("i = %d \n COUNT = %d", i,COUNT);
		if (dice_pla[i] == lassguess.value)COUNT++;
		if (dice_ai[i] == lassguess.value)COUNT++;
		if (lassguess.value != 0)
		{
			if(dice_pla[i] == 0)COUNT++;
			if (dice_ai[i] == 0)COUNT++;
		}
	}
	printf("whose turn = %d Count = %d lassguss = %d", whose_turn,COUNT,lassguess.count);
	if (whose_turn == 0 && COUNT <= lassguess.count)//如果是player叫的
		MessageBox(NULL, "YOU WIN。", "提示", MB_OK);
	else if (whose_turn == 0 && COUNT > lassguess.count)
		MessageBox(NULL, "YOU FAIL.", "提示", MB_OK);
	if (whose_turn == 1 && COUNT <= lassguess.count)
		MessageBox(NULL, "YOU FAIL.", "提示", MB_OK);
	else if (whose_turn == 1 && COUNT > lassguess.count)
		MessageBox(NULL, "YOU WIN.", "提示", MB_OK);
	exit(0);
}

bool UI::checkGuess(int Count,int Value)
{
	if ((Count > lassguess.count || Value > lassguess.value) && (Count >= 2))return 1;
	else return false;
}

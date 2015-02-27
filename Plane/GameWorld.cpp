#include "stdafx.h"
#include "GameWorld.h"
#include <conio.h>

GameWorld::GameWorld(void)
{
	print[0] = '\0';
	EnemyNum = 0;
	score = 0;
	gameover = false;
	hardness = 1;
	helpnum = 0;
	for(int i = 0;i < 3;i ++)
		help[i] = NULL;
	//time get
	tpre = GetTickCount();
	tnow = GetTickCount();
	tcreEnemy = GetTickCount();
	tHelp = GetTickCount();
	p = new Player(wide/2,height/2);
	
}

GameWorld::~GameWorld(void)
{
	DeleteObject(picture);
}

void GameWorld::OpenState(int state)
{
	p->OpenState(state);
}
void GameWorld::CloseState(int state)
{
	p->CloseState(state);
}

void GameWorld::start()
{
	setHard();
	tnow = GetTickCount();
	tpre = GetTickCount();
	SelectObject(bufdc , bg);
	BitBlt(mdc ,  0 , 0 ,1024 , 768 , bufdc , 0 , 0 , SRCCOPY);
	for(int i = 0;i < 3;i ++)
		if(help[i] != NULL)
			help[i]->update(p);
	eList.update(p);
	p->update(eList,score);

	if(p->hp <= 0)
	{
		p->survive = false;
		if(p->explosion < 0)
		{
			SetTextColor(mdc,RGB(255,0,0));
			TextOutA(mdc , 500,350,"GameOver",9);
			BitBlt(hdc , 0 , 0 , 1024,768,mdc , 0 , 0  ,SRCCOPY);
			Sleep(2000);
			p->hp = 20;
			p->explosion = 8;
			p->bombnum = 3;
			p->survive = true;
			p->BombState = 0;
			p->PlaneState = 0;
			score = 0;
			p->x = wide/2;
			p->y = 3*height/4;
		}
	}
	sprintf(print,"Player: HP:  %d , Bomb:  %d, Score:  %d, Level:  %d" ,\
		p->hp , p->bombnum,score,hardness); 
	SetTextColor(mdc,RGB(255,0,0));
	TextOutA(mdc , 0 , 0 ,print,strlen(print));
	BitBlt(hdc , 0 , 0 , 1024,768 , mdc , 0 , 0 ,SRCCOPY);
}

void GameWorld::update()//更新
{
	tnow = GetTickCount();
	if(tnow - tcreEnemy >= 5000)
	{
		CreateEnemy();
		tcreEnemy = GetTickCount();
	}
	if(tnow - tHelp >= 10000)
	{
		for(int i = 0;i < 3;i ++)
		{	
			if(help[i] != NULL)
			{
				delete help[i];
				help[helpnum] = NULL;
			}
			help[i] = new Helper;
		}
		tHelp = GetTickCount();
	}
	if(tnow - tpre >= 16)
	{
		start();
	}
}

//bool GameWorld::checkOutOfBoundary(int x, int y)//
//{
//	if(x<0||y<0||x>=cs.hScreenSize||y>=cs.vScreenSize)
//		return true;
//	else
//		return false;
//}

void GameWorld::CreateEnemy()//增加敌机
{
	int num = rand()%3+hardness;//获得增加的敌机数
	for(int i = 0; i < num; i ++)//增加敌机
	{
		eList.Create();
	}
}

void GameWorld::Bomb()//炸弹
{
	if(p->bombnum >0)
	{
		p->bombnum --;
		eList.Clear();
	}
}
void GameWorld::setHard()
{
	if(score < 1000)
	{
		hardness = 1;
	}
	else if(score < 3000)
	{
		hardness = 2;
	}
	else if(score < 5000)
	{
		hardness = 3;
	}
	else if(score < 8000)
	{
		hardness = 4;
	}
	else if(score < 10000)
	{
		hardness = 5;
	}
	else if(score < 15000)
	{
		hardness = 6;
	}
	else if(score < 20000)
	{
		hardness = 7;
	}
	else
		hardness = 8;
}
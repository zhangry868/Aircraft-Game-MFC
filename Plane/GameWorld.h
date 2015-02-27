
#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Helper.h"
#include "EnemyList.h"
#include<iostream>
#include <cstdio>
#include<windows.h>
#include "Player.h"
#include "CommonDefinitions.h"

using namespace std;


class GameWorld
{	//time control
	char print[100];
	DWORD tpre,tnow,tcreEnemy,tHelp;
	//picture
	bool gameover;
	//cs controls the content displayed in the screen.
	Helper* help[3];
	//p represents the player in the game
	Player* p;
	EnemyList eList;
	int score;
	int EnemyNum;
	int hardness;
	int helpnum;
	//Ë½ÓÐº¯Êý
	void setHard();
public:
	GameWorld(void);
	~GameWorld(void);

	//check the keyboard input to control the program 
	//void checkKeyBoardInput(Control dir);
	void OpenState(int state);
	void CloseState(int state);
	void Bomb();
	//start the game
	void start();
	void CreateEnemy();
	//update everything in the game, including the player and the screen
	void update();
//	void shot(){p->shot();}
	//check whether the given position is out of the screen
	//bool checkOutOfBoundary(int x, int y);
	friend EnemyList;
};



#endif
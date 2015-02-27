#pragma once

#include "Helper.h"
#include "EnemyList.h"
#include "CommonDefinitions.h"
#include "Bullet.h"

class EnemyTriB;
class TriBullet;
class Boss;
class BossLaser;

class Player
{
	int state[5];
	int BombState;
	int PlaneState;
	int hp;
	//position of the player
	DWORD tshot,tshotpre;
	int x,y,size;
	bool survive;
	Bullet *b[BulletMax];
	int bulletnum;
	int bombnum;
	int explosion;
public: 
	Player(int sx, int sy);
	~Player(void);
	Player(const Player& p);
	//move one step to the given Control
	int move(const Control& t);
//	void reset(){hp = 20;bombnum = 0;}
	void OpenState(int sta){state[sta] = 1;}
	void CloseState(int sta){state[sta] = 0;}
	bool shot();
	void bullet_fly(EnemyList& list,int& score);
	//draw the play on the given screen
	void update(EnemyList& list,int &score);
	Player operator = (const Player& p);
	bool PlayerSurvive(){return survive;}
	friend GameWorld;
	friend ConsoleScreen;
	friend Enemy;
	friend Bullet;
	friend TriBullet;
	friend BossLaser;
	friend EnemyTrack;
	friend EnemyLinger;
	friend EnemyTriB;
	friend Boss;
	friend Helper;
};

#pragma once


#include "Bullet.h"


class Enemy
{
protected:
	DWORD tshot,tshotpre;
	Bullet *b[BulletMax];
	int x , y;//×ø±ê
	int speed;
	bool exist;
	int size;
	int bulletnum;
	int type;
	int explosion;
	int hp;
public:
	virtual void fly(Player* p);//µÐ»ú·ÉÐÐ
	virtual void shot();
	void update(Player& p);
	Enemy(void);
	~Enemy(void);

	friend EnemyList;
};


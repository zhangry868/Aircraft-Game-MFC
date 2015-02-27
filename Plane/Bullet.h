#ifndef BULLET_H
#define BULLET_H

#include "Player.h"
#include "CommonDefinitions.h"

class Bullet
{
protected:
	int x , y;//x,y����
	int type;
	bool exist;//�Ƿ����
public:
	Bullet(int px = 0,int py = 0);
	virtual void fly(EnemyList& list,int& score);//�ӵ�����
	virtual void fly(Player& p);
	~Bullet(void);
	virtual void update();
	friend Enemy;
	friend Player;
	friend EnemyList;
};

class BossLaser:public Bullet
{
	DWORD tshot,tshotpre;
public:
	BossLaser(int px = 0,int py = 0);
	~BossLaser(void);
	void update();
	void fly(Player& p);
	friend Enemy;
	friend Player;
	friend EnemyList;
};

class TriBullet:public Bullet
{
protected:
	int bx,by;//Bullet����
	bool subexist[3];
public:
	TriBullet(int px = 0,int py = 0);
	void fly(EnemyList& list,int& score);//�ӵ�����
	void fly(Player& p);
	~TriBullet(void);
	void update();
	friend Enemy;
	friend Player;
	friend EnemyList;
};

class LaserBullet:public Bullet
{
protected:
	bool subexist[4];
public:
	LaserBullet(int px = 0,int py = 0);
	~LaserBullet(void);
	void update();
	friend Enemy;
	friend Player;
	friend EnemyList;
};


class TriBulletP:public TriBullet
{
public:
	TriBulletP(int px = 0,int py = 0);
	~TriBulletP(void);
	void update();
	friend Enemy;
	friend Player;
	friend EnemyList;
};

#endif
#pragma once

#include "Player.h"
#include "Enemy.h"

class Boss :public Enemy
{
	int mid ;
	int x_move;
public:
	Boss(void);
	~Boss(void);
	virtual void fly(Player* p);
	virtual void shot();
	void Lasershot();
};

#pragma once

#include "Player.h"
#include "Enemy.h"

class EnemyLinger :public Enemy
{
	int mid ;
	int x_move;
public:
	EnemyLinger(void);
	~EnemyLinger(void);
	virtual void fly(Player* p);
};

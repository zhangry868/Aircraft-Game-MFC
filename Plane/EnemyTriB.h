#pragma once

#include "Player.h"
#include "Enemy.h"

class EnemyTriB :public Enemy
{
	int mid ;
	int x_move;
public:
	EnemyTriB(void);
	~EnemyTriB(void);
	virtual void shot();
};

#pragma once

#include "Player.h"
#include "Enemy.h"

class EnemyTrack :public Enemy
{
public:
	EnemyTrack(void);
	~EnemyTrack(void);
	virtual void fly(Player* p);


};

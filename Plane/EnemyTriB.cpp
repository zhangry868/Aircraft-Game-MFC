#include "stdafx.h"
#include "EnemyTriB.h"

EnemyTriB::EnemyTriB(void)
{
	x_move = rand()%2+1;
	if(x < 20)
		x = 20;
	if(x > 699)
		x = 699;
	mid = x;
	speed = 3;
	type = 3;
	size = 42;
	hp = 6;
}

EnemyTriB::~EnemyTriB(void)
{
	for(int i = 0;i < BulletMax; i ++)
	{
		if(b[i] != NULL)
		{
			delete b[i];
			b[i] = NULL;
		}
	}
}

void EnemyTriB::shot()
{
	if(bulletnum < 2)
	{
		b[bulletnum] = new TriBullet(x+size/2,y+0.8*size);
		bulletnum ++;
	}
}
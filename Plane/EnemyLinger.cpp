#include "stdafx.h"
#include "EnemyLinger.h"

EnemyLinger::EnemyLinger(void)
{
	x_move = rand()%2+1;
	if(x < 20)
		x = 20;
	if(x > 699)
		x = 699;
	mid = x;
	speed = 2;
	type = 1;
	size = 30;
	hp = 2;
}

EnemyLinger::~EnemyLinger(void)
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

void EnemyLinger::fly(Player* p)
{
	if(exist)
	{
		if(x - mid >= 20 || mid - x >= 20)
			x_move = -x_move;
		x += x_move;
		y += speed;//敌机向下飞
	}
	if (y >= height)//判断是否出了屏幕
		exist = false;
	int dis = (size + p->size)/2;
	if(exist && x >= p->x-dis && x <= p->x + dis && y >= p->y-dis && y <= p->y+dis)//撞上玩家
	{
		p->hp --;
		if(p->hp <= 0 && p->explosion < 0)
			p->survive = false;
		hp --;
		if(hp <= 0)
			exist = false;
	}
}
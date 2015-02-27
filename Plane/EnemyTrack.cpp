#include "stdafx.h"
#include "EnemyTrack.h"

EnemyTrack::EnemyTrack(void)
{
	speed += 3;
	type = 2;
	size = 30;
	hp = 1;
}

EnemyTrack::~EnemyTrack(void)
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

void EnemyTrack::fly(Player* p)
{
	if(!exist)
		return;
	if(p->x < x)
		x -= 3;
	if(p->x > x)
		x += 3;
	y += speed;//�л����·�
	if (y >= height)//�ж��Ƿ������Ļ
		exist = false;
	if(exist && x >= p->x-30 && x <= p->x + 30 && y >= p->y-30 && y <= p->y+30)//ײ�����
	{
		p->hp --;
		if(p->hp <= 0 && p->explosion < 0)
			p->survive = false;
		exist = false;
	}
}
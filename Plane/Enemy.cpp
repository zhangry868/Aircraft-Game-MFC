#include "stdafx.h"
#include "EnemyList.h"
#include "common.h"

Enemy::Enemy(void)//构造函数
{
	tshot = GetTickCount();
	tshotpre = GetTickCount();
	x = rand()%wide;//随机位置
	y = 0;
	hp = 4;
	speed = rand()%2+2;
	exist = true;
	for(int i = 0; i < BulletMax; i ++)
	{
		b[i] = NULL;
	}
	bulletnum = 0;
	type = 0;
	size = 50;
	explosion = 8;
}



Enemy::~Enemy(void)
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



void Enemy::fly(Player* p)//敌机飞行
{
	if(exist)
		y += speed;//敌机向下飞
	if (y >= height)//判断是否出了屏幕
		exist = false;
	int dis = (size + p->size)/2;
	if(exist && x >= p->x-dis*0.8 && x <= p->x + dis*0.8 && y >= p->y-dis*0.8 && y <= p->y+dis*0.8)//撞上玩家
	{
		p->hp --;
		if(p->hp <= 0 && p->explosion < 0)
			p->survive = false;
		hp --;
		if(hp <= 0)
			exist = false;
	}
}

void Enemy::update(Player& p)
{
	tshot = GetTickCount();
	if(exist && (tshot - tshotpre >= 800))
	{
		shot();
		tshotpre = GetTickCount();
	}
	for(int i = 0; i < bulletnum; i ++)//子弹
	{
		b[i]->fly(p);
		if(!b[i]->exist)
		{
			delete b[i];
			for(int apple = i;apple < bulletnum; apple ++)
			{
				b[apple] = b[apple+1];
			}
			b[bulletnum] = NULL;
			bulletnum --;
		}
		else
		{
			b[i]->update();
		}
	}
	if(exist)
	{
		SelectObject(bufdc , picture);
		if(type == 1 || type == 2)
			TransparentBltU(mdc , x, y ,30,30,bufdc,40,0,30,30,RGB(0,0,0));
		else if(type == 0)
			TransparentBltU(mdc , x, y ,63,50,bufdc,0,33,63,50,RGB(0,0,0));
		else if(type == 3)
			TransparentBltU(mdc , x, y ,42,44,bufdc,75,0,42,44,RGB(0,0,0));
		else if(type == 4)
		{
			SelectObject(bufdc , boss1);
			TransparentBltU(mdc , x, y ,182,186,bufdc,0,0,182,186,RGB(0,0,0));
		}
	}
	else if(!exist && explosion >= 0)
	{
		SelectObject(bufdc , picture);
		tshot = GetTickCount();
		if(tshot - tshotpre >= 70)
		{
			tshotpre = GetTickCount();
			explosion --;
		}
		switch(explosion)
		{
			case 7:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22,150,175,126,RGB(0,0,0));break;
			case 6:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22+175*1,150,175,126,RGB(0,0,0));break;
			case 5:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22+175*2,150,175,126,RGB(0,0,0));break;
			case 4:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22+175*3,150,175,126,RGB(0,0,0));break;
			case 3:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22+175*0,276,175,126,RGB(0,0,0));break;
			case 2:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22+175*1,276,175,126,RGB(0,0,0));break;
			case 1:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22+175*2,276,175,126,RGB(0,0,0));break;
			case 0:TransparentBltU(mdc , x + size/2 - 50, y - size/2 - 50,126,175,bufdc,22+175*3,276,175,126,RGB(0,0,0));break;
		}
	}
}

void Enemy::shot()
{
	if(bulletnum < BulletMax)
	{
		b[bulletnum] = new Bullet(x+size/2,y);
		bulletnum ++;
	}
}

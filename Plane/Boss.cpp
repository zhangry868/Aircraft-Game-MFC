#include "stdafx.h"
#include "Boss.h"

Boss::Boss(void)
{
	if(x < 20)
		x = 20;
	if(x > 699)
		x = 699;
	mid = x;
	speed = 2;
	type = 4;
	size = 182;
	hp = 200;
	x_move = 3;
	explosion = 8;
}
Boss::~Boss(void)
{
}
void Boss::fly(Player* p)
{
	if(exist)
	{
		if(wide/2 - x >= 250 && x_move < 0)
			x_move = -x_move;
		if(x - wide/2 >= 250 && x_move > 0)
			x_move = -x_move;
		x += x_move;
		if(height/10 - y >= 50 && speed < 0)
			speed = -speed;
		else if(y - height/10 >= 50 && speed > 0)
			speed = -speed;
		y += speed;
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
void Boss::shot()
{
	static int count = 0;
	count = (count++)%5;
	if(bulletnum < BulletMax)
	{
		b[bulletnum] = new TriBullet(x+0.8*size/2,y+0.3*size);
		b[bulletnum+1] = new TriBullet(x+1.2*size/2,y+0.4*size);
		b[bulletnum+2] = new TriBullet(x+0.7*size/2,y+0.5*size);
		b[bulletnum+3] = new TriBullet(x+1.3*size/2,y+0.6*size);
		bulletnum += 4;
	}
	if(count == 4)
		Lasershot();
}

void Boss::Lasershot()
{
	if(bulletnum < BulletMax)
	{
		b[bulletnum+0] = new BossLaser(x+16,y+40);
		b[bulletnum+1] = new BossLaser(x+45,y+40);
		b[bulletnum+2] = new BossLaser(x+133,y+70);
		b[bulletnum+3] = new BossLaser(x+163,y+70);
		bulletnum += 4;
		
	}
}
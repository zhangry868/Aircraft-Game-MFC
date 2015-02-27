#include "stdafx.h"
#include "Player.h"
#include "common.h"

Player::Player(int sx, int sy)//构造函数
{
	for(int i = 0; i < 5; i ++)
		state[i] = 0;
	x = sx;
	y = sy;
	bombnum = 3;
	hp = 20;
	survive = true;
	for(int i = 0;i < BulletMax; i ++)
	{
		b[i] = NULL;
	}
	bulletnum = 0;
	tshot = GetTickCount();
	tshotpre = GetTickCount();
	BombState = 2;
	PlaneState = 0;
	size = 30;
	explosion = 8;
}

Player::~Player()//析构函数
{
	for(int i = 0; i < bulletnum; i ++)
	{
		if(b[i] != NULL)
		{
			delete b[i];
			b[i] = NULL;
		}
	}
}


int Player::move(const Control& t)
{//移动
	if(t == UP && y > 3)//上移
		y -= 3;
	else if(t == DOWN && y < height-30*3)//下移
		y += 3;
	else if(t == LEFT && x > 3)//左移
		x -= 3;
	else if(t == RIGHT  && x < wide-30 )//右移
		x += 3;
	return 0;
}

void Player::update(EnemyList& list,int& score)//更新
{
	if(state[0])
		move(UP);
	if(state[1])
		move(DOWN);
	if(state[2])
		move(LEFT);
	if(state[3])
		move(RIGHT);
	if(state[4])
	{
		tshot = GetTickCount();
		if(survive && (tshot - tshotpre >= 140))
		{
			shot();
			tshotpre = GetTickCount();
		}
	}
	for(int i = 0; i < bulletnum; i ++)//子弹
	{
		b[i]->fly(list,score);
		if(!(b[i]->exist))
		{
			delete b[i];
			b[i] = NULL;
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
	if(survive)
	{
		SelectObject(bufdc , picture);
		if(PlaneState == 0)
			TransparentBltU(mdc , x, y ,28 , 30 , bufdc , 0, 0, 28, 30, RGB(0,0,0));
		else if(PlaneState == 1)
			TransparentBltU(mdc , x, y ,41 , 48 , bufdc , 122 , 0,41 , 48,RGB(0,0,0));
		else if(PlaneState == 2)
			TransparentBltU(mdc , x, y ,42 , 52 , bufdc , 169 , 0,42 , 52,RGB(0,0,0));
	}
	else if(!survive && explosion >= 0)
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

void Player::bullet_fly(EnemyList &list,int& score)//子弹飞行
{
	for(int i = 0; i < bulletnum; i ++)
	{
		if(b[i] != NULL)
			b[i]->fly(list,score);//是否命中敌机
	}
}

bool Player::shot()
{
	if(bulletnum < BulletMax)
	{
		if(BombState == 0)
			b[bulletnum] = new Bullet(x+size*0.4,y+size*0.2);
		if(BombState == 2)
			b[bulletnum] = new TriBulletP(x+size*0.4,y+size*0.2);
		if(BombState == 3)
			b[bulletnum] = new LaserBullet(x+size*0.4,y+size*0.2);
		bulletnum ++;
		return true;
	}
	return false;
}

Player Player::operator = (const Player& p)
{
	x = p.x;
	y = p.y;
	survive = p.survive;
	bulletnum = p.bulletnum;
	for(int i = 0; i < bulletnum; i ++)
	{
		b[i] = new Bullet(*(p.b[i]));
	}
	return (*this);
}

Player::Player(const Player& p)
{
	x = p.x;
	y = p.y;
	survive = p.survive;
	bulletnum = p.bulletnum;
	for(int i = 0; i < bulletnum; i ++)
	{
		b[i] = new Bullet(*(p.b[i]));
	}
	explosion = 8;
}
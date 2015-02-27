#include "stdafx.h"
#include "Bullet.h"
#include "common.h"

Bullet::Bullet(int px,int py)//���캯��
{
	x = px;
	y = py;
	exist = true;
	type = 0;
}

Bullet::~Bullet(void)
{
}

void Bullet::fly(EnemyList& list,int& score)//����
{
	y -= 7;
	if(y < 0)//Խ����
	{
		y = 0;
		exist = false;
		return;
	}
	list.hit(this,score,type);
}

void Bullet::fly(Player &p)
{
	y += 6;
	if(y >= height)//Խ����
	{
		y = height-1;
		exist = false;
		return;
	}
	if(y >= p.y && y <= p.y + p.size && x >= p.x && x <= p.x + p.size)//����
	{
		p.hp --;
		if(p.hp <= 0 && p.survive)
			p.survive = false;
		exist = false;
		return;
	}
}

void Bullet::update()//�����ӵ���ͼƬ
{
	SelectObject(bufdc,picture);//ѡ��ͼƬ
	BitBlt(mdc , x , y , 3, 10 , bufdc , 30 , 0 , SRCCOPY);
}

TriBullet::TriBullet(int px,int py)//���캯��
{
	x = px;
	y = py;
	bx = px;
	by = py;
	exist = true;
	type = 1;
	for(int i = 0;i < 3;i ++)
		subexist[i] = true;
}

TriBullet::~TriBullet(void)
{
}

void TriBullet::fly(EnemyList& list,int& score)//����
{
	y -= 7;
	if(y < 0)//Խ����
	{
		y = 0;
		exist = false;
		return;
	}
	list.hit(this,score,type);
}

void TriBullet::fly(Player &p)
{
	y += 6;
	if(y >= height)//Խ����
	{
		y = height-1;
		this->exist = false;
		return;
	}
	if(subexist[0] && y >= p.y && y <= p.y + p.size && x >= p.x && x <= p.x + p.size)
	{
		p.hp --;
		if(p.hp <= 0 && p.survive)
			p.survive = false;
		subexist[0] = false;
		return;
	}
	if(subexist[1] && y >= p.y && y <= p.y + p.size && x+abs(y-by)*0.5 >= p.x && x+abs(y-by)*0.5 <= p.x + p.size)
	{
		p.hp --;
		if(p.hp <= 0 && p.survive)
			p.survive = false;
		subexist[1] = false;
		return;
	}
	if(subexist[2] && y >= p.y && y <= p.y + p.size && x-abs(y-by)*0.5 >= p.x && x-abs(y-by)*0.5 <= p.x + p.size)
	{
		p.hp --;
		if(p.hp <= 0 && p.survive)
			p.survive = false;
		subexist[2] = false;
		return;
	}
	int i;
	for(i = 0;i < 3;i ++)
	{
		if(subexist[i])
			break;
	}
	if(i == 3)
		exist = false;
}

void TriBullet::update()//�����ӵ���ͼƬ
{
	SelectObject(bufdc,picture);//ѡ��ͼƬ
	if(subexist[0])
		BitBlt(mdc , x , y , 7, 7 , bufdc , 30 , 13 , SRCCOPY);
	if(subexist[1])
		BitBlt(mdc , x+abs(y-by)*0.5, y , 7, 7 , bufdc , 30 , 13 , SRCCOPY);
	if(subexist[2])
		BitBlt(mdc , x-abs(y-by)*0.5, y , 7, 7 , bufdc , 30 , 13 , SRCCOPY);
	/*
	if(subexist[0])
		BitBlt(mdc , x , y , 10, 25 , bufdc , 11 , 125 , SRCCOPY);
	if(subexist[1])
		BitBlt(mdc , x+abs(y-by)*0.5, y , 10, 25 , bufdc , 22 , 125 , SRCCOPY);
	if(subexist[2])
		BitBlt(mdc , x-abs(y-by)*0.5, y , 10, 25 , bufdc , 0 , 125 , SRCCOPY);
	*/
}

TriBulletP::TriBulletP(int px,int py)//���캯��
{
	x = px;
	y = py;
	bx = px;
	by = py;
	exist = true;
	type = 2;
}

TriBulletP::~TriBulletP(void)
{
}

void TriBulletP::update()//�����ӵ���ͼƬ
{
	SelectObject(bufdc,picture);//ѡ��ͼƬ
	if(subexist[0])
		TransparentBltU(mdc , x , y , 10, 25 , bufdc , 11 , 125 , 10, 25,RGB(0,0,0));
	if(subexist[1])
		TransparentBltU(mdc , x+abs(y-by)*0.5, y , 10, 25 , bufdc , 22 , 125 , 10, 25,RGB(0,0,0));
	if(subexist[2])
		TransparentBltU(mdc , x-abs(y-by)*0.5, y , 10, 25 , bufdc , 0 , 125 , 10, 25 ,RGB(0,0,0));
}

LaserBullet::LaserBullet(int px,int py)//���캯��
{
	x = px;
	y = py;
	exist = true;
	type = 3;
}

LaserBullet::~LaserBullet(void)
{
}

void LaserBullet::update()//�����ӵ���ͼƬ
{
	SelectObject(bufdc,picture);//ѡ��ͼƬ
	if(subexist[0])
		TransparentBltU(mdc , x-15 , y , 7, 25 , bufdc , 216 , 0 , 7, 25,RGB(0,0,0));
	if(subexist[1])
		TransparentBltU(mdc , x-5, y , 7, 25 , bufdc , 216 , 0 , 7, 25,RGB(0,0,0));
	if(subexist[2])
		TransparentBltU(mdc , x+5, y , 7, 25 , bufdc , 216 , 0 , 7, 25 ,RGB(0,0,0));
	if(subexist[3])
		TransparentBltU(mdc , x+15, y , 7, 25 , bufdc , 216 , 0 , 7, 25 ,RGB(0,0,0));
}



BossLaser::BossLaser(int px,int py)
{
	x = px;
	y = py;
	exist = true;
	type = 4;
	tshotpre = GetTickCount();
}
BossLaser::~BossLaser(void)
{

}

void BossLaser::update()
{
	SelectObject(bufdc,bg);//ѡ��ͼƬ
	//BitBlt(mdc , x, y , 7, 200 , bufdc ,1025,0,SRCCOPY);
	if(exist)
 		TransparentBltU(mdc , x, y , 7, 768-y , bufdc , 1025 , 0 , 7, 768-y, RGB(0,0,0));
}

void BossLaser::fly(Player& p)
{

	if(!exist || x >= wide)//Խ����
	{
		x = wide-1;
		exist = false;
		return;
	}
	tshot = GetTickCount();
	if(exist && (tshot - tshotpre >= 20))
	{
		exist = false;
	}
	if(x >= p.x && x <= p.x + p.size)//����
	{
		p.hp --;
		if(p.hp <= 0 && p.survive)
			p.survive = false;
		return;
	}
}
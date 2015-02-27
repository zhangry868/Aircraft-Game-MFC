#include "stdafx.h"
#include "Helper.h"
#include "common.h"

Helper::Helper(void)
{
	x = rand() % wide;
	y = 0;
	type = rand() % 5;
	exist = true;
}

Helper::~Helper(void)
{
}

//wide
//height

void Helper::get(Player* p)
{
	y += 2;
	if (y >= height)//判断是否出了屏幕
	{
		y = height-1;
		exist = false;
	}
	if(exist && x >= p->x-p->size && x <= p->x + p->size && y >= p->y-p->size && y <= p->y+p->size)//撞上玩家
	{
		if(type == 0){
			p->BombState = 3;
		}
		else if(type == 1){
			p->bombnum ++;
		}
		else if(type == 2){
			p->BombState = 2;
			//p->PlaneState = 0;
		}
		else if(type == 3){
			p->hp ++;
		}
		else if(type == 4){
			if(p->PlaneState <= 1)
				p->PlaneState ++;
			p->size = 40;
		}
		exist = false;
	}
}
//Laser,Bomb,General,Hp,Protect
void Helper::update(Player* p)
{
	get(p);//Laser
	if(!exist) return; 
	if(type == 0){
		SelectObject(bufdc ,Laser);
		TransparentBltU(mdc , x, y ,20 , 20 , bufdc , 0, 0, 20, 20, RGB(255,255,255));
		//BitBlt(mdc , x, y , 10 , 10 ,bufdc , 0 , 0 ,SRCCOPY);
	}
	else if(type == 1){
		SelectObject(bufdc ,Bomb);
		TransparentBltU(mdc , x, y ,20 , 20 , bufdc , 0, 0, 20, 20, RGB(255,255,255));
		//BitBlt(mdc , x, y , 10 , 10 ,bufdc , 0 , 0 ,SRCCOPY);
	}
	else if(type == 2){
		SelectObject(bufdc ,General);
		TransparentBltU(mdc , x, y ,20 , 20 , bufdc , 0, 0, 20, 20, RGB(255,255,255));
		//BitBlt(mdc , x, y , 10 , 10 ,bufdc , 0 , 0 ,SRCCOPY);
	}
	else if(type == 3){
		SelectObject(bufdc ,Hp);
		TransparentBltU(mdc , x, y ,20 , 20 , bufdc , 0, 0, 20, 20, RGB(255,255,255));
		//BitBlt(mdc , x, y , 10 , 10 ,bufdc , 0 , 0 ,SRCCOPY);
	}
	else if(type == 4){
		SelectObject(bufdc ,Protect);
		TransparentBltU(mdc , x, y ,20 , 20 , bufdc , 0, 0, 20, 20, RGB(255,255,255));
		//BitBlt(mdc , x, y , 10 , 10 ,bufdc , 0 , 0 ,SRCCOPY);
	}
}
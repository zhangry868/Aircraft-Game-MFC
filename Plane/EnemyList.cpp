#include "stdafx.h"
#include "EnemyList.h"
#include "GameWorld.h"

EnemyList::EnemyList(void)//构造函数
{
	top = new Node;
	top->enemy = NULL;
	top->next = NULL;
	BossExist = false;
}

EnemyList::~EnemyList(void)//析构函数
{
	Node* p = top;
	while(top != NULL)
	{
		p = top->next;
		delete top->enemy;
		delete top;
		top = p;
	}
	top = NULL;
}

void EnemyList::Create()//创建敌机
{
	static bool only = true;
	Node* p = new Node;
	p->next = NULL;
	int random = rand()%4;
	if(game.hardness % 2 == 0 && game.score % 1000  < 200)
	{	
		BossExist = true;
	}
	if(!BossExist)
	{	
		only = true;
		if(random == 0)
			p->enemy = new Enemy;
		else if(random == 1)
			p->enemy = new EnemyTrack;
		else if(random == 2)
			p->enemy = new EnemyLinger;
		else if(random == 3)
			p->enemy = new EnemyTriB;
		p->next = top->next;
		top->next = p;
	}
	else
	{
		if(only)
		{
			p->enemy = new Boss;
			only = false;
			p->next = top->next;
			top->next = p;
		}
	}
}

void EnemyList::del(Node* p)
{
	Node* ptemp = p->next;
	p->next = ptemp->next;
	delete ptemp->enemy;
	delete ptemp;
}

void EnemyList::update(Player* p)//更新
{
	Node* pEnemy = top;
	while(pEnemy->next != NULL)//遍历
	{
		pEnemy->next->enemy->fly(p);
		if((pEnemy->next->enemy->y >= height) || pEnemy->next->enemy->explosion < 0)//越界或被击落
		{
			if(pEnemy->next->enemy->type == 4)
				BossExist = false;
			//if(pEnemy->next->enemy->y >= height)
				del(pEnemy);//删除敌机
		}
		else
		{
			pEnemy->next->enemy->update(*p);//更新敌机
			pEnemy = pEnemy->next;//下一架敌机
		}
	}
}

void EnemyList::hit(Bullet *b,int &score,int type)
{
	Node* p = top->next;
	while(p != NULL)//遍历敌机
	{
		if(type == 0 && p->enemy->exist && b->x >= p->enemy->x  && b->x <= p->enemy->x + p->enemy->size \
			&&  b->y >= p->enemy->y && b->y <= p->enemy->y + p->enemy->size * 0.8)//命中敌机，子弹和敌机一起消亡
		{
			b->exist = false;
			p->enemy->hp --;
			if(p->enemy->hp <= 0)
			{
				score += 50 * (p->enemy->size/10);
				p->enemy->exist = false;
			}
			return;
		}
		else if(type == 2 && p->enemy->exist)
		{
			TriBullet* temp = (TriBullet*)b;
			if(temp->subexist[0] && b->x >= p->enemy->x  && b->x <= p->enemy->x + p->enemy->size && b->y >= p->enemy->y && b->y <= p->enemy->y + p->enemy->size * 0.8)
			{
				p->enemy->hp --;
				temp->subexist[0] = false;
				if(p->enemy->hp <= 0)
				{
					score += 50 * (p->enemy->size/10);
					p->enemy->exist = false;
				}
			}
			if(temp->subexist[1] && b->x + 0.5*abs(b->y - temp->by) >= p->enemy->x  && b->x + 0.5*abs(b->y - temp->by) <= p->enemy->x + p->enemy->size && b->y >= p->enemy->y && b->y <= p->enemy->y + p->enemy->size * 0.8)
			{
				p->enemy->hp --;
				temp->subexist[1] = false;
				if(p->enemy->hp <= 0)
				{
					score += 50 * (p->enemy->size/10);
					p->enemy->exist = false;
				}
			}
			if(temp->subexist[2] && b->x - 0.5*abs(b->y - temp->by) >= p->enemy->x  && b->x - 0.5*abs(b->y - temp->by) <= p->enemy->x + p->enemy->size && b->y >= p->enemy->y && b->y <= p->enemy->y + p->enemy->size * 0.8)
			{
				p->enemy->hp --;
				temp->subexist[2] = false;
				if(p->enemy->hp <= 0)
				{
					score += 50 * (p->enemy->size/10);
					p->enemy->exist = false;
				}
			}
			if(!(temp->subexist[2]|temp->subexist[1]|temp->subexist[0]))
			{	
				b->exist = false;
				return;
			}
			else
				p = p->next;
		}
		else if(type == 3 && p->enemy->exist)
		{
			LaserBullet* temp = (LaserBullet*)b;
			for(int i = 0;i < 4;i ++)
				if(temp->subexist[i] && b->x + (i-2)*10 + 5>= p->enemy->x  && b->x + (i-2)*10 + 5<= p->enemy->x + p->enemy->size && b->y >= p->enemy->y && b->y <= p->enemy->y + p->enemy->size * 0.8)
				{
					p->enemy->hp --;
					temp->subexist[i] = false;
					if(p->enemy->hp <= 0)
					{
						score += 50 * (p->enemy->size/10);
						p->enemy->exist = false;
					}
				}
			if(!(temp->subexist[2]|temp->subexist[1]|temp->subexist[0]|temp->subexist[3]))
			{	
				b->exist = false;
				return;
			}
			else
				p = p->next;
		}
		else
			p = p->next;
	}
}

void EnemyList::Clear()//敌机全灭
{
	Node* p = top->next;
	while(p != NULL)
	{
		p -> enemy -> hp -= 10;
		if(p -> enemy -> hp < 0)
			p -> enemy -> exist = false;
		p = p->next;
	}
}

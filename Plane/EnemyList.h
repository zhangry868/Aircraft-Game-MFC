#pragma once

#include "EnemyTrack.h"
#include "EnemyLinger.h"
#include "EnemyTriB.h"
#include "Boss.h"
#include "CommonDefinitions.h"

class EnemyList
{
	struct Node
	{
		Enemy* enemy;
		Node* next;
	} *top;
	bool BossExist;
	void del(Node* p);
public:
	void Create();//增加敌机
	void update(Player* p);//更新敌机
	void hit(Bullet* b,int& hardness,int type);
	void Clear();//全灭
	EnemyList(void);
	~EnemyList(void);

	friend Bullet;
};

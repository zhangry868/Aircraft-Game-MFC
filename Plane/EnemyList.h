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
	void Create();//���ӵл�
	void update(Player* p);//���µл�
	void hit(Bullet* b,int& hardness,int type);
	void Clear();//ȫ��
	EnemyList(void);
	~EnemyList(void);

	friend Bullet;
};

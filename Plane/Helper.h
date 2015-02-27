#pragma once

#include "CommonDefinitions.h"

#include "Player.h"
class Helper
{
	int x,y;
	int type;
	bool exist;
public:
	Helper(void);
	~Helper(void);
	void get(Player* p);
	void update(Player* p);
	friend GameWorld;
};

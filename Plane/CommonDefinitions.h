#pragma once

#include <iostream>
#include "stdafx.h"

using namespace std;
const int wide = 1024;
const int height = 768;
const int BulletMax = 200;

extern HDC hdc ,mdc ,bufdc ;
extern HWND hWnd;
extern HBITMAP picture,Laser,Bomb,General,Hp,Protect,bg,boss1;
enum Control{RIGHT,UP,LEFT,DOWN,NONE};

class Player;
class Bullet;
class ConsoleScreen;
class GameWorld;
class Enemy;
class EnemyList;
class EnemyTrack;
class EnemyLinger;
class Helper;

extern GameWorld game;

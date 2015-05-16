/*
 * Alien.h
 *
 *  Created on: 15/04/2015
 *      Author: Vitor
 */

#ifndef TRAB_ALIEN_H_
#define TRAB_ALIEN_H_
#include <iostream>
#include <vector>
#include <queue>
#include "Sprite.h"
#include "Point.h"
#include "GameObject.h"
#include "Minion.h"
#include "StillAnimation.h"
#include "Timer.h"
#include "Sound.h"

using std::cout;
using std::endl;

class Alien : public GameObject{
public:
	Alien(float x,float y,int nMinions,int cooldown);
	~Alien();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
	static int alienCount;
private:
	class Action{
		public:
			enum ActionType{MOVE,SHOOT};
			Action(ActionType type,float x, float y);
			ActionType type;
			Point pos;
		};
	Sprite sp;
	Point speed;
	int hp;
	std::queue<Action> taskQueue;
	std::vector<Minion> minionArray;
	enum AlienState{MOVING,RESTING};
	AlienState alienState;
	Timer shootCoolDown;
	int cooldown;

};


#endif /* TRAB_ALIEN_H_ */

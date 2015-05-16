/*
 * Bullet.h
 *
 *  Created on: 16/04/2015
 *      Author: Vitor
 */

#ifndef TRAB_BULLET_H_
#define TRAB_BULLET_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Point.h"
#include <iostream>
#include <math.h>

using std::string;
using std::cout;
using std::endl;

class Bullet : public GameObject{
public:
	Bullet(float x,float y,float angle, float speed,float maxDistance, string sprite,bool targetsPlay,int frameCount = 1);
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
	bool targetsPlayer;
private:
	Sprite sp;
	Point speed;
	float distanceLeft;
	float angle;
};




#endif /* TRAB_BULLET_H_ */

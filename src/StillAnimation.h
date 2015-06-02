/*
 * StillAnimation.h
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */

#ifndef SRC_STILLANIMATION_H_
#define SRC_STILLANIMATION_H_

#include "GameObject.h"
#include "Timer.h"

class StillAnimation: public GameObject{
public:
	StillAnimation(float x, float y, float rotation, Sprite sprite,float timeLimit,bool ends);
	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(string type);
	Sprite getSprite();
private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;
};



#endif /* SRC_STILLANIMATION_H_ */

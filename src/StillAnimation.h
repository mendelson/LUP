/*
 * StillAnimation.h
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */

#ifndef SRC_STILLANIMATION_H_
#define SRC_STILLANIMATION_H_

#include "GameObject.h"
#include "InputManager.h"
#include "Timer.h"

class StillAnimation: public GameObject{
public:
	StillAnimation(float x, float y,  GameObject* planet, float rotation, Sprite sprite,float timeLimit,bool ends, float alturaInicial);
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
	GameObject* planet;
	float alturaInicial;
};



#endif /* SRC_STILLANIMATION_H_ */

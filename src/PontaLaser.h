/*
 * PontaLaser.h
 *
 *  Created on: 12/07/2015
 *      Author: Vitor
 */

#ifndef SRC_PONTALASER_H_
#define SRC_PONTALASER_H_

#include "GameObject.h"
#include "Timer.h"

class PontaLaser : public GameObject{
public:
	PontaLaser(float x,float y,GameObject* planet, float rotation,float alturaInicial,int d);
	~PontaLaser();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	void NotifyCollision(GameObject&);
	bool Is(string type);
private:
	Sprite sp;
	GameObject* planet;
	float alturaInicial;
	int d;

};

#endif /* SRC_PONTALASER_H_ */

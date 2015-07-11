/*
 * Laser.h
 *
 *  Created on: 11/07/2015
 *      Author: Vitor
 */

#ifndef SRC_LASER_H_
#define SRC_LASER_H_

#include "GameObject.h"
#include "Timer.h"

class Laser : public GameObject{
public:
	Laser(float x,float y,GameObject* planet, float rotation,float alturaInicial,int frameI,int frameC);
	~Laser();
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
	Timer timer;
	int frameCarregado;
	int frameInit;

};

#endif /* SRC_LASER_H_ */

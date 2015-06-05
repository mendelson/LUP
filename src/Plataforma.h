/*
 * Plataforma1.h
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#ifndef SRC_PLATAFORMA_H_
#define SRC_PLATAFORMA_H_

#include "GameObject.h"

class Plataforma : public GameObject{
public:
	Plataforma(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file);
	~Plataforma();
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

};

#endif /* SRC_PLATAFORMA_H_ */

/*
 * Plataforma1.h
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#ifndef SRC_PLATAFORMA1_H_
#define SRC_PLATAFORMA1_H_

#include "GameObject.h"

class Plataforma1 : public GameObject{
public:
	Plataforma1(float x,float y,float rotation);
	~Plataforma1();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	void NotifyCollision(GameObject&);
	bool Is(string type);
private:
	Sprite body;
	Rect initBox;
	float initRotation;
};

#endif /* SRC_PLATAFORMA1_H_ */

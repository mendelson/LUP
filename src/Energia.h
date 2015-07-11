/*
 * Energia.h
 *
 *  Created on: 28/06/2015
 *      Author: Vitor
 */

#ifndef SRC_ENERGIA_H_
#define SRC_ENERGIA_H_

#include "GameObject.h"

class Energia : public GameObject {
public:
	Energia(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file,int qntdFrames);
	~Energia();
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
	bool dead;
	bool willDie;
};

#endif /* SRC_ENERGIA_H_ */

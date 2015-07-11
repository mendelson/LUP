/*
 * Cometa.h
 *
 *  Created on: 09/07/2015
 *      Author: Vitor
 */

#ifndef SRC_COMETA_H_
#define SRC_COMETA_H_

#include "GameObject.h"

class Cometa : public GameObject{
public:
	Cometa(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file);
	~Cometa();
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
	float initialX;

};

#endif /* SRC_COMETA_H_ */

/*
 * Planet.h
 *
 *  Created on: 05/06/2015
 *      Author: Vitor
 */

#ifndef SRC_PLANET_H_
#define SRC_PLANET_H_
#include "GameObject.h"
#include "Sprite.h"

class Planet : public GameObject{
public:
	Planet(float x, float y,string file);
	~Planet();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
private:
	Sprite sp;
};

#endif /* SRC_PLANET_H_ */

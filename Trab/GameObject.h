/*
 * GameObject.h
 *
 *  Created on: 27/03/2015
 *      Author: Vitor
 */

#ifndef TRAB_GAMEOBJECT_H_
#define TRAB_GAMEOBJECT_H_
#include "Rect.h"
#include "Point.h"
#include "Sprite.h"
using std::string;

class GameObject{
public:
	virtual ~GameObject(){};
	GameObject(){rotation = 0;}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual Sprite getSprite() = 0;
	Rect box;
	float rotation;
	virtual void NotifyCollision(GameObject&) = 0;
	virtual bool Is(string type) = 0;
};



#endif /* TRAB_GAMEOBJECT_H_ */

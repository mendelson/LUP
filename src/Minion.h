/*
 * Minion.h
 *
 *  Created on: 15/04/2015
 *      Author: Vitor
 */

#ifndef SRC_MINION_H_
#define SRC_MINION_H_
#include "GameObject.h"
#include "Point.h"
#include "Bullet.h"

class Minion: public GameObject{
public:
	Minion(GameObject* minionCenter, float arcOffset);
	~Minion(){}
	void Update(float dt);
	void Render();
	bool IsDead();
	void Shoot(Point pos);
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
private:
	GameObject* center;
	Sprite sp;
	float arc;
};



#endif /* SRC_MINION_H_ */

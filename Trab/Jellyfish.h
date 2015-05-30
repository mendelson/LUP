/*
 * Jellyfish.h
 *
 *  Created on: 29/05/2015
 *      Author: Lucas
 */

#ifndef TRAB_JELLYFISH_H_
#define TRAB_JELLYFISH_H_
#include "Sprite.h"
#include "Point.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"

class Jellyfish : public GameObject{
public:
	Jellyfish(float x,float y);
	~Jellyfish();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
	void Shoot(Point pos);
private:
	Sprite sp;
	Point speed;
	int hp;
	Timer shootcd;
	Facing orientation;
};


#endif /* TRAB_JELLYFISH_H_ */

/*
 * Enemy3.h
 *
 *  Created on: 23 Jun 2015
 *      Author: Baile
 */

#ifndef SRC_ENEMY3_H_
#define SRC_ENEMY3_H_

#include "Sprite.h"
#include "Point.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"

class Enemy3: public GameObject {
public:
	Enemy3(float x, float y, GameObject* planet, float initialRotation, float alturaInicial);
	~Enemy3();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void Shoot (Point pos);
	void NotifyCollision(GameObject&);
private:
	Sprite sp;
	Point speed;
	Point startPos;
	int hp;
	Timer dmgCD;
	Facing orientation;
	GameObject* planet;
	float alturaInicial;
	Timer knockback;
	Timer shootcd;
	Facing kbDirection;
};



#endif /* SRC_ENEMY3_H_ */

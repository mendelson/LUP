/*
 * Jellyfish.h
 *
 *  Created on: 29/05/2015
 *      Author: Lucas
 */

#ifndef SRC_ENEMYJELLYFISH_H_
#define SRC_ENEMYJELLYFISH_H_
#include "Sprite.h"
#include "Point.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"
#include "Planet.h"

class EnemyJellyfish : public GameObject{
public:
	EnemyJellyfish(GameObject* planet, float initialRotation, float alturaInicial);
	~EnemyJellyfish();
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
	float alturaInicial;
	GameObject* planet;
};


#endif /* SRC_ENEMYJELLYFISH_H_ */

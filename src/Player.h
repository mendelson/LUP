/*
 * Player.h
 *
 *  Created on: 22/05/2015
 *      Author: Vitor
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_
#include "GameObject.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"

class Player : public GameObject{
public:
	Player(float x,float y);
	~Player();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	static Player* player;
	bool Is(string type);
	void NotifyCollision(GameObject&);
private:
	Sprite bodySp;
	Sprite weaponSp;
	Point speed;
	float linearSpeed;
	float cannonAngle;
	int hp;
	Timer timer;
};


#endif /* SRC_PLAYER_H_ */

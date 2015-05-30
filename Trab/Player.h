/*
 * Player.h
 *
 *  Created on: 22/05/2015
 *      Author: Vitor
 */

#ifndef TRAB_PLAYER_H_
#define TRAB_PLAYER_H_
#include "GameObject.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"

enum Jumping { STAND, JUMP, DJUMP };

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
	Sprite sp;
	Point speed;
	int hp;
	Timer timer;
	Jumping jumpState;
	Facing orientation;
	int jumpY;
	int jumped;
};


#endif /* TRAB_PLAYER_H_ */

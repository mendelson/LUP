/*
 * Player.h
 *
 *  Created on: 29/05/2015
 *      Author: Lucas
 */

#ifndef SRC_SUPPORT_H_
#define SRC_SUPPORT_H_
#include "GameObject.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"
#include "Player.h"

class Support : public GameObject{
public:
	Support();
	~Support();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
private:
	Sprite sp;
	Timer timer;
	Facing orientation;
};


#endif /* SRC_SUPPORT_H_ */

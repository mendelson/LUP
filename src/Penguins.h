/*
 * Penguins.h
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */

#ifndef SRC_PENGUINS_H_
#define SRC_PENGUINS_H_
#include "GameObject.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"

class Penguins: public GameObject {
public:
	Penguins(float x, float y);
	~Penguins();
	void Update(float dt);
	void Render();
	bool IsDead();
	void Shoot();
	Sprite getSprite();
	static Penguins* player;
	bool Is(string type);
	void NotifyCollision(GameObject&);
	int getLife() {	return hp; }
	int getXp() { return xp; }
	bool getEnergyUpdate() { return newEnergy; }

private:
	Sprite bodySp;
	Sprite cannonSp;
	Point speed;
	float linearSpeed;
	float cannonAngle;
	int hp;
	int xp;
	bool newEnergy;
	Timer timer;
	bool pulando;
	float posInicial;
};

#endif /* SRC_PENGUINS_H_ */

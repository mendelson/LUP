
#ifndef TRAB_WEAPON_H_
#define TRAB_WEAPON_H_
#include "GameObject.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Player.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"

class Weapon : public GameObject{
public:
	Weapon(std::string file);
	~Weapon();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
	Facing orientation;

private:
	Sprite sp;
};


#endif /* TRAB_WEAPON_H_ */

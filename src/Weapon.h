
#ifndef SRC_WEAPON_H_
#define SRC_WEAPON_H_
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
	bool atkFrame;
	Sprite sp;
};


#endif /* SRC_WEAPON_H_ */

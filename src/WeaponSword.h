
#ifndef SRC_WEAPONSWORD_H_
#define SRC_WEAPONSWORD_H_
#include "GameObject.h"
#include "Weapon.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Player.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"

class WeaponSword : public Weapon{
public:
	WeaponSword(std::string file);
	~WeaponSword();
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


#endif /* SRC_WEAPONSWORD_H_ */

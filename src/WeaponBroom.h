
#ifndef SRC_WEAPONBROOM_H_
#define SRC_WEAPONBROOM_H_

#include <string>

#include "GameObject.h"
#include "Sprite.h"
#include "Weapon.h"

class WeaponBroom : public Weapon{
public:
	WeaponBroom(std::string file);
	~WeaponBroom();
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


#endif /* SRC_WEAPONBROOM_H_ */

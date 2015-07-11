
#ifndef SRC_WEAPON_H_
#define SRC_WEAPON_H_

#include "GameObject.h"
#include "Timer.h"


class Weapon : public GameObject{
public:
	Weapon();
	~Weapon();
	void Kill();
	bool isDead;
	Timer deathCD;
private:

};


#endif /* SRC_WEAPON_H_ */

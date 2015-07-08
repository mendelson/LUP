
#ifndef SRC_WEAPON_H_
#define SRC_WEAPON_H_

#include "GameObject.h"


class Weapon : public GameObject{
public:
	Weapon();
	~Weapon();
	void Kill();
	bool isDead;
private:

};


#endif /* SRC_WEAPON_H_ */

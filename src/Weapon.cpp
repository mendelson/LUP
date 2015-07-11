#include "Weapon.h"

Weapon::Weapon() : deathCD()
{

}

Weapon::~Weapon()
{

}

void Weapon::Kill()
{
	isDead = true;
}

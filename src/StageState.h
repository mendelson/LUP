#ifndef SRC_STAGESTATE_H_
#define SRC_STAGESTATE_H_

#include <string>

#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "Timer.h"
#include "UI.h"

class Weapon;

using std::string;

class StageState: public State {
public:
	enum WeaponName_lazy {
		BROOM, SWORD, GUN
	};

	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	static WeaponName_lazy CheckWeapon();
private:
	Sprite bg;
	Music music;
	UI ui;
	float xBg;
	Weapon* activeWeapon;
	Timer changeWpCD;
	static WeaponName_lazy weapon;
};

#endif /* SRC_STAGESTATE_H_ */

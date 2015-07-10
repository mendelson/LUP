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
	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	static int CheckWeapon();
private:
	Sprite bg;
	Music music;
	UI ui;
	float xBg;
	Weapon* activeWeapon;
	Timer changeWpCD;
	static int weapon;
};

#endif /* SRC_STAGESTATE_H_ */

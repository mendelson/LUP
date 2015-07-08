#ifndef SRC_UI_H_
#define SRC_UI_H_

#include "Sprite.h"
#include "Text.h"
#include "Timer.h"

class UI {
public:
	UI(int requiredEnergy, int collectedEnergy = 0);
	~UI() {};

	void Update(float dt);
	void Render();

private:
	int xp; // Percentage
	int life; // Percentage
	int special; // Percentage
	const int requiredEnergy;
	int collectedEnergy;
	bool newEnergy;

	Text textNewEnergy;
	Timer timer;
	bool firstExecution;

	float centerX;
	float centerY;
	float xpUnitConstant;


	Sprite bgLife;
	Sprite bgXpBackground;
	Sprite bgXpUnit;
	Sprite bgSpecial;
	Sprite bgBroom;
	Sprite bgSword;
	Sprite bgEnergyBackground;
};

#endif /* SRC_UI_H_ */

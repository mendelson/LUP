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
	const int requiredEnergy;
	int collectedEnergy;
	bool newEnergy;

	Text textNewEnergy;
	Timer timer;
	bool firstExecution;

	float centerX;
	float centerY;
	float xpUnitConstant;


	Sprite bgLifeBackground;
	Sprite bgLifeUnit;
	Sprite bgLifeHeart;
	Sprite bgXpBackground;
	Sprite bgXpUnit;
	Sprite bgEnergy;
};

#endif /* SRC_UI_H_ */

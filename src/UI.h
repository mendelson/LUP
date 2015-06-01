/*
 * UI.h
 *
 *  Created on: 31/05/2015
 *      Author: MateusMendelson
 */

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

	Sprite bgXp;
	Sprite bgLife;
	Sprite bgEnergy;

	Text textNewEnergy;
	Timer timer;
	bool firstExecution;
};

#endif /* SRC_UI_H_ */

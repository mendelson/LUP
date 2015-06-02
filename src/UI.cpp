/*
 * UI.cpp
 *
 *  Created on: 31/05/2015
 *      Author: MateusMendelson
 */

#include "UI.h"

#include <sstream>
#include <string>

#include "Penguins.h"

UI::UI(int requiredEnergy, int collectedEnergy) :
		requiredEnergy(requiredEnergy),
		textNewEnergy("font/Call me maybe.ttf", 40, Text::BLENDED, "Energia recolhida!", { 0, 0, 0 }, 350, 250),
		timer() {
	this->xp = 0;
	this->life = 0;
	this->collectedEnergy = collectedEnergy;
	this->newEnergy = false;
	this->firstExecution = true;
}

void UI::Update(float dt) {
	timer.Update(dt);

	if (Penguins::player != NULL) {
		this->xp = Penguins::player->getXp();
		this->life = Penguins::player->getLife();

		newEnergy = Penguins::player->getEnergyUpdate();

		if(newEnergy) {
			collectedEnergy++;
			timer.Restart();
		}
	}
}

void UI::Render() {
	if (timer.Get() > 3) {
		firstExecution = false;
	}

	if ((newEnergy || timer.Get() <= 3) && !firstExecution) {
		textNewEnergy.Render();
	} else {
		std::stringstream sstmXp, sstmLife, sstmEnergy;
		sstmXp << "XP       " << this->xp;
		sstmLife << "Vida    " << this->life;
		sstmEnergy << "Energia   " << this->collectedEnergy << " de " << this->requiredEnergy;
		std::string stringXp = sstmXp.str();
		std::string stringLife = sstmLife.str();
		std::string stringEnergy = sstmEnergy.str();

		Text textXp("font/Call me maybe.ttf", 20, Text::BLENDED, stringXp, { 0, 0, 0 }, 100, 20);
		Text textLife("font/Call me maybe.ttf", 20, Text::BLENDED, stringLife, { 0, 0, 0 }, 100, 40);
		Text textEnergy("font/Call me maybe.ttf", 20, Text::BLENDED, stringEnergy, { 0, 0, 0 }, 430, 30);
		textXp.Render();
		textLife.Render();
		textEnergy.Render();
	}
}

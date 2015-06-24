#include "UI.h"

#include <sstream>
#include <string>

#include "Player.h"

const float lifeBackgroundX = 10;
const float lifeBackgroundY = 5;
const float r = 43;
const float initAngle = 98;
const float displacementXpUnit = 6.5;

UI::UI(int requiredEnergy, int collectedEnergy) :
		requiredEnergy(requiredEnergy),
		textNewEnergy("font/Call me maybe.ttf", 40, Text::BLENDED, "Energia recolhida!", { 0, 0, 0 }, 350, 250),
		timer(), bgLifeBackground("img/life_background.png"), bgLifeUnit("img/life_unit.png"),
		bgLifeHeart("img/life_heart.png"), bgXpBackground("img/xp_background.png"),
		bgXpUnit("img/xp_unit.png") {
	this->xp = 0;
	this->life = 0;
	this->collectedEnergy = collectedEnergy;
	this->newEnergy = false;
	this->firstExecution = true;
	this->centerX = lifeBackgroundX + (bgLifeBackground.GetWidth()/2);
	this->centerY = lifeBackgroundY + (bgLifeBackground.GetHeight()/2);
	this->xpUnitConstant = lifeBackgroundX + bgLifeBackground.GetWidth() + 28;
}

void UI::Update(float dt) {
	timer.Update(dt);

	if (Player::player != NULL) {
		this->xp = Player::player->GetXp();
		if(xp > 100) {
			xp = 100;
		}

		this->life = Player::player->GetHp();
		if(life > 100) {
			life = 100;
		}

		newEnergy = Player::player->GetEnergyUpdate();

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
		//std::stringstream sstmXp, sstmEnergy;
		//sstmXp << "XP       " << this->xp;
		//sstmEnergy << "Energia   " << this->collectedEnergy << " de " << this->requiredEnergy;
		//std::string stringXp = sstmXp.str();
		//std::string stringEnergy = sstmEnergy.str();

		//Text textXp("font/Call me maybe.ttf", 20, Text::BLENDED, stringXp, { 0, 0, 0 }, 100, 20);
		//Text textEnergy("font/Call me maybe.ttf", 20, Text::BLENDED, stringEnergy, { 0, 0, 0 }, 430, 30);
		//textXp.Render();
		//textEnergy.Render();
	}

	bgLifeBackground.Render(lifeBackgroundX, lifeBackgroundY, 0);
	bgLifeHeart.Render(lifeBackgroundX, lifeBackgroundY, 0);

	float theta = 0;

	//Life bar
	for(int i = 1; i <= 2; i++) {
		float x = centerX - (bgLifeUnit.GetWidth()/2)  - r*cos(theta);
		float y = centerY - (bgLifeUnit.GetHeight()/2) - r*sin(theta);

		bgLifeUnit.Render(x, y, initAngle - theta);

		theta -= 13.5;
	}

	//Xp bar
	int numberOfUnits = ((int) xp/5) - 1;
	float y = lifeBackgroundY + 57;
	for(int i = 0; i <= numberOfUnits; i++) {
		float x = xpUnitConstant + i*displacementXpUnit;

		bgXpUnit.Render(x, y, 0);
	}
	bgXpBackground.Render(lifeBackgroundX + bgLifeBackground.GetWidth() - 10, lifeBackgroundY + 40, 0);

	//Energy bar
	//TODO

}

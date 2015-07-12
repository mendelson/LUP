#include "FinalState.h"

#include <SDL_keycode.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Camera.h"
#include "Enemy3.h"
#include "InputManager.h"
#include "Planet.h"
#include "Planta.h"
#include "Plataforma.h"
#include "Player.h"
#include "Point.h"
#include "Support.h"
#include "WeaponBroom.h"
#include "WeaponGun.h"
#include "WeaponSword.h"

FinalState::WeaponName_lazy FinalState::weapon;

FinalState::FinalState() :bg("img/BACKGROUND.png"), music("audio/stageState.ogg"), ui(3), changeWpCD() {
	quitRequested = false;
	srand((unsigned int) time(NULL));
	xBg = -1400;
	this->weapon = BROOM;


	GameObject* planet = new Planet(0,-150,"img/planetafase3.png","map/mapLastPlaneta.txt","map/mapSubida.txt",3);


	GameObject* planeta1 = new PlanetaFundo(-2*xBg,-200,planet,0,0,"img/planeta_rosa.png");
	objectArray.emplace_back(planeta1);

	GameObject* planeta2 = new PlanetaFundo(xBg,-200,planet,0,0,"img/planeta_amarelo.png");
	objectArray.emplace_back(planeta2);

	GameObject* cometa1 = new Cometa(-2*xBg,-200,planet,0,0,"img/estrela_cadente_azul.png");
	objectArray.emplace_back(cometa1);

	GameObject* cometa2 = new Cometa(xBg,-200,planet,0,0,"img/estrela_cadente.png");
	objectArray.emplace_back(cometa2);

	objectArray.emplace_back(planet);

	GameObject* energia1 = new Energia(500,0,planet,90,400,"img/ENERGIA_V1_2.png",4);
	objectArray.emplace_back(energia1);

	GameObject* energia2 = new Energia(500,0,planet,47,400,"img/ENERGIA_V1_2.png",4);
	objectArray.emplace_back(energia2);

	GameObject* energia3 = new Energia(500,0,planet,230,400,"img/ENERGIA_V1_2.png",4);
	objectArray.emplace_back(energia3);

	GameObject* nave = new Nave(500,0,planet,-89,150,"img/nave-desligada.png");
	objectArray.emplace_back(nave);

//	GameObject* laserEterno = new Laser(500,0,planet,-90,200,8,8);
//	objectArray.emplace_back(laserEterno);
//
//	GameObject* laser = new Laser(500,0,planet,240,200,1,8);
//	objectArray.emplace_back(laser);

	GameObject* player = new Player(0,0,planet);
	objectArray.emplace_back(player);
	Camera::Follow(player);

	GameObject* support = new Support(planet);
	objectArray.emplace_back(support);

	activeWeapon = new WeaponBroom("img/Sprites_Bracos_LUP.png");
	//GameObject* weapon = new WeaponSword("img/Sprites_Espada_LUP.png");
	objectArray.emplace_back(activeWeapon);

	//GameObject* tank = new EnemyTank(500, 0,planet,18,50);
	//objectArray.emplace_back(tank);
	GameObject* e3 = new Enemy3(500, 0,planet,18,0);
	objectArray.emplace_back(e3);


	//rotacaoPlaneta = 0;
	//raioPlaneta = 1000;

	//GameObject* alien = new Alien(512,300,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien);
	//GameObject* alien2 = new Alien(300,512,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien2);
	//GameObject* alien3 = new Alien(1000,1000,5,(rand()%5) + dd3);
	//objectArray.emplace_back(alien3);

}

void FinalState::Update(float dt) {
//	if(SDL_QuitRequested()){
//		quitRequested = true;
//	}

	changeWpCD.Update(dt);

	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		std::cout
				<< InputManager::GetInstance().GetMouseX() - Camera::pos.getX()
				<< std::endl;
		std::cout
				<< InputManager::GetInstance().GetMouseY() - Camera::pos.getY()
				<< std::endl;

	}

	if(InputManager::GetInstance().KeyPress(SDLK_d) && (changeWpCD.Get() > 0.5))
	{
		changeWpCD.Restart();
		if (activeWeapon->Is("WeaponBroom"))
		{
			activeWeapon = new WeaponSword("img/Sprites_Espada_LUP.png");
			this->weapon = SWORD; //Sword
		}
		else if (activeWeapon->Is("WeaponSword"))
		{
			activeWeapon = new WeaponGun("img/Sprites_Gun_LUP.png");
			this->weapon = GUN; //Gun
		}
		else if (activeWeapon->Is("WeaponGun"))
		{
			activeWeapon = new WeaponBroom("img/Sprites_Bracos_LUP.png");
			this->weapon = BROOM; //Broom
		}
		objectArray.emplace_back(activeWeapon);
	}

	float somaRotation = Player::player->somaRotation;
	//xBg += somaRotation;
	Camera::Update(dt);
	quitRequested = InputManager::GetInstance().QuitRequested();
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	UpdateArray(dt);
	ui.Update(dt);


	//verifica fim da fase
	if(Player::player->deveMudarDeFase){
		popRequested = true;
	}
}

void FinalState::Render() {
	bg.Render(xBg, 0);
	RenderArray();
	ui.Render();
}

FinalState::~FinalState() {
	objectArray.clear();
}

void FinalState::Pause() {
	music.Stop();

}

void FinalState::Resume() {
	//music.Play(-1);
}

FinalState::WeaponName_lazy FinalState::CheckWeapon()
{
	return weapon;
}

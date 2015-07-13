#include "StageState.h"

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

StageState::WeaponName_lazy StageState::weapon;

StageState::StageState() :bg("img/BACKGROUND.png"), music("audio/fase1.ogg"), ui(3), changeWpCD() {
	quitRequested = false;
	srand((unsigned int) time(NULL));
	xBg = -1400;
	this->weapon = BROOM;


	GameObject* planet = new Planet(0,-100,"img/planetafase1.png","map/mapPlaneta.txt","map/mapSubida.txt",1);


	GameObject* planeta1 = new PlanetaFundo(-2*xBg,-200,planet,0,0,"img/planeta_rosa.png");
	objectArray.emplace_back(planeta1);

	GameObject* planeta2 = new PlanetaFundo(xBg,-200,planet,0,0,"img/planeta_amarelo.png");
	objectArray.emplace_back(planeta2);

	GameObject* cometa1 = new Cometa(-2*xBg,-200,planet,0,0,"img/estrela_cadente_azul.png");
	objectArray.emplace_back(cometa1);

	GameObject* cometa2 = new Cometa(xBg,-200,planet,0,0,"img/estrela_cadente.png");
	objectArray.emplace_back(cometa2);

	objectArray.emplace_back(planet);

	GameObject* plataforma1 = new Plataforma(500,100,planet,-30,100,"img/plataformas/2200/plataformas2200_44.png");
	objectArray.emplace_back(plataforma1);

	GameObject* plataforma2 = new Plataforma(500,0,planet,-25,150,"img/plataformas/2200/plataformas2200_39.png");
	objectArray.emplace_back(plataforma2);

	GameObject* plataforma3 = new Plataforma(500,0,planet,-20,200,"img/plataformas/2200/plataformas2200_13.png");
	objectArray.emplace_back(plataforma3);

	GameObject* plataforma4 = new Plataforma(500,0,planet,-15,250,"img/plataformas/2200/plataformas2200_50.png");
	objectArray.emplace_back(plataforma4);

	GameObject* planta1 = new Planta(500,0,planet,-1,50,"img/plataformas/2200/planta.png");
	objectArray.emplace_back(planta1);

	GameObject* planta2 = new Planta(500,0,planet,39,50,"img/plataformas/2200/planta.png");
	objectArray.emplace_back(planta2);

	GameObject* plataforma5 = new Plataforma(500,0,planet,47,200,"img/plataformas/2200/plataformas2200_15.png");
	objectArray.emplace_back(plataforma5);

	GameObject* planta3 = new Planta(500,0,planet,53,50,"img/plataformas/2200/planta.png");
	objectArray.emplace_back(planta3);

	GameObject* plataforma6 = new Plataforma(500,0,planet,75,150,"img/plataformas/2200/plataformas2200_03.png");
	objectArray.emplace_back(plataforma6);

	GameObject* plataforma7 = new Plataforma(500,0,planet,80,220,"img/plataformas/2200/plataformas2200_05.png");
	objectArray.emplace_back(plataforma7);

	GameObject* plataforma9 = new Plataforma(500,0,planet,85,280,"img/plataformas/2200/plataformas2200_17.png");
	objectArray.emplace_back(plataforma9);

	GameObject* plataforma10 = new Plataforma(500,0,planet,90,330,"img/plataformas/2200/plataformas2200_21.png");
	objectArray.emplace_back(plataforma10);

	GameObject* plataforma11 = new Plataforma(500,0,planet,95,330,"img/plataformas/2200/plataformas2200_19.png");
	objectArray.emplace_back(plataforma11);

	GameObject* plataforma12 = new Plataforma(500,0,planet,100,310,"img/plataformas/2200/plataformas2200_47.png");
	objectArray.emplace_back(plataforma12);

	GameObject* plataforma13 = new Plataforma(500,0,planet,105,250,"img/plataformas/2200/plataformas2200_10.png");
	objectArray.emplace_back(plataforma13);

	GameObject* plataforma14 = new Plataforma(500,0,planet,140,150,"img/plataformas/2200/plataformas2200_23.png");
	objectArray.emplace_back(plataforma14);

	GameObject* plataforma15 = new Plataforma(500,0,planet,150,150,"img/plataformas/2200/plataformas2200_08.png");
	objectArray.emplace_back(plataforma15);

	GameObject* plataforma16 = new Plataforma(500,0,planet,170,150,"img/plataformas/2200/plataformas2200_35.png");
	objectArray.emplace_back(plataforma16);

	GameObject* plataforma17 = new Plataforma(500,0,planet,175,150,"img/plataformas/2200/plataformas2200_19.png");
	objectArray.emplace_back(plataforma17);

	GameObject* plataforma18 = new Plataforma(500,0,planet,180,150,"img/plataformas/2200/plataformas2200_37.png");
	objectArray.emplace_back(plataforma18);

	GameObject* plataforma19 = new Plataforma(500,0,planet,218,150,"img/plataformas/2200/plataformas2200_15.png");
	objectArray.emplace_back(plataforma19);

	GameObject* planta4 = new Planta(500,0,planet,221.5,50,"img/plataformas/2200/planta.png");
	objectArray.emplace_back(planta4);

	GameObject* plataforma20 = new Plataforma(500,0,planet,224,200,"img/plataformas/2200/plataformas2200_41.png");
	objectArray.emplace_back(plataforma20);

	GameObject* planta5 = new Planta(500,0,planet,226.5,50,"img/plataformas/2200/planta.png");
	objectArray.emplace_back(planta5);

	GameObject* plataforma21 = new Plataforma(500,0,planet,230,150,"img/plataformas/2200/plataformas2200_41.png");
	objectArray.emplace_back(plataforma21);

	GameObject* plataforma22 = new Plataforma(500,0,planet,230,250,"img/plataformas/2200/plataformas2200_41.png");
	objectArray.emplace_back(plataforma22);

	GameObject* planta6 = new Planta(500,0,planet,231,50,"img/plataformas/2200/planta.png");
	objectArray.emplace_back(planta6);

	GameObject* plataforma23 = new Plataforma(500,0,planet,236,200,"img/plataformas/2200/plataformas2200_41.png");
	objectArray.emplace_back(plataforma23);

	GameObject* planta7 = new Planta(500,0,planet,236,50,"img/plataformas/2200/planta.png");
	objectArray.emplace_back(planta7);

	GameObject* plataforma24 = new Plataforma(500,0,planet,240,150,"img/plataformas/2200/plataformas2200_15.png");
	objectArray.emplace_back(plataforma24);

	GameObject* energia1 = new Energia(500,0,planet,90,400,"img/ENERGIA_V1.png",4);
	objectArray.emplace_back(energia1);

	GameObject* energia2 = new Energia(500,0,planet,47,400,"img/ENERGIA_V1.png",4);
	objectArray.emplace_back(energia2);

	GameObject* energia3 = new Energia(500,0,planet,230,400,"img/ENERGIA_V1.png",4);
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

	GameObject* tank1 = new EnemyTank(500, 0,planet,-50,50);
	objectArray.emplace_back(tank1);

	GameObject* tank2 = new EnemyTank(500, 0,planet,-40,50);
	objectArray.emplace_back(tank2);

	GameObject* tank3 = new EnemyTank(500, 0,planet,-30,50);
	objectArray.emplace_back(tank3);

	GameObject* tank4 = new EnemyTank(500, 0,planet,45,50);
	objectArray.emplace_back(tank4);

	GameObject* tank5 = new EnemyTank(500, 0,planet,140,50);
	objectArray.emplace_back(tank5);

	GameObject* tank6 = new EnemyTank(500, 0,planet,150,50);
	objectArray.emplace_back(tank6);

	GameObject* tank7 = new EnemyTank(500, 0,planet,160,50);
	objectArray.emplace_back(tank7);

	GameObject* tank8 = new EnemyTank(500, 0,planet,170,50);
	objectArray.emplace_back(tank8);

	GameObject* tank9 = new EnemyTank(500, 0,planet,180,50);
	objectArray.emplace_back(tank9);

	GameObject* tank10 = new EnemyTank(500, 0,planet,190,50);
	objectArray.emplace_back(tank10);



	//rotacaoPlaneta = 0;
	//raioPlaneta = 1000;

	//GameObject* alien = new Alien(512,300,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien);
	//GameObject* alien2 = new Alien(300,512,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien2);
	//GameObject* alien3 = new Alien(1000,1000,5,(rand()%5) + dd3);
	//objectArray.emplace_back(alien3);
	music.Play(-1);

}

void StageState::Update(float dt) {
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
		Player::player->deveMudarDeFase = false;
	}
}

void StageState::Render() {
	if(Player::player->GetHp() <= 0 && Player::player->deathAnimation.Get() > 1.4)
	{
		Sprite* black = new Sprite("img/blank.png");
		black->Render(0,0);
		delete black;
		return;
	}

	bg.Render(xBg, 0);
	RenderArray();
	ui.Render();
}

StageState::~StageState() {
	objectArray.clear();
}

void StageState::Pause() {
	music.Stop();
	objectArray.clear();

}

void StageState::Resume() {
	music.Play(-1);

}

StageState::WeaponName_lazy StageState::CheckWeapon()
{
	return weapon;
}

/*
 * Penguins.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */

#include "Penguins.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Bullet.h"

Penguins* Penguins::player=NULL;

Penguins::Penguins(float x,float y): bodySp("img/penguin.png"),cannonSp("img/cubngun.png"),speed(),timer(){
	int novox = x - (bodySp.GetWidth()/2);
	int novoy = y - (bodySp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(bodySp.GetHeight());
	box.setW(bodySp.GetWidth());
	linearSpeed = 0;
	cannonAngle = 0;
	hp = 30;
	player = this;
	pulando = false;
	posInicial = y;
}

Penguins::~Penguins(){
	player = NULL;
}

void Penguins::Update(float dt){
	timer.Update(dt);
	float speedWalk = 20;
	float gravity = 500;
	float floorHeight = Game::GetInstance().GetCurrentState().getTileMapHeight(box.getX());
	float posX = InputManager::GetInstance().GetMouseX() - Camera::pos.getX();
	float posY = InputManager::GetInstance().GetMouseY() - Camera::pos.getY();
	float proxHeight = Game::GetInstance().GetCurrentState().getTileMapHeight(box.getX() + speedWalk);
	float antHeight = Game::GetInstance().GetCurrentState().getTileMapHeight(box.getX()- speedWalk);
	/*if(InputManager::GetInstance().IsKeyDown(SDLK_w) && box.getY() >= 250){
		pulando = true;
		posInicial = box.getY();
	}*/
	if(InputManager::GetInstance().IsKeyDown(SDLK_a) ){
		box.setX(box.getX() - speedWalk);
	}
	if(InputManager::GetInstance().IsKeyDown(SDLK_d)){
		box.setX(box.getX() + speedWalk);
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_s)){
		box.setY(box.getY() + speedWalk);
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_w)){
			box.setY(box.getY() - speedWalk);
		}

//	if(pulando == true){
//		if((posInicial - box.getY()) < 150){
//			box.setY(box.getY() - 2*gravity*dt);
//		}else{
//			pulando = false;
//		}
//	}else{
//		if(box.getY() < floorHeight && floorHeight != 0){
//			box.setY(box.getY() + gravity*dt);
//		}
//		if(box.getY() > floorHeight){
//				box.setY(floorHeight);
//		}
//	}


	if(box.getX() <= 324){
		box.setX(1920);
	}
	if(box.getX() >= 3523){
		box.setX(1920);
	}

	/*Point* pspeed = new Point(box.getCenterX() - posX,box.getCenterY() - posY);
	speed = *pspeed;
	cannonAngle = atan(speed.getY()/speed.getX());
	if(speed.getX() > 0){
		cannonAngle += 3.141592653;
	}
	if(InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) && timer.Get() > 1){
		timer.Restart();
		Shoot();
	}
	if(box.getX() >= 0 && box.getX() <= 1480){
		box.setX(box.getX() + linearSpeed*dt*cos(rotation));
	}
	if(box.getY() >= 0 && box.getY() <= 1280){
		box.setY(box.getY() + linearSpeed*dt*sin(rotation));
	}

	if(box.getX() < 0){
		box.setX(0);
	}else if(box.getX() > 1480){
		box.setX(1480);
	}

	if(box.getY() < 0){
		box.setY(0);
	}else if(box.getY() > 1280){
		box.setY(1280);
	}*/

}

void Penguins::Render(){
	float angulo = rotation*180/3.141592653;
	bodySp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY(),angulo);
	angulo = cannonAngle*180/3.141592653;
	cannonSp.Render(box.getX() +  Camera::pos.getX() ,box.getY() +  Camera::pos.getY() ,angulo);
}


void Penguins::Shoot(){
	float fspeed = speed.magVector() + linearSpeed;
	Bullet* bullet = new Bullet((float)box.getCenterX()+(cannonSp.GetWidth()*cos(cannonAngle)/2),(float)box.getCenterY() + (cannonSp.GetHeight()*sin(cannonAngle)/2),cannonAngle,fspeed,2000.0,"img/penguinbullet.png",false,4);
	Game::GetInstance().GetCurrentState().AddObject(bullet);
}

bool Penguins::Is(string type){
	return (type == "Penguins");
}

void Penguins::NotifyCollision(GameObject& other){
	if(other.Is("Bullet")){
		Bullet& bull = dynamic_cast<Bullet&>(other);
		if ( bull.targetsPlayer){
			hp-= (rand()%9 + 1);
			if(IsDead()){
							Sprite* sp = new Sprite("img/penguindeath.png",5,0.3);
							StillAnimation* animacao = new StillAnimation(box.getCenterX(),box.getCenterY(),rotation,*sp,0.3*5,true);
							Game::GetInstance().GetCurrentState().AddObject(animacao);
							Sound* sound = new Sound("audio/boom.wav");
							sound->Play(0);
							Camera::Unfollow();
							Game::GetInstance().GetCurrentState().SetPopRequested(true);
							StateData* stateData = new StateData();
							stateData->playerVictory = false;
							State* state = new EndState(*stateData);
							Game::GetInstance().Push(state);

			}
		}

	}

}

bool Penguins::IsDead(){
	if (hp<=0){
		return true;
	}
	return false;
}


Sprite Penguins::getSprite(){
	return bodySp;
}

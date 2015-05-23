/*
 * Player.cpp
 *
 *  Created on: 22/05/2015
 *      Author: Vitor
 */
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"

Player* Player::player = NULL;

Player::Player(float x, float y): bodySp("img/penguin.png"),speed(),timer(){
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
}

Player::~Player(){
	player = NULL;
}


void Player::Update(float dt){
	timer.Update(dt);
	/*float distAPercorrer = 1;

	if(InputManager::GetInstance().IsKeyDown(SDLK_a)){
		box.setX(box.getX() - distAPercorrer);
	}
	if(InputManager::GetInstance().IsKeyDown(SDLK_d)){
		box.setX(box.getX() + distAPercorrer);
	}

	//gravidade
	while(box.getY() < 450){
		box.setY(box.getY() + dt);
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_w)){
		box.setY(box.getY() + 100);
	}*/
}

void Player::Render(){
	bodySp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY());
}


bool Player::Is(string type){
	return (type == "Player");
}
bool Player::IsDead(){
	if (hp<=0){
		return true;
	}
	return false;
}


Sprite Player::getSprite(){
	return bodySp;
}

void Player::NotifyCollision(GameObject& other){
}

/*
 * Camera.cpp
 *
 *  Created on: 08/04/2015
 *      Author: Vitor
 */

#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

GameObject* Camera::focus = NULL;
Point Camera::pos;
Point Camera::speed;

void Camera::Follow(GameObject* newFocus){
	focus = newFocus;
}

void Camera::Unfollow(){
	focus = NULL;
}

void Camera::Update(float dt){

	if(focus == NULL){
		speed.setX(0);
		speed.setY(0);
		if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
			speed.setX( - Game::GetInstance().GetDeltaTime());
		}
		if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
			speed.setX(Game::GetInstance().GetDeltaTime());
		}
		if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
			speed.setY( - Game::GetInstance().GetDeltaTime());
		}
		if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
			speed.setY( Game::GetInstance().GetDeltaTime());
		}
		speed.vetMultEscalar(500);
		pos.somaPonto(speed);
	}else{

		pos.setX((Game::GetInstance().getWidth()/2) - focus->box.getCenterX());
		pos.setY((Game::GetInstance().getHeight()/2) - focus->box.getCenterY());
	}
}

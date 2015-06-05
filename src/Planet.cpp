/*
 * Planet.cpp
 *
 *  Created on: 05/06/2015
 *      Author: Vitor
 */

#include "Planet.h"
#include "InputManager.h"
#include "Camera.h"

Planet::Planet(float x, float y,string file):sp(file) {
	int novox = x - (sp.GetWidth()/2);
	int novoy = y;
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = 0;
	float scale;
}

Planet::~Planet() {
	// TODO Auto-generated destructor stub
}

void Planet::Update(float dt){
	if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
	{
		rotation += 18*dt;
	}
	else if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
	{
		rotation -= 18*dt;
	}
}

void Planet::Render(){
	sp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation);
}


bool Planet::IsDead(){
	return false;
}

bool Planet::Is(string type){
	return type == "Planet";
}

Sprite Planet::getSprite(){
	return sp;
}

void Planet::NotifyCollision(GameObject& object){

}

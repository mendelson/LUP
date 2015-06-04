/*
 * Plataforma1.cpp
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#include "Plataforma1.h"
#include "Camera.h"
#include "Game.h"

Plataforma1::Plataforma1(float x,float y,float rotation):body("img/plataforma1.png") {
	initBox.x = x;
	initBox.y = y;
	initRotation = rotation;
	box.x = x;
	box.y = y;
	this->rotation = rotation;

}

Plataforma1::~Plataforma1() {
	// TODO Auto-generated destructor stub
}

void Plataforma1::Update(float dt){
	box.x = initBox.x + Game::GetInstance().GetCurrentState().raioPlaneta*cos(Camera::rotation*3.14/180);
	box.y = initBox.y + Game::GetInstance().GetCurrentState().raioPlaneta*sin(Camera::rotation*3.14/180);
}

void Plataforma1::Render(){
	body.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY());
}

bool Plataforma1::IsDead(){
	return false;
}

Sprite Plataforma1::getSprite(){
	return body;
}

void Plataforma1::NotifyCollision(GameObject&){

}

bool Plataforma1::Is(string type){
	return (type == "Plataforma1");
}

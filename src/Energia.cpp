/*
 * Energia.cpp
 *
 *  Created on: 28/06/2015
 *      Author: Vitor
 */

#include "Energia.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Energia::Energia(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file):sp(file) {
	this->planet = planet;

	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->alturaInicial = alturaInicial;
	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY() + alturaInicial)*sin(arc)) - (box.getH()/2));
	dead = false;

}

Energia::~Energia() {
	//delete(&sp);
}

void Energia::Update(float dt){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;

		float arc = rotation*3.1415/180;
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));
}

void Energia::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation + 90);
}

bool Energia::IsDead(){
	return dead;
}

Sprite Energia::getSprite(){
	return sp;
}

void Energia::NotifyCollision(GameObject& other){
	if (other.Is("Player"))
		{
			dead = true;
		}
}

bool Energia::Is(string type){
	return (type == "Energia");
}

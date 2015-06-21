/*
 * Planta.cpp
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#include "Planta.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Planta::Planta(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file):sp(file) {
	this->planet = planet;

	box.x = x;int novox = x - (sp.GetFrameWidth() / 2);
	int novoy = y - (sp.GetHeight() / 2);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->alturaInicial = alturaInicial;
	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY() + alturaInicial)*sin(arc)) - (box.getH()/2));


}

Planta::~Planta() {
	// TODO Auto-generated destructor stub
}

void Planta::Update(float dt){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;

		float arc = rotation*3.1415/180;
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));
}

void Planta::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation + 90);
}

bool Planta::IsDead(){
	return false;
}

Sprite Planta::getSprite(){
	return sp;
}

void Planta::NotifyCollision(GameObject&){

}

bool Planta::Is(string type){
	return (type == "Planta");
}

/*
 * Nave.cpp
 *
 *  Created on: 11/07/2015
 *      Author: Vitor
 */

#include "Nave.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Nave::Nave(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file):sp(file) {
	this->planet = planet;

	box.x = x;//int novox = x - (sp.GetFrameWidth() / 2);
	//int novoy = y - (sp.GetHeight() / 2);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->alturaInicial = alturaInicial;
	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY() + alturaInicial)*sin(arc)) - (box.getH()/2));


}

Nave::~Nave() {
	// TODO Auto-generated destructor stub
}

void Nave::Update(float dt){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;

		float arc = rotation*3.1415/180;
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));
}

void Nave::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation + 90);
}

bool Nave::IsDead(){
	return false;
}

Sprite Nave::getSprite(){
	return sp;
}

void Nave::NotifyCollision(GameObject&){

}

bool Nave::Is(string type){
	return (type == "Nave");
}

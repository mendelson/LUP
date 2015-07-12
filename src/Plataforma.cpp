/*
 * Plataforma1.cpp
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#include "Plataforma.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Plataforma::Plataforma(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file,int fase):sp(file) {
	this->planet = planet;

	box.x = x;//int novox = x - (sp.GetFrameWidth() / 2);
	//int novoy = y - (sp.GetHeight() / 2);
	if(fase > 1){
		sp.SetScaleX(0.3);
		sp.SetScaleY(0.3);
	}
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->alturaInicial = alturaInicial;
	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY() + alturaInicial)*sin(arc)) - (box.getH()/2));


}

Plataforma::~Plataforma() {
	// TODO Auto-generated destructor stub
}

void Plataforma::Update(float dt){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;

		float arc = rotation*3.1415/180;
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));
}

void Plataforma::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation + 90);
}

bool Plataforma::IsDead(){
	return false;
}

Sprite Plataforma::getSprite(){
	return sp;
}

void Plataforma::NotifyCollision(GameObject&){

}

bool Plataforma::Is(string type){
	return (type == "Plataforma");
}

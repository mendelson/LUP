/*
 * PontaLaser.cpp
 *
 *  Created on: 12/07/2015
 *      Author: Vitor
 */

#include "PontaLaser.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

PontaLaser::PontaLaser(float x,float y,GameObject* planet, float rotation,float alturaInicial,int d):sp("img/laser.png",0,2,8) {
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
	sp.SetFlipH(false);
	sp.SetFrame(0);
	sp.SetLoop(0,0);
	sp.Update(0);
	this->d = d;

}

PontaLaser::~PontaLaser() {
	// TODO Auto-generated destructor stub
}

void PontaLaser::Update(float dt){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;

		float arc = rotation*3.1415/180;
		box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
		box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));
}

void PontaLaser::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation + 90 + d);
}

bool PontaLaser::IsDead(){
	return false;
}

Sprite PontaLaser::getSprite(){
	return sp;
}

void PontaLaser::NotifyCollision(GameObject&){

}

bool PontaLaser::Is(string type){
	return (type == "PontaLaser");
}

/*
 * PlanetaFundo.cpp
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#include "PlanetaFundo.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

PlanetaFundo::PlanetaFundo(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file):sp(file) {
	this->planet = planet;
	box.x = x;
	box.y = y;
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->alturaInicial = alturaInicial;
	initialX = x;


}

PlanetaFundo::~PlanetaFundo() {
	// TODO Auto-generated destructor stub
}

void PlanetaFundo::Update(float dt){
	somaRotation = planet->somaRotation;
	box.x += somaRotation;
	if(box.x > 4000 || box.x < -4000){
			box.x = initialX;
	}
}

void PlanetaFundo::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation);
}

bool PlanetaFundo::IsDead(){
	return false;
}

Sprite PlanetaFundo::getSprite(){
	return sp;
}

void PlanetaFundo::NotifyCollision(GameObject&){

}

bool PlanetaFundo::Is(string type){
	return (type == "PlanetaFundo");
}

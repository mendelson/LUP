/*
 * Cometa.cpp
 *
 *  Created on: 09/07/2015
 *      Author: Vitor
 */

#include "Cometa.h"
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

Cometa::Cometa(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file):sp(file) {
	this->planet = planet;
	box.x = x;
	initialX = x;
	box.y = y;
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	this->rotation = rotation;
	this->alturaInicial = alturaInicial;


}

Cometa::~Cometa() {
	// TODO Auto-generated destructor stub
}

void Cometa::Update(float dt){
	somaRotation = planet->somaRotation;
	box.x += 10*somaRotation;
	if(box.x > 4000 || box.x < -4000){
		box.x = initialX;
	}
}

void Cometa::Render(){
	sp.Render(box.getX() + Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation);
}

bool Cometa::IsDead(){
	return false;
}

Sprite Cometa::getSprite(){
	return sp;
}

void Cometa::NotifyCollision(GameObject&){

}

bool Cometa::Is(string type){
	return (type == "PlanetaFundo");
}

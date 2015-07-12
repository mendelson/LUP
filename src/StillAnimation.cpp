/*
 * StillAnimation.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */

#include "StillAnimation.h"

#include <cmath>
#include <string>

#include "Camera.h"
#include "Point.h"
#include "Sprite.h"


StillAnimation::StillAnimation(float x, float y, GameObject* planet,float rotation,Sprite sprite,float timeLimit,bool ends, float alturaInicial):endTimer(){
	sp = sprite;
	this->timeLimit = timeLimit;
	this->planet = planet;
	oneTimeOnly = ends;
	this->rotation = rotation;
	float arc = rotation*3.1415/180;
	this->alturaInicial = alturaInicial;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY()  + alturaInicial)*sin(arc)) - (box.getH()/2));
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	std::cout << "TESTE STILL\n";
}

void StillAnimation::Update(float dt){
	somaRotation = planet->somaRotation;
	rotation += somaRotation;
	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));

	sp.Update(dt);
	endTimer.Update(dt);
}

void StillAnimation::Render(){
	sp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY());
}

bool StillAnimation::IsDead(){
	if(oneTimeOnly){
		if(endTimer.Get() > timeLimit){
			return true;
		}
	}
	return false;
}

void StillAnimation::NotifyCollision(GameObject& other){

}

bool StillAnimation::Is(string type){
	return (type == "StillAnimation");
}

Sprite StillAnimation::getSprite(){
	return sp;
}

/*
 * StillAnimation.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */

#include "StillAnimation.h"
#include "Camera.h"


StillAnimation::StillAnimation(float x, float y,float rotation,Sprite sprite,float timeLimit,bool ends):endTimer(){
	sp = sprite;
	this->timeLimit = timeLimit;
	oneTimeOnly = ends;
	this->rotation = rotation;
	int novox = x - (sp.GetFrameWidth()/2);
	int novoy = y - (sp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
}

void StillAnimation::Update(float dt){
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

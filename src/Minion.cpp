/*
 * Minion.cpp
 *
 *  Created on: 15/04/2015
 *      Author: Vitor
 */

#include "Minion.h"
#include "Game.h"
#include "Camera.h"
Minion::Minion(GameObject* minionCenter,float arcOffset) : sp("img/minion.png"){

	center = minionCenter;
	arc = arcOffset;
	rotation = (arc*180/3.141592653)-180;
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	box.setX(center->box.getCenterX() + (200*cos(arc)) - (box.getW()/2));
	box.setY(center->box.getCenterY()  + (200*sin(arc)) - (box.getH()/2));
	float scale = (((rand())%50)+100)/100.0;
	sp.SetScaleX(scale);
	sp.SetScaleY(scale);
}


void Minion::Update(float dt){
	arc += 0.3141592653*dt;
	rotation = (arc*180/3.141592653)-180;
	float x = center->box.getCenterX() + (100*cos(arc)) - (box.getW()/2);
	float y = center->box.getCenterY()  + (100*sin(arc)) - (box.getH()/2);
	box.setX(x);
	box.setY(y);
}

void Minion::Render(){
	sp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation);
}

bool Minion::IsDead(){
	return false;
}

void Minion::Shoot(Point pos){
	Point* pspeed = new Point(box.getCenterX() - pos.getX(),box.getCenterY() - pos.getY());
	//float speed = pspeed->magVector();
	float angle = atan(pspeed->getY()/pspeed->getX());
	if(pspeed->getX() > 0){
		angle += 3.141592653;
	}
	delete(pspeed);
	//Bullet* bullet = new Bullet(box.getCenterX(),box.getCenterY(),angle,speed,2000,"img/minionBullet2.png",true,3);
	//Game::GetInstance().GetCurrentState().AddObject(bullet);
}

Sprite Minion::getSprite(){
	return sp;
}

bool Minion::Is(string type){
	return (type == "Minion");
}

void Minion::NotifyCollision(GameObject& other){
	//center->NotifyCollision(other);
}

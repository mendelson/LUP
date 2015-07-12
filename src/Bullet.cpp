#include "Bullet.h"
#include "Camera.h"

#include <cmath>
#include <iostream>
#include <string>

Bullet::Bullet(GameObject* planet, float initialRotation, float alturaInicial, float speed, float maxDistance, string Sprite, bool targetsPlay, int frameCount) : sp(Sprite,0.1,1,frameCount){

	this->planet = planet;
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = initialRotation;
	float arc = rotation*3.1415/180;
	this->alturaInicial = alturaInicial;
	std::cout << "AlturaInicial: " << this->alturaInicial << std::endl;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial+100)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY()  + alturaInicial+100)*sin(arc)) - (box.getH()/2));
	distanceLeft = maxDistance;
	targetsPlayer = targetsPlay;

	sp.SetLoop(0, 4);

	Sound* sound = new Sound("audio/projetil.wav");
	sound->Play(0);
	delete(sound);
}

void Bullet::Update(float dt){
	rotation += 5*dt;

	somaRotation = planet->somaRotation;
	rotation += somaRotation;

	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial+100)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY()  + alturaInicial+100)*sin(arc)) - (box.getH()/2));
	//std::cout << "AlturaInicial: " << alturaInicial << std::endl;

	sp.Update(dt);
}

void Bullet::Render(){
	//float correctedAngle = angle*180/3.141592653;
	//sp.Render(box.getX()+Camera::pos.getX(),box.getY() + Camera::pos.getY(),correctedAngle);
	sp.Render(box.getX() + Camera::pos.getX(), box.getY() + Camera::pos.getY(),rotation + 90);
}

bool Bullet::IsDead(){
	if(distanceLeft <= 0){
		return true;
	}
	return false;
}

Sprite Bullet::getSprite(){
	return sp;
}

bool Bullet::Is(string type){
	return (type == "Bullet");
}

void Bullet::NotifyCollision(GameObject& other){
	if(other.Is("Player")){
		distanceLeft = 0;
	}
}

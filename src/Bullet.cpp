#include "Bullet.h"
#include "Camera.h"

Bullet::Bullet(float x,float y,GameObject* planet, float angle, float alturaIncial, float speed, float maxDistance, string Sprite,bool targetsPlay,int frameCount):sp(Sprite,0.1,1,frameCount){

	this->planet = planet;
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = angle;
	float arc = rotation*3.1415/180;
	this->alturaInicial = alturaInicial;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY()  + alturaInicial)*sin(arc)));

	box.setX(x - sp.GetWidth()/2);
	box.setY(y - sp.GetHeight()/2);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	float coord = speed/sqrt(2);
	Point* aux = new Point(coord,coord);
	this->speed = *aux;
	distanceLeft = maxDistance;
	this->angle = angle;
	targetsPlayer = targetsPlay;
	Sound* sound = new Sound("audio/projetil.wav");
	sound->Play(0);
	delete(sound);
}

void Bullet::Update(float dt){
	box.setX(box.getX() + (dt*speed.magVector()*cos(angle)));
	box.setY(box.getY() + (dt*speed.magVector()*sin(angle)));
	distanceLeft -= speed.magVector()*dt;
	sp.Update(dt);
}

void Bullet::Render(){
	float correctedAngle = angle*180/3.141592653;
	sp.Render(box.getX()+Camera::pos.getX(),box.getY() + Camera::pos.getY(),correctedAngle);
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

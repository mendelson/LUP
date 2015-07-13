/*
 * Planet.cpp
 *
 *  Created on: 05/06/2015
 *      Author: Vitor
 */

#include "Planet.h"
#include "InputManager.h"
#include "Camera.h"

Planet::Planet(float x, float y,string file,string mapaPlaneta,string mapaSubida,int nPlaneta):sp(file) {
	int novox = x - (sp.GetWidth()/2);
	int novoy = y;
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = 0;
	FILE* fp;
	fp = fopen(mapaPlaneta.c_str(),"r");
	for(int i=0;i<361;i++){
		fscanf(fp,"%d,",&offsetALtura[i]);
	}
	FILE* f;
	f = fopen(mapaSubida.c_str(),"r");
	for(int i=0;i<361;i++){
		fscanf(f,"%d,",&mapaSubida[i]);
	}
	this->nPlaneta = nPlaneta;
	fclose(fp);
	fclose(f);
	free(fp);
	free(f);
}

Planet::~Planet() {
	// TODO Auto-generated destructor stub
}

void Planet::Update(float dt){
		somaRotation = Player::player->somaRotation;
		rotation += somaRotation;
		while(rotation > 360){
				rotation -= 360;
		}
		while(rotation <0 ){
				rotation += 360;
		}
}

void Planet::Render(){
	sp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation);
}


bool Planet::IsDead(){
	return false;
}

bool Planet::Is(string type){
	return type == "Planet";
}

Sprite Planet::getSprite(){
	return sp;
}

void Planet::NotifyCollision(GameObject& object){

}

int Planet::getAltura(float rotation){
	while(rotation < 0) rotation += 360;

	while (rotation > 360) rotation  -= 360;

	int auxrotation = ((int ) rotation) % 360;
	return -offsetALtura[auxrotation] + Player::player->getSprite().GetHeight();
}

bool Planet::podeSubir(float rotation){
	while(rotation < 0) rotation += 360;

	while (rotation > 360) rotation  -= 360;
	int auxrotation = ((int ) rotation) % 360;
	if(mapaSubida[auxrotation] == 1)
		return true;
	return false;

}

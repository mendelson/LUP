/*
 * Planet.h
 *
 *  Created on: 05/06/2015
 *      Author: Vitor
 */

#ifndef SRC_PLANET_H_
#define SRC_PLANET_H_
#include "GameObject.h"
#include "Sprite.h"
#include "Player.h"
#include<iostream>
#include<stdio.h>

class Planet : public GameObject{
public:
	Planet(float x, float y,string file,string mapaPlaneta,string mapaSubida,int nPlaneta);
	~Planet();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
	int getAltura(float rotation);
	bool podeSubir(float rotation);
private:
	Sprite sp;
	int offsetALtura[361];
	int mapaSubida[361];
};

#endif /* SRC_PLANET_H_ */

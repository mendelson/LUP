/*
 * LaserDeitadoDeitado.h
 *
 *  Created on: 12/07/2015
 *      Author: Vitor
 */

#ifndef SRC_LaserDeitadoDEITADO_H_
#define SRC_LaserDeitadoDEITADO_H_

#include "GameObject.h"
#include "Timer.h"


class LaserDeitado : public GameObject{
public:
	LaserDeitado(float x,float y,GameObject* planet, float rotation,float alturaInicial,int frameI,int frameC);
	~LaserDeitado();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	void NotifyCollision(GameObject&);
	bool Is(string type);
private:
	Sprite sp;
	GameObject* planet;
	float alturaInicial;
	Timer timer;
	int frameCarregado;
	int frameInit;

};
#endif /* SRC_LaserDeitadoDEITADO_H_ */

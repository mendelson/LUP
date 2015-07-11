/*
 * PlataformaOfensiva.h
 *
 *  Created on: 03/06/2015
 *      Author: Vitor
 */

#ifndef SRC_PLATAFORMA_OFENSIVA_H_
#define SRC_PLATAFORMA_OFENSIVA_H_

#include "GameObject.h"

class PlataformaOfensiva : public GameObject{
public:
	PlataformaOfensiva(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file);
	~PlataformaOfensiva();
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

};

#endif /* SRC_PLATAFORMA_OFENSIVA_H_ */

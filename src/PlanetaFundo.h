/*
 * PlanetaFundo.h
 *
 *  Created on: 09/07/2015
 *      Author: Vitor
 */

#ifndef SRC_PLANETAFUNDO_H_
#define SRC_PLANETAFUNDO_H_

#include "GameObject.h"

class PlanetaFundo : public GameObject{
public:
	PlanetaFundo(float x,float y,GameObject* planet, float rotation,float alturaInicial, string file);
	~PlanetaFundo();
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
	float initialX;

};
#endif /* SRC_PLANETAFUNDO_H_ */

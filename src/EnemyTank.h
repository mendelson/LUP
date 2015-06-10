#ifndef SRC_ENEMYTANK_H_
#define SRC_ENEMYTANK_H_

#include "Sprite.h"
#include "Point.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"

class EnemyTank: public GameObject {
public:
	EnemyTank(float x, float y,GameObject* planet, float initialRotation, float alturaIncial);
	~EnemyTank();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
	void Move(Point dest);
private:
	Sprite sp;
	Point speed;
	Point startPos;
	int hp;
	Timer dmgCD;
	Facing orientation;
	GameObject* planet;
	float alturaInicial;
	Timer knockback;
	Facing kbDirection;
};

#endif /* SRC_ENEMYTANK_H_ */

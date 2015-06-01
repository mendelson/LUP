#ifndef TRAB_ENEMYTANK_H_
#define TRAB_ENEMYTANK_H_
#include "Sprite.h"
#include "Point.h"
#include "GameObject.h"
#include "Timer.h"
#include "Camera.h"
#include "InputManager.h"
#include "Player.h"

class EnemyTank : public GameObject{
public:
	EnemyTank(float x,float y);
	~EnemyTank();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
	void Shoot(Point pos);
private:
	Sprite sp;
	Point speed;
	int hp;
	Timer shootcd;
	Facing orientation;
};


#endif /* TRAB_ENEMYTANK_H_ */

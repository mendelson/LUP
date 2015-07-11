#ifndef SRC_SUPPORT_H_
#define SRC_SUPPORT_H_

#include <string>

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Support: public GameObject {
public:
	enum State {
		MOVING_TO_RIGHT, RESTING_RIGHT, MOVING_TO_LEFT, RESTING_LEFT
	};

	Support(GameObject* p);
	~Support();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	bool Is(string type);
	void NotifyCollision(GameObject&);
private:
	Sprite sp;
	Timer timer;
	Facing orientation;
	State state;
	Point speed;
	GameObject* planet;
	//////
	int alturaInicial;
//	int xi;
};

#endif /* SRC_SUPPORT_H_ */

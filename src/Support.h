#ifndef SRC_SUPPORT_H_
#define SRC_SUPPORT_H_

#include <string>

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Support: public GameObject {
public:
	Support();
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
};

#endif /* SRC_SUPPORT_H_ */

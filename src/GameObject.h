#ifndef SRC_GAMEOBJECT_H_
#define SRC_GAMEOBJECT_H_
#include "Rect.h"
#include "Point.h"
#include "Sprite.h"
using std::string;

enum Facing { RIGHT, LEFT };

class GameObject{
public:
	virtual ~GameObject(){ attacking = false; };
	GameObject(){rotation = 0;}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual Sprite getSprite() = 0;
	Rect box;
	float rotation;
	bool attacking;
	virtual void NotifyCollision(GameObject&) = 0;
	virtual bool Is(string type) = 0;
};



#endif /* SRC_GAMEOBJECT_H_ */

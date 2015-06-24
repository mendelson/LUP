#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include "GameObject.h"
#include "Timer.h"
#include "StillAnimation.h"
#include "Sound.h"
#include "EndState.h"
#include "StateData.h"

enum Jumping { STAND, JUMP, DJUMP };

class Player : public GameObject{
public:
	Player(float x,float y,GameObject* planet);
	~Player();
	void Update(float dt);
	void Render();
	bool IsDead();
	Sprite getSprite();
	static Player* player;
	bool Is(string type);
	void NotifyCollision(GameObject&);
	int GetHp();
	int GetXp();
	void IncXp(int xp);
	bool GetEnergyUpdate();

	int loopStart;
	int loopEnd;

private:
	Sprite body;
	Point speed;
	int hp;
	int xp;
	bool energyUpdate;
	Timer dmgCD;
	Timer knockback;
	Jumping jumpState;
	int jumpY;
	int yPlaneta;
	int jumped;
	GameObject* planet;
	Facing kbDirection;
};


#endif /* SRC_PLAYER_H_ */

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
	int GetSpecial();
	void IncXp(int xp);
	bool GetEnergyUpdate();
	bool energyUpdate;
	void Die();
	int loopStart;
	int loopEnd;
	GameObject* planet;
	bool deveMudarDeFase;

private:
	Sprite body;
	Point speed;
	int hp;
	int xp;
	Timer dmgCD;
	Timer knockback;
	Timer deathAnimation;
	Jumping jumpState;
	int jumpY;
	int yPlaneta;
	int jumped;
	Facing kbDirection;
	int c;
	int qntEnergia;
	Timer energiaCD;

};


#endif /* SRC_PLAYER_H_ */

#include "EnemyTank.h"
#include "Game.h"

EnemyTank::EnemyTank(float x,float y) : sp("img/enemy_tank.png",0.1,1,8),speed(),shootcd()
{
	int novox = x - (sp.GetFrameWidth()/2);
	int novoy = y - (sp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	hp = 30;
	speed.x = 2;
	speed.y = 0;
	orientation = LEFT;
	sp.SetLoop(0,7);
}

EnemyTank::~EnemyTank()
{

}

void EnemyTank::Update(float dt)
{
	Point* playerPos = new Point (Player::player->box.getCenterX(), Player::player->box.getCenterY());
	Point* currentPos = new Point (box.getCenterX(), box.getCenterY());

	shootcd.Update(dt);

	if (currentPos->getDist(*playerPos) <= 300 && currentPos->getDist(*playerPos) >= 20)
	{
		if (playerPos->x > currentPos->x)
		{
			orientation = RIGHT;
			sp.SetFlipH(true);
			box.setX(box.getX() + speed.x);
		}
		else if (playerPos->x < currentPos->x)
		{
			orientation = LEFT;
			sp.SetFlipH(false);
			box.setX(box.getX() - speed.x);
		}

		if ((playerPos->y > currentPos->y) && fabs(playerPos->y - currentPos->y) > 10)
		{
			box.setY(box.getY() + speed.y);
		}
		else if ((playerPos->y < currentPos->y) && fabs(playerPos->y - currentPos->y) > 10)
		{
			box.setY(box.getY() - speed.y);
		}
		sp.Update(dt);
	}
}

void EnemyTank::Render()
{
	sp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY());
}

bool EnemyTank::IsDead()
{
	return (hp <= 0);
}

Sprite EnemyTank::getSprite()
{
	return sp;
}

bool EnemyTank::Is(string type)
{
	return (type == "EnemyTank");
}

void EnemyTank::NotifyCollision(GameObject&)
{

}

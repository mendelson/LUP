#include "EnemyTank.h"
#include "Game.h"

EnemyTank::EnemyTank(float x,float y) : sp("img/enemy_tank.png",8,0.3,1,8),speed(),shootcd()
{
	int novox = x - (sp.GetFrameWidth()/2);
	int novoy = y - (sp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	hp = 30;
	speed.x = 10;
	speed.y = 0;
	orientation = LEFT;
}

EnemyTank::~EnemyTank()
{

}

void EnemyTank::Update(float dt)
{
	Point* playerPos = new Point (Player::player->box.getCenterX(), Player::player->box.getCenterY());
	Point* currentPos = new Point (box.getCenterX(), box.getCenterY());

	shootcd.Update(dt);
	sp.Update(dt);

	if (currentPos->getDist(*playerPos) >= 300)
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
	}
	else
	{
		if (shootcd.Get() >= 0.5)
		{
			Shoot(*playerPos);
			shootcd.Restart();
		}
		if (playerPos->x > currentPos->x)
		{
			orientation = RIGHT;
			sp.SetFlipH(true);
		}
		else if (playerPos->x < currentPos->x)
		{
			orientation = LEFT;
			sp.SetFlipH(false);
		}
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

void EnemyTank::Shoot(Point pos){
	Point* pspeed = new Point(box.getCenterX() - pos.getX(),box.getCenterY() - pos.getY());
	float speed = pspeed->magVector();
	float angle = atan(pspeed->getY()/pspeed->getX());
	if(pspeed->getX() > 0){
		angle += 3.141592653;
	}
	delete(pspeed);
	Bullet* bullet = new Bullet(box.getCenterX(),box.getCenterY(),angle,speed,2000,"img/minionBullet2.png",true,3);
	Game::GetInstance().GetCurrentState().AddObject(bullet);
}

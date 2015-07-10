#include "EnemyJellyfish.h"
#include "Game.h"

EnemyJellyfish::EnemyJellyfish(GameObject* planet, float initialRotation, float alturaInicial) : sp("img/inimigo_01.png"),speed(),shootcd()
{
	this->planet = planet;
	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = initialRotation;
	float arc = rotation*3.1415/180;
	this->alturaInicial = alturaInicial;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY()  + alturaInicial)*sin(arc)) - (box.getH()/2));
	hp = 30;
	speed.x = 10;
	speed.y = 10;
	orientation = LEFT;
}

EnemyJellyfish::~EnemyJellyfish()
{

}

void EnemyJellyfish::Update(float dt)
{
	Point* playerPos = new Point (Player::player->box.getCenterX(), Player::player->box.getCenterY());
	Point* currentPos = new Point (box.getCenterX(), box.getCenterY());

	shootcd.Update(dt);

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

void EnemyJellyfish::Render()
{
	int c;
	if (orientation == RIGHT)
		c = -30;
	else
		c = 30;

	sp.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
}

bool EnemyJellyfish::IsDead()
{
	return (hp <= 0);
}

Sprite EnemyJellyfish::getSprite()
{
	return sp;
}

bool EnemyJellyfish::Is(string type)
{
	return (type == "EnemyJellyfish");
}

void EnemyJellyfish::NotifyCollision(GameObject&)
{

}

void EnemyJellyfish::Shoot(Point pos){
	Point* pspeed = new Point(box.getCenterX() - pos.getX(),box.getCenterY() - pos.getY());
	//float speed = pspeed->magVector();
	float angle = atan(pspeed->getY()/pspeed->getX());
	if(pspeed->getX() > 0){
		angle += 3.141592653;
	}
	delete(pspeed);
	//Bullet* bullet = new Bullet(box.getCenterX(),box.getCenterY(),angle,speed,2000,"img/minionBullet2.png",true,3);
	//Game::GetInstance().GetCurrentState().AddObject(bullet);
}

#include "Jellyfish.h"
#include "Game.h"

Jellyfish::Jellyfish(float x,float y) : sp("img/inimigo_01.png"),speed(),shootcd()
{
	int novox = x - (sp.GetFrameWidth()/2);
	int novoy = y - (sp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	hp = 30;
	speed.x = 10;
	speed.y = 10;
	orientation = LEFT;
}

Jellyfish::~Jellyfish()
{

}

void Jellyfish::Update(float dt)
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
	}
}

void Jellyfish::Render()
{
	int c;
	if (orientation == RIGHT)
		c = -30;
	else
		c = 30;

	sp.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
}

bool Jellyfish::IsDead()
{
	return (hp <= 0);
}

Sprite Jellyfish::getSprite()
{
	return sp;
}

bool Jellyfish::Is(string type)
{
	return (type == "Jellyfish");
}

void Jellyfish::NotifyCollision(GameObject&)
{

}

void Jellyfish::Shoot(Point pos){
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

#include "Support.h"

Support::Support() : sp("img/support.png",19,0.3,2,15), timer()
{

	orientation = Player::player->orientation;

	int c;
	if (orientation == RIGHT)
		c = -13;
	else
		c = Player::player->box.getW() + 50;

	box.setX(Player::player->box.getX() + c);
	box.setY(Player::player->box.getY() + 50);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());

	orbitation = 0;
}

Support::~Support()
{

}

void Support::Update(float dt)
{
	timer.Update(dt);

	orientation = Player::player->orientation;
	int c;
	if (orientation == RIGHT)
	{
		c = -13;
		sp.SetFlipH(false);
	}
	else
	{
		c = Player::player->box.getW() - 50;
		sp.SetFlipH(true);
	}

	box.setX(Player::player->box.getX() + c);
	box.setY(Player::player->box.getY() + 50);

	sp.Update(dt);
}

void Support::Render()
{
	sp.Render(box.getX() +  Camera::pos.getX(), box.getY() +  Camera::pos.getY());
}

bool Support::IsDead()
{
	return false;
}

Sprite Support::getSprite()
{
	return sp;
}
bool Support::Is(string type)
{
	return (type == "Support");
}

void Support::NotifyCollision(GameObject&)
{

}

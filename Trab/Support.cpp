#include "Support.h"

Support::Support() : sp("img/support.png"), timer()
{
	sp.SetScaleX(0.05);
	sp.SetScaleY(0.05);

	orientation = Player::player->orientation;

	int c;
	if (orientation == RIGHT)
		c = -50;
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
	if (timer.Get() >= 2)
	{
		timer.Restart();
	}

	orientation = Player::player->orientation;
	int c;
	if (orientation == RIGHT)
	{
		c = -50;
		sp.SetFlipH(false);
	}
	else
	{
		c = Player::player->box.getW() - 50;
		sp.SetFlipH(true);
	}

	if (timer.Get() <= 1)
	{
		orbitation += 0.5;
	}
	else
	{
		orbitation -= 0.5;
	}

	box.setX(Player::player->box.getX() + c);
	box.setY(Player::player->box.getY() + 50 + orbitation);
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

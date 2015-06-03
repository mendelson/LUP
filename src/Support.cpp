#include "Support.h"

Support::Support() : sp("img/support.png",0.1,3,16), timer()
{

	orientation = Player::player->orientation;

	int c;
	if (orientation == RIGHT)
		c = -50;
	else
		c = Player::player->box.getW() - 50;

	box.setX(Player::player->box.getX() + c);
	box.setY(Player::player->box.getY() + 1);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	attacking = false;

	sp.SetLoop(0,14);
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
		c = -50;
		sp.SetFlipH(false);
	}
	else
	{
		c = Player::player->box.getW() - 50;
		sp.SetFlipH(true);
	}

	if (sp.GetCurrentFrame() == 14)
		sp.SetLoop(16,19);
	else if (sp.GetCurrentFrame() == 19)
		sp.SetLoop(0,14);

	if (sp.GetCurrentFrame() == 47)
	{
		attacking = false;
		sp.SetLoop(16,19);
	}

	if(InputManager::GetInstance().KeyPress(SDLK_s) || attacking)
	{
		attacking = true;
		sp.SetLoop(32, 47);
	}

	box.setX(Player::player->box.getX() + c);
	box.setY(Player::player->box.getY() + 1);

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

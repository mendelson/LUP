#include "WeaponGun.h"

#include <SDL_keycode.h>
#include <string>

#include "Camera.h"
#include "InputManager.h"
#include "Point.h"

WeaponGun::WeaponGun(std::string file) : sp(file,0.1,2,8)
{
	isDead = false;
	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
	box.setX(Player::player->box.x);
	box.setY(Player::player->box.y);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());

	atkFrame = false;

	orientation = Player::player->orientation;
	if (orientation == LEFT)
		sp.SetFlipH(true);
}

WeaponGun::~WeaponGun()
{

}

void WeaponGun::Update(float dt)
{
	deathCD.Update(dt);

	if (Player::player == NULL)
		return;

	box.setX(Player::player->box.x);
	box.setY(Player::player->box.y);
	orientation = Player::player->orientation;

	if (orientation == LEFT)
		sp.SetFlipH(true);
	else
		sp.SetFlipH(false);

	if (sp.GetCurrentFrame() == 9)
		atkFrame = false;

	if(InputManager::GetInstance().KeyPress(SDLK_a) || atkFrame)
	{
		Sound* sound = new Sound("audio/vassoura.wav");
		sound->Play(0);
		delete(sound);
		atkFrame = true;
		sp.SetLoop(8, 9);
	}
	else
	{
		if (Player::player->loopStart == 16 && Player::player->loopEnd == 17)
		{
			sp.SetLoop(0,0);
		}
		else
		{
			sp.SetLoop(0, 7);
		}
	}

	if (orientation == RIGHT)
		rotation += 90;
	else
		rotation -= 90;

	sp.Update(dt);

	if(InputManager::GetInstance().KeyPress(SDLK_d) && deathCD.Get() > 0.5)
	{
		isDead = true;
	}
}

void WeaponGun::Render()
{
	int c = 0;

	if (orientation == RIGHT)
		c = -25;
	else
		c = 25;

	sp.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
}

bool WeaponGun::IsDead()
{
	return ((Player::player == NULL) || isDead);
}

Sprite WeaponGun::getSprite()
{
	return sp;
}

bool WeaponGun::Is(string type)
{
	return (type == "WeaponGun");
}

void WeaponGun::NotifyCollision(GameObject&)
{

}

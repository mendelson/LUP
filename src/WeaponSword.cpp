#include "WeaponSword.h"

#include <SDL_keycode.h>
#include <string>

#include "Camera.h"
#include "InputManager.h"
#include "Point.h"

WeaponSword::WeaponSword(std::string file) : sp(file,0.1,2,8)
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

WeaponSword::~WeaponSword()
{

}

void WeaponSword::Update(float dt)
{
	if (Player::player->GetHp() <= 0)
	{
		somaRotation = 0;
		sp.SetLoop(4,4);
		sp.Update(1);
		return;
	}

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

	if (sp.GetCurrentFrame() == 3)
		atkFrame = false;

	if(InputManager::GetInstance().KeyPress(SDLK_a) || atkFrame)
	{
		Sound* sound = new Sound("audio/espada.wav");
		sound->Play(0);
		delete(sound);
		atkFrame = true;
		sp.SetLoop(0, 3);
	}
	else
	{
		if (Player::player->loopStart == 16 && Player::player->loopEnd == 17)
		{
			sp.SetLoop(0,0);
		}
		else
		{
			sp.SetLoop(8, 15);
			if (Player::player->planet->somaRotation == 0)
				sp.SetLoop(8, 8);
		}
	}

	attacking = (sp.GetCurrentFrame() == 2);

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

void WeaponSword::Render()
{
	int c = 0;

	if (orientation == RIGHT)
		c = -25;
	else
		c = 25;

	sp.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
}

bool WeaponSword::IsDead()
{
	return ((Player::player == NULL) || isDead);
}

Sprite WeaponSword::getSprite()
{
	return sp;
}

bool WeaponSword::Is(string type)
{
	return (type == "WeaponSword");
}

void WeaponSword::NotifyCollision(GameObject&)
{

}

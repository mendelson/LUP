#include "WeaponBroom.h"

#include <SDL_keycode.h>

#include "Camera.h"
#include "InputManager.h"
#include "Player.h"
#include "Point.h"
#include "Sound.h"

WeaponBroom::WeaponBroom(std::string file) : sp(file,0.1,4,8)
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

WeaponBroom::~WeaponBroom()
{

}

void WeaponBroom::Update(float dt)
{
	if(InputManager::GetInstance().KeyPress(SDLK_d))
	{
		isDead = true;
	}

	if (Player::player == NULL)
		return;

	box.setX(Player::player->box.x);
	box.setY(Player::player->box.y);
	orientation = Player::player->orientation;

	if (orientation == LEFT)
		sp.SetFlipH(true);
	else
		sp.SetFlipH(false);

	if (sp.GetCurrentFrame() == 19)
		atkFrame = false;

	if(InputManager::GetInstance().KeyPress(SDLK_a) || atkFrame)
	{
		Sound* sound = new Sound("audio/vassoura.wav");
		sound->Play(0);
		delete(sound);
		atkFrame = true;
		sp.SetLoop(16, 19);
	}
	else
	{
		if (Player::player->loopStart == 16 && Player::player->loopEnd == 17)
		{
			sp.SetLoop(0,0);
		}
		else
		{
			sp.SetLoop(Player::player->loopStart, Player::player->loopEnd);
		}
	}

	attacking = (sp.GetCurrentFrame() == 18);

	if (orientation == RIGHT)
		rotation += 90;
	else
		rotation -= 90;

	sp.Update(dt);
}

void WeaponBroom::Render()
{
	int c = 0;

	if (orientation == RIGHT)
		c = -25;
	else
		c = 25;

	sp.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
}

bool WeaponBroom::IsDead()
{
	return ((Player::player == NULL) || isDead);
}

Sprite WeaponBroom::getSprite()
{
	return sp;
}

bool WeaponBroom::Is(string type)
{
	return (type == "WeaponBroom");
}

void WeaponBroom::NotifyCollision(GameObject&)
{

}

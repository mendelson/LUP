#include "Support.h"

#include <SDL_keycode.h>

#include "Camera.h"
#include "InputManager.h"
#include "Player.h"
#include "Point.h"
#include "Sound.h"

Support::Support() : sp("img/support.png",0.1,3,16), timer()
{

	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
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


	sp.SetLoop(0,12);
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
		c = -25;
		sp.SetFlipH(false);
	}
	else
	{
		c = Player::player->box.getW() - 25;
		sp.SetFlipH(true);
	}

	if (sp.GetCurrentFrame() == 47)
	{
		sp.SetLoop(0,12);
	}

	if(InputManager::GetInstance().KeyPress(SDLK_s))
	{
		Sound* sound = new Sound("audio/robo.wav");
		sound->Play(0);
		delete(sound);
		sp.SetLoop(32, 47);
	}
	attacking = (sp.GetCurrentFrame() == 42);

	if(InputManager::GetInstance().IsKeyDown(SDLK_SPACE))
	{
		sp.SetLoop(16,19);
	}
	else
	{
		sp.SetLoop(0,12);
	}

	/*Point p_player(Player::player->box.getX() + c,
			Player::player->box.getY() + 1);
	Point p_me(box.x, box.y);

	if (p_me.getDist(p_player) <= 20) {
		box.x = Player::player->box.getX() + c;
		box.y = Player::player->box.getY() + 1;
	} else {
		float theta = p_player.getInclinationFromTop();
		box.setX(box.x + SPEED * cos(theta)*dt - Camera::pos.getX());
		box.setY(box.y + SPEED * sin(theta)*dt - Camera::pos.getY());
	}*/

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

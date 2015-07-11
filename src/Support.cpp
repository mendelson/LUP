#include "Support.h"

#include <SDL_keycode.h>
#include <cmath>

#include "Camera.h"
#include "InputManager.h"
#include "Player.h"
#include "Point.h"
#include "Sound.h"

#define SPEED 70

Support::Support(GameObject* p) : sp("img/support.png",0.1,3,16), timer(), speed(0,0)
{
	this->planet = p;

	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
	orientation = Player::player->orientation;
	state = RESTING_LEFT;

	int c;
	if (orientation == RIGHT)
		c = -50;
	else
		c = Player::player->box.getW() - 50;
	//////
	alturaInicial = Player::player->box.getY() + 1;
	//xi = Player::player->box.getX() + c;

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
	if (orientation == RIGHT) {
		c = -50;
	} else if (orientation == LEFT) {
		c = Player::player->box.getW() - 6;
	}

	if (sp.GetCurrentFrame() == 47) {
		sp.SetLoop(0, 12);
	}

	if (InputManager::GetInstance().KeyPress(SDLK_s)) {
		Sound* sound = new Sound("audio/robo.wav");
		sound->Play(0);
		delete (sound);
		sp.SetLoop(32, 47);
	}
	attacking = (sp.GetCurrentFrame() == 42);

	if (InputManager::GetInstance().IsKeyDown(SDLK_SPACE)) {
		sp.SetLoop(16, 19);
	} else {
		sp.SetLoop(0, 12);
	}

	Point p_player(Player::player->box.getX() + c,
			Player::player->box.getY() + 1);

	//cout << box.x << "; " << box.y << " | ";
	//cout << p_player.x << "; " << p_player.y << endl;

	//cout << Camera::pos.getX() << " | " << Camera::pos.getY() << endl;

	float dx = p_player.x - box.x;
	float dy = p_player.y - box.y;
	float distance = sqrt(dx * dx + dy * dy);

	//cout << distance << endl;

	if (distance <= 5) {
		speed.setX(0);
		speed.setY(0);
		//box.x = Player::player->box.getX() + c;
		//box.y = Player::player->box.getY() + 1;

		if (orientation == RIGHT) {
			state = RESTING_LEFT;
		} else {
			state = RESTING_RIGHT;
		}
	} else {
//		somaRotation = planet->somaRotation;
//		rotation += somaRotation;
//
//		float arc = rotation * 3.1415 / 180;
//		box.x = (planet->box.getCenterX()
//				+ ((planet->box.getW() / 2 - 300 + alturaInicial + box.getH())
//						* cos(arc)) - (box.getW() / 2));
//		box.y = (planet->box.getCenterY()
//				+ ((planet->box.getH() / 2 - 300 + alturaInicial + box.getH())
//						* sin(arc)) - (box.getH() / 2));
		float theta1 = acos(dx / distance);
		float theta2 = asin(dy / distance);
		speed.setX(SPEED * cos(theta1));
		speed.setY(SPEED * sin(theta2));

		float dX = speed.x * dt;
		float dY = speed.y * dt;

		box.x += dX;
		box.y += dY;

		if (orientation == RIGHT) {
			state = MOVING_TO_LEFT;
		} else {
			state = MOVING_TO_RIGHT;
		}
	}

	if (state == MOVING_TO_RIGHT || state == RESTING_LEFT) {
		sp.SetFlipH(false);
	} else if (state == MOVING_TO_LEFT || state == RESTING_RIGHT) {
		sp.SetFlipH(true);
	}

	sp.Update(dt);

	//cout << speed.x << " | " << speed.y << endl;
//	int c;
//	if (orientation == RIGHT) {
//		c = -50;
//	} else if (orientation == LEFT) {
//		c = Player::player->box.getW() - 6;
//	}
//
//	Point p_player(Player::player->box.getX() + c, Player::player->box.getY() + 1);
//
////	cout << box.x << "; " << box.y << " | ";
////	cout << p_player.x << "; " << p_player.y << endl;
//
//	float dx = p_player.x - box.x;
//	float dy = p_player.y - box.y;
//	float distance = sqrt(dx * dx + dy * dy);
//
//	//cout << distance << endl;
//
//	timer.Update(dt);
//	if (distance > 50) {
//		//sp.SetLoop(4, 5);
//		if (p_player.x > box.x) {
//			//orientation = RIGHT;
//			//sp.SetFlipH(true);
//			rotation += 10 * dt;
//		} else if (p_player.x < box.x) {
//			//orientation = LEFT;
//			//sp.SetFlipH(false);
//			rotation -= 10 * dt;
//		}
//
//		somaRotation = planet->somaRotation;
//		rotation += somaRotation;
//
//		float dx1 = p_player.x - planet->box.getW() / 2 - 300 + box.getH();
//		float dy1 = p_player.y - planet->box.getH() / 2 - 300 + box.getH();
//		float distance1 = sqrt(dx1 * dx1 + dy1 * dy1);
//		alturaInicial = distance1;
//
//		float arc = rotation * 3.1415 / 180;
////		box.x = (planet->box.getCenterX() + ((planet->box.getW() / 2 - 300 + alturaInicial + box.getH()) * cos(arc)) - (box.getW() / 2));
////		box.y = (planet->box.getCenterY() + ((planet->box.getH() / 2 - 300 + alturaInicial + box.getH()) * sin(arc)) - (box.getH() / 2));
//		box.x = (planet->box.getCenterX() + ((planet->box.getW() / 2 - 300 + alturaInicial + box.getH()) * cos(arc)) - (box.getW() / 2));
//		box.y = (planet->box.getCenterY() + ((planet->box.getH() / 2 - 300 + alturaInicial + box.getH()) * sin(arc)) - (box.getH() / 2));
//		//sp.Update(dt);
//		//cout << box.y << " | ";
//
//		////////
//
//		//float theta1 = acos(dx / distance);
//		//float theta2 = asin(dy / distance);
//		//speed.setX(SPEED * cos(theta1));
//		//speed.setY(SPEED * sin(theta2));
//
//		//float dX = speed.x * dt;
//		//float dY = speed.y * dt;
//
//		//box.x += dX;
//		//box.y += dY;
//		//box.y = (planet->box.getCenterY() + ((planet->box.getH() / 2 - 300 + alturaInicial + box.getH()) * sin(arc)) - (box.getH() / 2))          +                                           ;
//		//cout << box.y << endl;
//
//		////////
//	} else {
//		speed.setX(0);
//		speed.setY(0);
//		//sp.SetLoop(0, 13);
//		//if ((sp.GetCurrentFrame() == 4 || sp.GetCurrentFrame() == 11)
//		//		&& shootcd.Get() > 0.35) {
//			if (p_player.x > box.x) {
//				//orientation = RIGHT;
//				//sp.SetFlipH(true);
//			} else if (p_player.x < box.x) {
//				//orientation = LEFT;
//				//sp.SetFlipH(false);
//			}
//			//Shoot(*playerPos);
//			//shootcd.Restart();
//		//}
//		//sp.Update(dt);
//	} /*else {
		//sp.SetFrame(0);
		//sp.Update(1);
	//}

	/*free(playerPos);
	free(currentPos);*/


	/*timer.Update(dt);

	orientation = Player::player->orientation;
	int c;
	if (orientation == RIGHT) {
		c = -50;
	} else if (orientation == LEFT) {
		c = Player::player->box.getW() - 6;
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

	Point p_player(Player::player->box.getX() + c, Player::player->box.getY() + 1);

	cout << box.x << "; " << box.y << " | ";
	cout << p_player.x << "; " << p_player.y << endl;

	//cout << Camera::pos.getX() << " | " << Camera::pos.getY() << endl;

	float dx = p_player.x - box.x;
	float dy = p_player.y - box.y;
	float distance = sqrt(dx * dx + dy * dy);

	//cout << distance << endl;

	if (distance <= 5) {
		speed.setX(0);
		speed.setY(0);
		box.x = Player::player->box.getX() + c;
		box.y = Player::player->box.getY() + 1;

		if (orientation == RIGHT) {
			state = RESTING_LEFT;
		} else {
			state = RESTING_RIGHT;
		}
	} else {
		float theta1 = acos(dx / distance);
		float theta2 = asin(dy / distance);
		speed.setX(SPEED * cos(theta1));
		speed.setY(SPEED * sin(theta2));

		float dX = speed.x * dt;
		float dY = speed.y * dt;

		box.x += dX;
		box.y += dY;

		if (orientation == RIGHT) {
			state = MOVING_TO_LEFT;
		} else {
			state = MOVING_TO_RIGHT;
		}
	}

	if(state == MOVING_TO_RIGHT || state == RESTING_LEFT) {
		sp.SetFlipH(false);
	}
	else if(state == MOVING_TO_LEFT || state == RESTING_RIGHT){
		sp.SetFlipH(true);
	}

	sp.Update(dt);

	//cout << speed.x << " | " << speed.y << endl;*/
}

void Support::Render()
{
	sp.Render(box.getX() +  Camera::pos.getX(), box.getY() +  Camera::pos.getY());
	//sp.Render(box.getX() + Camera::pos.getX(), box.getY() + Camera::pos.getY(),rotation + 90);
//	float x = planet->box.getCenterX() + planet->box.getW() / 2 - 300 + box.getH() - (box.getW() / 2);
//	float y = planet->box.getCenterY() + planet->box.getH() / 2 - 300 + box.getH() - (box.getH() / 2);
//	float x = Player::player->box.getX();
//	float y = Player::player->box.getY();
//	cout << x << " | " << y << endl;
//	sp.Render(x, y);
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

#include "Support.h"

#include <SDL_keycode.h>
#include <cmath>

#include "Camera.h"
#include "InputManager.h"
#include "Player.h"
#include "Sound.h"

const unsigned int SPEED_X = 600;
const unsigned int SPEED_Y = 70;

Support::Support(GameObject* p) :
		sp("img/support.png", 0.1, 3, 16), timer(), speed(0, 0) {
	this->planet = p;

	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
	orientation = Player::player->orientation;
	previousOrientation = orientation;
	state = RESTING_LEFT;

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

	sp.SetLoop(0, 12);
}

Support::~Support() {

}

void Support::Update(float dt) {
	timer.Update(dt);

	orientation = Player::player->orientation;
	int c;
	if (orientation == RIGHT) {
		c = -50;
	} else if (orientation == LEFT) {
		c = Player::player->box.getW() - 6;
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

	if (distance <= 10) {
		speed.setX(0);
		speed.setY(0);

		if (orientation == RIGHT) {
			state = RESTING_LEFT;
		} else {
			state = RESTING_RIGHT;
		}
	} else {
		float theta1 = acos(dx / distance);
		float theta2 = asin(dy / distance);
		speed.setX(SPEED_X * cos(theta1));
		speed.setY(SPEED_Y * sin(theta2));

		float dX = speed.x * dt;
		float dY = speed.y * dt;

		box.x += dX;
		box.y += dY;

		if (previousOrientation != orientation) {
			if (orientation == RIGHT) {
				state = MOVING_TO_LEFT;
			} else {
				state = MOVING_TO_RIGHT;
			}
		}
	}

	previousOrientation = orientation;

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
		if (state == MOVING_TO_RIGHT || state == RESTING_LEFT) {
			sp.SetFlipH(false);
		} else if (state == MOVING_TO_LEFT || state == RESTING_RIGHT) {
			sp.SetFlipH(true);
		}
	}

	sp.Update(dt);
}

void Support::Render() {
	sp.Render(box.getX() + Camera::pos.getX(), box.getY() + Camera::pos.getY());
}

bool Support::IsDead() {
	return false;
}

Sprite Support::getSprite() {
	return sp;
}
bool Support::Is(string type) {
	return (type == "Support");
}

void Support::NotifyCollision(GameObject&) {

}

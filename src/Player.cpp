#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"

Player* Player::player = NULL;

Player::Player(float x, float y): body("img/lup.png",0.15,3,9), speed(),timer()
{
	int novox = x - (body.GetFrameWidth()/2);
	int novoy = y - (body.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(body.GetHeight());
	box.setW(body.GetWidth());
	hp = 30;
	speed.x = 15;
	speed.y = 25;
	jumpState = STAND;
	orientation = RIGHT;
	jumped = 0;

	player = this;

	loopStart = 0;
	loopEnd = 0;

}

Player::~Player(){
	player = NULL;
}


void Player::Update(float dt)
{
	if (energyUpdate == true)
		energyUpdate = false;

	if(InputManager::GetInstance().KeyPress(SDLK_UP) && jumpState != DJUMP)
	{
		body.SetFrame(10);
		if (jumpState == STAND)
		{
			jumpState = JUMP;
			jumpY = box.getY();
		}
		else if (jumpState == JUMP)
		{
			jumpState = DJUMP;
			jumped = 0;
		}
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
	{
		loopStart = 1;
		loopEnd = 8;
		orientation = LEFT;
		body.SetFlipH(true);
		box.setX(box.getX() - speed.x);
	}
	else if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
	{
		loopStart = 1;
		loopEnd = 8;
		orientation = RIGHT;
		body.SetFlipH(false);
		box.setX(box.getX() + speed.x);
	}
	else
	{
		loopStart = 1;
		loopEnd = 1;
		body.Update(0);

	}

	if (jumpState == JUMP || jumpState == DJUMP)
	{
		if (jumped <= 250)
		{
			jumped += speed.y;
			box.setY(box.getY() - speed.y);
		}
		else if (box.getY() < jumpY)
		{
			box.setY(box.getY() + speed.y);
		}
		else
		{
			jumpState = STAND;
			jumped = 0;
		}
		loopStart = 10;
		loopEnd = 14;

		if (body.GetCurrentFrame() >= 14)
		{
			loopStart = 14;
			body.Update(0);
		}
	}

	body.SetLoop(loopStart,loopEnd);
	body.Update(dt);

}

void Player::Render()
{
	int c;
	if (orientation == RIGHT)
		c = -80;
	else
		c = 80;

	body.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
}


bool Player::Is(string type)
{
	return (type == "Player");
}
bool Player::IsDead(){
	if (hp<=0){
		return true;
	}
	return false;
}


Sprite Player::getSprite()
{
	return body;
}

void Player::NotifyCollision(GameObject& other)
{
}

int Player::GetHp()
{
	return hp;
}

int Player::GetXp()
{
	return xp;
}

bool Player::GetEnergyUpdate()
{
	return energyUpdate;
}

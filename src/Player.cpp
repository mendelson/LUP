#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"

Player* Player::player = NULL;

Player::Player(float x, float y): body("img/lup.png",0.15,3,8), speed(),dmgCD()
{
	int novox = x - (body.GetFrameWidth()/2);
	int novoy = y - (body.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(body.GetHeight());
	box.setW(body.GetWidth());
	hp = 50;
	xp = 0;
	speed.x = 15;
	speed.y = 25;
	jumpState = STAND;
	orientation = RIGHT;
	jumped = 0;

	player = this;
	globalRotation = 0;
	loopStart = 0;
	loopEnd = 0;

}

Player::~Player(){
	player = NULL;
}


void Player::Update(float dt)
{
	dmgCD.Update(dt);

	if (energyUpdate == true)
		energyUpdate = false;
/*
	if (dmgCD.Get() < 1)
	{
		loopStart = 16;
		loopEnd = 18;
		if (body.GetCurrentFrame() >= 18)
		{
			loopStart = 18;
			body.Update(0);
		}
		body.SetLoop(loopStart,loopEnd);
		body.Update(dt);
		return;
	}
*/
	if(InputManager::GetInstance().KeyPress(SDLK_UP) && jumpState != DJUMP)
	{
		body.SetFrame(8);
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
		loopStart = 0;
		loopEnd = 7;
		orientation = LEFT;
		body.SetFlipH(true);
		box.setX(box.getX() - speed.x);
		globalRotation += 18*dt;
	}
	else if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
	{
		loopStart = 0;
		loopEnd = 7;
		orientation = RIGHT;
		body.SetFlipH(false);
		box.setX(box.getX() + speed.x);
		globalRotation -= 18*dt;
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
		loopStart = 8;
		loopEnd = 10;

		if (body.GetCurrentFrame() >= 10)
		{
			loopStart = 10;
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
	/*
	if (other.Is("EnemyTank") && other.attacking)
	{
		if (dmgCD.Get() > 1)
		{
			dmgCD.Restart();
			hp -= 10;
		}

		if (IsDead())
		{
			Sprite* aux = new Sprite("img/lup_dying.png",0.2,1,8);
			aux->SetLoop(1,7);
			StillAnimation* animacao = new StillAnimation(box.getCenterX(),box.getCenterY(), rotation, *aux, 0.2 * 7, true);
			Game::GetInstance().GetCurrentState().AddObject(animacao);
			Camera::Unfollow();
			Game::GetInstance().GetCurrentState().SetPopRequested(true);
		}
	}
	*/
}

int Player::GetHp()
{
	return hp;
}

int Player::GetXp()
{
	return xp;
}

void Player::IncXp(int xp)
{
	this->xp += xp;
}

bool Player::GetEnergyUpdate()
{
	return energyUpdate;
}

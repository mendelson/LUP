/*
 * Player.cpp
 *
 *  Created on: 22/05/2015
 *      Author: Vitor
 */
#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"

Player* Player::player = NULL;

Player::Player(float x, float y): sp("img/penguin.png"),speed(),timer(){
	int novox = x - (sp.GetWidth()/2);
	int novoy = y - (sp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	hp = 30;
	speed.x = 15;
	speed.y = 10;
}

Player::~Player(){
	player = NULL;
}


void Player::Update(float dt){
	//timer.Update(dt);

	if(InputManager::GetInstance().KeyPress(SDLK_w) && jumpState != DJUMP)
	{
		if (jumpState == STAND)
		{
			jumpState = JUMP;
		}
		else if (jumpState == JUMP)
		{
			jumpState = DJUMP;
			timer.Restart();
		}
	}

	if(InputManager::GetInstance().IsKeyDown(SDLK_a))
	{
		orientation = LEFT;
		sp.SetFlipH(true);
		box.setX(box.getX() - speed.x);
		sp.Update(dt);
	}
	else if(InputManager::GetInstance().IsKeyDown(SDLK_d))
	{
		orientation = RIGHT;
		sp.SetFlipH(false);
		box.setX(box.getX() + speed.x);
		sp.Update(dt);
	}
	else
	{
		sp.SetFrame(0);
	}

	if (jumpState == JUMP || jumpState == DJUMP)
	{
		timer.Update(dt);

		if (timer.Get() <= 0.6)
		{
			box.setY(box.getY() - speed.y);
		}
		else if (box.getY() < 200)
		{
			box.setY(box.getY() + speed.y);
		}
		else
		{
			jumpState = STAND;
			timer.Restart();
		}
	}


	if(box.getX() <= 324){
		box.setX(1920);
	}
	if(box.getX() >= 3523){
		box.setX(1920);
	}

}

void Player::Render(){
	sp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY());
}


bool Player::Is(string type){
	return (type == "Player");
}
bool Player::IsDead(){
	if (hp<=0){
		return true;
	}
	return false;
}


Sprite Player::getSprite(){
	return sp;
}

void Player::NotifyCollision(GameObject& other){
}

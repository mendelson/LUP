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

Player::Player(float x, float y): sp("img/player.png",8,0.3),speed(),timer(){
	int novox = x - (sp.GetFrameWidth()/2);
	int novoy = y - (sp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	hp = 30;
	speed.x = 15;
	speed.y = 25;
	jumpState = STAND;
	orientation = RIGHT;
	jumped = 0;

	player = this;

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
			jumpY = box.getY();
		}
		else if (jumpState == JUMP)
		{
			jumpState = DJUMP;
			jumped = 0;
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
		sp.Update(0);
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
	}


	if(box.getX() <= 324){
		box.setX(1920);
	}
	if(box.getX() >= 3523){
		box.setX(1920);
	}

}

void Player::Render(){
	int c;
	if (orientation == RIGHT)
		c = -80;
	else
		c = 80;

	sp.Render(box.getX() +  Camera::pos.getX() + c,box.getY() +  Camera::pos.getY());
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

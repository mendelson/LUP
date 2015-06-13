#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"

Player* Player::player = NULL;

Player::Player(float x, float y,GameObject* planet): body("img/lup.png",0.15,3,8), speed(),dmgCD()
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
	jumpState = DJUMP;
	orientation = RIGHT;
	jumped = 250;
	player = this;
	loopStart = 0;
	loopEnd = 0;
	this->planet = planet;

}

Player::~Player(){
	player = NULL;
}


void Player::Update(float dt)
{
	dmgCD.Update(dt);
	jumpY = planet->getAltura(planet->rotation);
	somaRotation = 0;
	//if(box.getY() < jumpY){
	//	jumpState = DJUMP;
	//	jumped = 250;
	//}


	//float yPersonagem = box.getCenterY() - planet->box.getW()/2 + planet->box.getCenterY();
	//float distPlaneta = - planet->box.getW()/2 + planet->box.getCenterY();
	float distPlaneta =  planet->box.getY() - 100;
	float yPersonagem = box.getY() + box.getH() +  distPlaneta;

	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
		cout << box.getY() << endl;
		cout << "jumpY :" << jumpY << endl;
	}

	//if(box.getY() < jumpY && jumpState == STAND){
	//	body.SetFrame(8);
    //	jumpState = DJUMP;
	//	jumped = 300;
	//}

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
			//jumpY = box.getY();
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
		int proxAltura = planet->getAltura(planet->rotation + 1);
		int difAltura = proxAltura - box.getY();
		somaRotation = 1;
		if(jumpState == STAND){
			if(difAltura > 0){
				body.SetFrame(8);
				jumpState = DJUMP;
				jumped = 300;
			}else if(difAltura > -25){
				box.setY(box.getY() + difAltura);

			}
		}
		//cout << "proxAltura  -  " << proxAltura << endl;
		//cout << "difAltura  -  " << difAltura << endl;
		//box.setX(box.getX() - speed.x);
	}
	else if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
	{
		loopStart = 0;
		loopEnd = 7;
		orientation = RIGHT;
		body.SetFlipH(false);
		int antAltura = planet->getAltura(planet->rotation - 1);
		int difAltura = antAltura - box.getY();
		somaRotation = -1;
		if(jumpState == STAND){
			if(difAltura > 0){
				body.SetFrame(8);
				jumpState = DJUMP;
				jumped = 300;
			}else if(difAltura > -25){
				box.setY(box.getY() - difAltura);

			}
		}

		//limite para nao passar do chao
		if(box.getY() > jumpY){
			box.setY(jumpY);
		}

		//cout << "antAltura  -  " << antAltura << endl;
		//cout << "difAltura  -  " << difAltura << endl;
		//box.setX(box.getX() + speed.x);
	}
	else
	{
		loopStart = 1;
		loopEnd = 1;
		body.Update(0);

	}

	if (jumpState == JUMP || jumpState == DJUMP)
	{
		if (jumped <= 100)
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

	//gambi para corrigir bug
	//if(box.getY() > jumpY)
	//	box.setY(jumpY - 1);


	//if(box.getY()-15 > jumpY){
	//	box.setY(box.getY() + 14);
	//}

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
	if(other.Is("Plataforma")){
		cout<<"Colidiu com plataforma!" << endl;
	}
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

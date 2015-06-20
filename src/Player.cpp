#include "Player.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"

Player* Player::player = NULL;

Player::Player(float x, float y,GameObject* planet): body("img/Sprites_Corpo_LUP.png",0.15,4,8), speed(),dmgCD()
{
	body.SetScaleX(0.5);
	body.SetScaleY(0.5);
	int novox = x - (body.GetFrameWidth()/2);
	int novoy = y - (body.GetHeight()/2);
	novoy += body.GetHeight()*3/2;
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

	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
		cout << box.getY() << endl;
		cout << "jumpY :" << jumpY << endl;
	}


	if (energyUpdate == true)
		energyUpdate = false;

	if(InputManager::GetInstance().KeyPress(SDLK_UP) && jumpState != DJUMP)
	{
		body.SetFrame(8);
		if (jumpState == STAND)
		{
			jumpState = JUMP;
		}
		else if (jumpState == JUMP)
		{
			jumpState = DJUMP;
			jumped = 0;
		}
	}

	//verifica se o personagem esta querendo andar pra algum lado
	if(InputManager::GetInstance().IsKeyDown(SDLK_LEFT))
	{
			loopStart = 0;
			loopEnd = 7;
			orientation = LEFT;
			body.SetFlipH(true);
			somaRotation = 1;
	}
	else if(InputManager::GetInstance().IsKeyDown(SDLK_RIGHT))
	{
		loopStart = 0;
		loopEnd = 7;
		orientation = RIGHT;
		body.SetFlipH(false);
		somaRotation = -1;
	}
	else
	{
		loopStart = 1;
		loopEnd = 1;
		body.Update(0);
	}

	//verifica se ele quer correr pra esse lado
	//corrida
	if(InputManager::GetInstance().IsKeyDown(SDLK_SPACE)){
		somaRotation*=2;
	}

	//verifica se ele pode ir pra onde quer, e sobe se ele deve subir
	if(jumpState == STAND){
		int proxAltura = planet->getAltura(planet->rotation + somaRotation);
		//a de cima é a proxima altura que ele ira, esta é a proxima altura do angulo, deve se usar a de baixo para verificar se eh uma rampa que ele pode subir, pois se ele estiver correndo pode subir muito
		//usamos entao a de cima para subir o personagem
		int alturaProxAngulo = planet->getAltura(planet->rotation + (somaRotation/abs(somaRotation)));
		int difAltura = proxAltura - jumpY;
		int difAlturaProxAngulo = alturaProxAngulo - jumpY;
		//usa esse porque se ele estiver correndo a altura pode subir mais do que o normal
		//float difAlturaPorAngulo = abs(difAltura / somaRotation);
		if(difAlturaProxAngulo > -25){
			box.setY(box.getY() + difAltura);
		}


		//se ele andar e o jumpy nao for o mesmo do chao tenta fazer ele cair, pois ele pode estar saindo da plataforma, se ainda estivar na plataforma isso vai ser resolvido na colisao
		if(somaRotation != 0){
			if(jumpY > box.getY()){
				body.SetFrame(8);
				jumpState = DJUMP;
				jumped = 300;
			}
		}

	}




	//limite para nao passar do chao --- GAMBIARRA
	if(box.getY() > jumpY){
		box.setY(jumpY);
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
	int c = 0;

	if (orientation == RIGHT)
		c = -50;
	else
		c = 50;

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
		//cout<<"Colidiu com plataforma!" << endl;
		if(box.getY()> other.box.getY()){
			box.setY(other.box.getY() - box.getH()/2 - 10);
			jumpState = STAND;
		}
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

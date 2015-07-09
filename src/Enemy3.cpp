#include "Enemy3.h"
#include "Game.h"

Enemy3::Enemy3(float x, float y, GameObject* planet, float initialRotation, float alturaIncial) : sp("img/enemy3.png", 0.30, 3, 7), speed(), startPos(x, y), dmgCD(), knockback(), shootcd()
{
	this->planet = planet;
	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = initialRotation;
	float arc = rotation*3.1415/180;
	this->alturaInicial = alturaInicial;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY()  + alturaInicial)*sin(arc)));
	hp = 50;
	speed.x = 2;
	speed.y = 0;
	orientation = LEFT;
	sp.SetLoop(4, 5);
	knockback.Update(10);
}

Enemy3::~Enemy3()
{

}

void Enemy3::Update(float dt)
{
	Point* playerPos = new Point(Player::player->box.getCenterX(),
			Player::player->box.getCenterY());
	Point* currentPos = new Point(box.getCenterX(), box.getCenterY());

	dmgCD.Update(dt);
	if (knockback.Get() < 0.3)
	{
		if (kbDirection == LEFT)
			rotation -= 18*dt;
		else
			rotation += 18*dt;

		sp.Update(dt);
	}
	else if (currentPos->getDist(*playerPos) <= 600
			&& currentPos->getDist(*playerPos) >= 300) {
		sp.SetLoop(4, 5);
		if (playerPos->x > currentPos->x) {
			orientation = RIGHT;
			sp.SetFlipH(true);
			rotation += 5*dt;
		} else if (playerPos->x < currentPos->x) {
			orientation = LEFT;
			sp.SetFlipH(false);
			rotation -= 5*dt;
		}
		sp.Update(dt);
	} else if(currentPos->getDist(*playerPos) <= 300) {
		sp.SetLoop(0, 13);
		if ((sp.GetCurrentFrame() == 4 || sp.GetCurrentFrame() == 11) && shootcd.Get() > 0.35)
		{
			if (playerPos->x > currentPos->x) {
				orientation = RIGHT;
				sp.SetFlipH(true);
			} else if (playerPos->x < currentPos->x) {
				orientation = LEFT;
				sp.SetFlipH(false);
			}
			Shoot(*playerPos);
			shootcd.Restart();
		}
		sp.Update(dt);
	} else {
		sp.SetFrame(0);
		sp.Update(1);
	}

	somaRotation = planet->somaRotation;
	rotation += somaRotation;

	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));

	knockback.Update(dt);
	shootcd.Update(dt);
}

void Enemy3::Render()
{
	sp.Render(box.getX() + Camera::pos.getX(), box.getY() + Camera::pos.getY(),rotation + 90);
}

bool Enemy3::IsDead()
{
	return (hp <= 0);
}

Sprite Enemy3::getSprite()
{
	return sp;
}

bool Enemy3::Is(string type)
{
	return (type == "Enemy3");
}

void Enemy3::Shoot (Point pos)
{
	Point* pspeed = new Point(box.getCenterX() - pos.getX(),box.getCenterY() - pos.getY());
	float speed = pspeed->magVector();
	float angle = atan(pspeed->getY()/pspeed->getX());
	if(pspeed->getX() > 0){
		angle += 3.141592653;
	}
	delete(pspeed);

	float xBullet;
	float yBullet;

	if(orientation == LEFT)
	{
		if (sp.GetCurrentFrame() == 4)
		{
			xBullet = box.getX();
			yBullet = box.getCenterY();
		}
		else
		{
			xBullet = box.getX()+ box.getW()/2;
			yBullet = box.getCenterY() + box.getH()/2 - 20;
		}
	}
	else
	{
		if (sp.GetCurrentFrame() == 4)
		{
			xBullet = box.getX()+ box.getW();
			yBullet = box.getCenterY();
		}
		else
		{
			xBullet = box.getX() + box.getW()/2;
			yBullet = box.getCenterY() + box.getH()/2 - 20;
		}
	}

	Bullet* bullet = new Bullet(xBullet,yBullet,angle,speed,2000,"img/enemy3_bullet.png",true,4);
	Game::GetInstance().GetCurrentState().AddObject(bullet);
}

void Enemy3::NotifyCollision(GameObject& other)
{
	if ((other.Is("WeaponBroom") && other.attacking) || (other.Is("WeaponSword") && other.attacking)) {

		if (dmgCD.Get() > 0.5) {
			dmgCD.Restart();
			hp -= 10;

			knockback.Restart();

			if (box.getCenterX() < other.box.getCenterX())
				kbDirection = LEFT;
			else
				kbDirection = RIGHT;

			std::cout << "Collision: Weapon>Tank\n";
		}

		if (IsDead()) {
			Player::player->IncXp(100);
			//Sprite* aux = new Sprite("img/enemy_tank_dying.png", 0.2, 1, 9);
			//aux->SetScaleX(0.5);
			//aux->SetScaleY(0.5);
			//aux->SetLoop(0, 6);
			//StillAnimation* animacao = new StillAnimation(box.getCenterX(),
			//		box.getCenterY(), planet, rotation, *aux, 0.2 * 7, true, box.getY()-50);
			//Game::GetInstance().GetCurrentState().AddObject(animacao);
		}
	}
}

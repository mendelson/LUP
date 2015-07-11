#include "EnemyTank.h"
#include "Game.h"

EnemyTank::EnemyTank(float x, float y,GameObject* planet, float initialRotation, float alturaInicial) :
		sp("img/enemy_tank.png", 0.35, 2, 8), speed(), startPos(x, y), dmgCD(), knockback() {
	this->planet = planet;
	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	rotation = initialRotation;
	float arc = rotation*3.1415/180;
	this->alturaInicial = alturaInicial;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 + planet->box.getCenterY() + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 + planet->box.getCenterY()  + alturaInicial)*sin(arc)) - (box.getH()/2));
	hp = 50;
	speed.x = 2;
	speed.y = 0;
	orientation = LEFT;
	sp.SetLoop(0, 7);
	knockback.Update(10);

}

EnemyTank::~EnemyTank() {

}

void EnemyTank::Update(float dt) {
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
			&& currentPos->getDist(*playerPos) >= 100) {
		sp.SetLoop(0, 7);
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
	} else if(currentPos->getDist(*playerPos) <= 100) {
		sp.SetLoop(8, 15);
		sp.Update(dt);
	} else {
		sp.SetFrame(7);
		sp.Update(1);
	}

	if (sp.GetCurrentFrame() == 3 || sp.GetCurrentFrame() == 5 || sp.GetCurrentFrame() == 11 || sp.GetCurrentFrame() == 13)
		attacking = true;
	else
		attacking = false;

	somaRotation = planet->somaRotation;
	rotation += somaRotation;

	float arc = rotation*3.1415/180;
	box.setX(planet->box.getCenterX() + ((planet->box.getW()/2 - 300 + alturaInicial)*cos(arc)) - (box.getW()/2));
	box.setY(planet->box.getCenterY()  + ((planet->box.getH()/2 - 300 + alturaInicial)*sin(arc)) - (box.getH()/2));

	knockback.Update(dt);
}

void EnemyTank::Render() {
	sp.Render(box.getX() + Camera::pos.getX(), box.getY() + Camera::pos.getY(),rotation + 90);
}

bool EnemyTank::IsDead() {
	return (hp <= 0);
}

Sprite EnemyTank::getSprite() {
	return sp;
}

bool EnemyTank::Is(string type) {
	return (type == "EnemyTank");
}

void EnemyTank::NotifyCollision(GameObject& other) {
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
			Sprite* aux = new Sprite("img/enemy_tank_dying.png", 0.2, 1, 9);
			aux->SetScaleX(0.5);
			aux->SetScaleY(0.5);
			aux->SetLoop(0, 6);
			StillAnimation* animacao = new StillAnimation(box.getCenterX(),
					box.getCenterY(), planet, rotation, *aux, 0.2 * 7, true, box.getY()-50);
			Game::GetInstance().GetCurrentState().AddObject(animacao);
		}
	}
}

void EnemyTank::Move(Point dest)
{

}

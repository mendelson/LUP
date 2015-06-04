#include "EnemyTank.h"
#include "Game.h"

EnemyTank::EnemyTank(float x, float y) :
		sp("img/enemy_tank.png", 0.35, 1, 8), speed(), startPos(x, y), dmgCD() {
	int novox = x - (sp.GetFrameWidth() / 2);
	int novoy = y - (sp.GetHeight() / 2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	hp = 50;
	speed.x = 2;
	speed.y = 0;
	orientation = LEFT;
	sp.SetLoop(0, 7);
	startRotation = 25;
}

EnemyTank::~EnemyTank() {

}

void EnemyTank::Update(float dt) {
	Point* playerPos = new Point(Player::player->box.getCenterX(),
			Player::player->box.getCenterY());
	Point* currentPos = new Point(box.getCenterX(), box.getCenterY());

	dmgCD.Update(dt);

	if (currentPos->getDist(*playerPos) <= 300
			&& currentPos->getDist(*playerPos) >= 30) {
		if (playerPos->x > currentPos->x) {
			orientation = RIGHT;
			sp.SetFlipH(true);
			box.setX(box.getX() + speed.x);
		} else if (playerPos->x < currentPos->x) {
			orientation = LEFT;
			sp.SetFlipH(false);
			box.setX(box.getX() - speed.x);
		}

		sp.Update(dt);
	} else if (currentPos->getDist(startPos) > speed.x) {
		if (startPos.x > currentPos->x) {
			orientation = RIGHT;
			sp.SetFlipH(true);
			box.setX(box.getX() + speed.x);
		} else if (startPos.x < currentPos->x) {
			orientation = LEFT;
			sp.SetFlipH(false);
			box.setX(box.getX() - speed.x);
		}
		sp.Update(dt);
	} else {
		sp.SetFrame(7);
		sp.Update(1);
	}

	if (sp.GetCurrentFrame() >= 2 && sp.GetCurrentFrame() <= 6)
		attacking = true;
	else
		attacking = false;
	rotation = startRotation + Camera::rotation;
	box.y = startPos.y + abs(Game::GetInstance().GetCurrentState().raioPlaneta*sin(rotation/180)/2);
}

void EnemyTank::Render() {
	sp.Render(box.getX() + Camera::pos.getX(), box.getY() + Camera::pos.getY(),30 + rotation);
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
	if (other.Is("Weapon") && other.attacking) {
		if (dmgCD.Get() > 0.5) {
			dmgCD.Restart();
			hp -= 10;
		}

		if (IsDead()) {
			Player::player->IncXp(100);
			Sprite* aux = new Sprite("img/enemy_tank_dying.png", 0.2, 1, 9);
			aux->SetLoop(0, 6);
			StillAnimation* animacao = new StillAnimation(box.getCenterX(),
					box.getCenterY(), rotation, *aux, 0.2 * 7, true);
			Game::GetInstance().GetCurrentState().AddObject(animacao);
		}
	}
}

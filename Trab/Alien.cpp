/*
 * Alien.cpp
 *
 *  Created on: 15/04/2015
 *      Author: Vitor
 */

#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Penguins.h"

int Alien::alienCount = 0;

Alien::Alien(float x, float y, int nMinions,int cooldown): sp("img/alien.png"),speed(),shootCoolDown(){
	hp = 30;
	int novox = x - (sp.GetWidth()/2);
	int novoy = y - (sp.GetHeight()/2);
	box.setX(novox);
	box.setY(novoy);
	box.setH(sp.GetHeight());
	box.setW(sp.GetWidth());
	//srand(time(NULL));
	float arc = 6.283185306/nMinions;
	float scale;
	for(int i=0;i<nMinions;i++){
	float angle = arc*i;
		Minion* minion = new Minion(this, angle);
		minionArray.emplace_back(*minion);

	}
	alienCount++;
	alienState = RESTING;
	this->cooldown = cooldown;
}

Alien::~Alien(){
	alienCount--;
}

Alien::Action::Action(ActionType type,float x,float y):pos(x,y){
	this->type = type;
}

void Alien::Update(float dt){
	if(Penguins::player == NULL){
		return;
	}
	rotation -= 18*dt;
	float x = Penguins::player->box.getCenterX();
	float y = Penguins::player->box.getCenterY();
	if(alienState == RESTING){
		shootCoolDown.Update(dt);
		if(shootCoolDown.Get() > cooldown){
			shootCoolDown.Restart();
			alienState = MOVING;
			Action* action = new Action(Action::MOVE,x,y);
			taskQueue.push(*action);
		}
	}else{
		if(!taskQueue.empty()){
			Action action = taskQueue.front();
			//Action action = taskQueue.queue();
			if(action.type == Action::MOVE){
				speed = *(new Point(action.pos.getX()- box.getCenterX(),action.pos.getY() - box.getCenterY()));
				Point* ponto = new Point(Game::GetInstance().GetDeltaTime()*speed.getX(),Game::GetInstance().GetDeltaTime()*speed.getY());
				box.somaPonto(*ponto);
				if(speed.magVector() <= 450){
					taskQueue.pop();
					Action* action = new Action(Action::SHOOT,x,y);
					taskQueue.push(*action);
				}
				delete(&ponto);
				delete(&speed);
			}
			if(action.type == Action::SHOOT){
				alienState = RESTING;
				//int i = rand()%minionArray.size();

				Point* pos = new Point(action.pos.getX(),action.pos.getY());
				float minDist;
				float minI = 0;
				Point* aux = new Point(minionArray[0].box.getCenterX(),minionArray[0].box.getCenterY());
				minDist = aux->getDist(*pos);
				delete(aux);
				for(int i=1;i<minionArray.size();i++){
					aux = new Point(minionArray[i].box.getCenterX(),minionArray[i].box.getCenterY());
					if(aux->getDist(*pos) < minDist){
						minDist = aux->getDist(*pos);
						minI = i;
					}
					delete(aux);
				}
				minionArray[minI].Shoot(*pos);
				delete(pos);
				taskQueue.pop();
			}
		}
	}
	for(int i=0;i<minionArray.size();i++){
			minionArray[i].Update(dt);
	}
}

void Alien::Render(){
	sp.Render(box.getX() +  Camera::pos.getX(),box.getY() +  Camera::pos.getY(),rotation);
	for(int i=0;i<minionArray.size();i++){
		minionArray[i].Render();
	}

}

bool Alien::IsDead(){
	if(hp <= 0){
		return true;
	}
	return false;
}

Sprite Alien::getSprite(){
	return sp;
}

bool Alien::Is(string type){
	return (type == "Alien");
}

void Alien::NotifyCollision(GameObject& other){

	if(other.Is("Bullet") ){
		Bullet& bull = dynamic_cast<Bullet&>(other);
		if(!bull.targetsPlayer){
			hp-= (rand()%9 + 1);
		if(IsDead()){
						Sprite* sp = new Sprite("img/aliendeath.png",4,0.3);
						StillAnimation* animacao = new StillAnimation(box.getCenterX() ,box.getCenterY(),rotation,*sp,0.3*4,true);
						Game::GetInstance().GetCurrentState().AddObject(animacao);
						Sound* sound = new Sound("audio/boom.wav");
						sound->Play(0);
						for(int i=0;i<minionArray.size();i++){
							Sprite* aux = new Sprite("img/miniondeath.png",4,0.3);
							StillAnimation* animacao = new StillAnimation(minionArray[i].box.getCenterX(),minionArray[i].box.getCenterY(),rotation,*aux,0.3*4,true);
							Game::GetInstance().GetCurrentState().AddObject(animacao);
						}
						//se e 1, e o ultimo alien
						if(alienCount <= 1){
							Camera::Unfollow();
							Game::GetInstance().GetCurrentState().SetPopRequested(true);
							StateData* stateData = new StateData();
							stateData->playerVictory = true;
							State* state = new EndState(*stateData);
							Game::GetInstance().Push(state);
						}
					}
		}

	}

}

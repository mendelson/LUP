/*
 * State.cpp
 *
 *  Created on: 21/03/2015
 *      Author: Vitor
 */

#include "StageState.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"
#include "Collision.h"

StageState::StageState() : bg("img/ocean.jpg") ,tileSet(60,60,"img/plataformas2.png"), tileMap("map/tileMapPlataforma.txt",&tileSet),music("audio/stageState.ogg"){
	quitRequested = false;
	srand( (unsigned int)time(NULL));
	/*
	GameObject* penguin = new Penguins(1920,100);
	objectArray.emplace_back(penguin);
	Camera::Follow(penguin);
	*/

	GameObject* player = new Player(1920,100);
	objectArray.emplace_back(player);
	Camera::Follow(player);

	GameObject* weapon = new Weapon("img/lup_vassoura.png");
	objectArray.emplace_back(weapon);

	GameObject* tank = new EnemyTank (2120, 100);
	objectArray.emplace_back(tank);

	GameObject* support = new Support ();
	objectArray.emplace_back(support);

	//GameObject* alien = new Alien(512,300,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien);
	//GameObject* alien2 = new Alien(300,512,5,(rand()%5) + 3);
	//objectArray.emplace_back(alien2);
	//GameObject* alien3 = new Alien(1000,1000,5,(rand()%5) + dd3);
	//objectArray.emplace_back(alien3);



}

void StageState::Update(float dt){
//	if(SDL_QuitRequested()){
//		quitRequested = true;
//	}

	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
	{
		std::cout << InputManager::GetInstance().GetMouseX() - Camera::pos.getX() << std::endl;
		std::cout << InputManager::GetInstance().GetMouseY() - Camera::pos.getY() << std::endl;
	}

	 Camera::Update(dt);
	 quitRequested = InputManager::GetInstance().QuitRequested();
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	UpdateArray(dt);

}


void StageState::Render(){
	bg.Render(0,0);
	tileMap.RenderLayer(0,Camera::pos.getX(),Camera::pos.getY());
	tileMap.RenderLayer(1,Camera::pos.getX(),Camera::pos.getY());
	RenderArray();
	tileMap.Render(Camera::pos.getX(),Camera::pos.getY());

}

StageState::~StageState(){
	objectArray.clear();
}

void StageState::Pause(){
	music.Stop();

}

void StageState::Resume(){
	//music.Play(-1);
}

float StageState::getTileMapHeight(int x,int y){
	return tileMap.GetFloorHeight(x,y,Camera::pos.getX());
}

float StageState::getTileMapAngle(int x){
	return tileMap.GetAngle(x,Camera::pos.getX());
}

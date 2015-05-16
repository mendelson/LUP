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

StageState::StageState() : bg("img/ocean.jpg") ,tileSet(64,64,"img/tileset.png"), tileMap("map/tileMap.txt",&tileSet),music("audio/stageState.ogg"){
	quitRequested = false;
	srand( (unsigned int)time(NULL));

}

void StageState::Update(float dt){
//	if(SDL_QuitRequested()){
//		quitRequested = true;
//	}
	 Camera::Update(dt);
	 quitRequested = InputManager::GetInstance().QuitRequested();
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	UpdateArray(dt);

}


void StageState::Render(){
	bg.Render(0,0);
	tileMap.RenderLayer(0,Camera::pos.getX(),Camera::pos.getY());
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
	music.Play(-1);
	Camera::pos.x = -1920;
}

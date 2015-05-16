/*
 * TitleState.cpp
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */

#include "TitleState.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"

TitleState::TitleState():bg("img/title.jpg"),timer(),text("font/Call me maybe.ttf",30,Text::SOLID,"Pressione espaco para continuar",{0,0,0},Game::GetInstance().getWidth()/2,Game::GetInstance().getHeight()/1.5){
	//text = NULL;
	text.SetPos(Game::GetInstance().getWidth()/2,Game::GetInstance().getHeight()/1.5,true,true);
}

void TitleState::Update(float dt){
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested =  InputManager::GetInstance().QuitRequested();
	if(InputManager::GetInstance().IsKeyDown(SPACE_KEY)){
		State* stageState = new StageState();
		Game::GetInstance().Push(stageState);
	}
	timer.Update(dt);
	if(timer.Get() > 1){
		timer.Restart();
	}

}

void TitleState::Render(){
	bg.Render(0,0);
	if(timer.Get() <= 0.5){
		text.Render();
	}
}


void TitleState::Pause(){

}

void TitleState::Resume(){
	text.SetPos(Game::GetInstance().getWidth()/2,Game::GetInstance().getHeight()/1.5,true,true);
}

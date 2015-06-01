/*
 * EndState.cpp
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */
#include "EndState.h"
#include "InputManager.h"
#include "Game.h"

EndState::EndState(StateData stateData) : bg(), music(), instruction("font/Call me maybe.ttf",20,Text::SOLID,"Voce venceu!",{255,255,255},0,Game::GetInstance().getHeight() - 40) {
	if(stateData.playerVictory){
		bg.Open("img/win.jpg");
		music.Open("audio/endStateWin.ogg");
		instruction.SetText("Voce venceu! Pressione espaco para jogar denovo ou esc para voltar a tela inicial");
	}else{
		bg.Open("img/lose.jpg");
		music.Open("audio/endStateLose.ogg");
		instruction.SetText("Voce perdeu! Pressione espaco para jogar denovo ou esc para voltar a tela inicial");
	}
}



void EndState::Update(float dt){
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();
	if(InputManager::GetInstance().IsKeyDown(SPACE_KEY)){
			State* stageState = new StageState();
			Game::GetInstance().Push(stageState);
			popRequested = true;
		}
}

void EndState::Render(){
	bg.Render(0,0);
	instruction.Render();
}

void EndState::Pause(){
	music.Stop();
}

void EndState::Resume(){
	music.Play(-1);
}

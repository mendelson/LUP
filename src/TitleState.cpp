/*
 * TitleState.cpp
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */

#include "TitleState.h"

#include <SDL_pixels.h>
#include <iostream>

#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

TitleState::TitleState() :
		bg("img/title.jpg"), timer() {

	focus = 0;
	initialize = true;

	menuYStartPosition = Game::GetInstance().getWidth() / 3.5;

	textVector.emplace_back(new Text("font/Call me maybe.ttf", 30, Text::SOLID, "JOGAR", { 0, 0, 0 }, 0, 0));
	textVector.emplace_back(new Text("font/Call me maybe.ttf", 30, Text::SOLID, "CREDITOS", { 0, 0, 0 }, 0, 0));
	textVector.emplace_back(new Text("font/Call me maybe.ttf", 30, Text::SOLID, "SAIR", { 0, 0, 0 }, 0, 0));
	textVector[0]->SetPos(30, menuYStartPosition, true, true);
	textVector[1]->SetPos(20, menuYStartPosition + 40, true, true);
	textVector[2]->SetPos(10, menuYStartPosition + 80, true, true);
}

TitleState::~TitleState() {
	textVector.clear();
}

void TitleState::Update(float dt) {
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

	if (initialize) {
		initialize = false;

		for (int i = 0; i < (int) textVector.size(); i++) {
			if (textVector[i]->GetXCenter() < Game::GetInstance().getWidth() / 2) {
				textVector[i]->SetPos(textVector[i]->GetXCenter() + 0.0000001, menuYStartPosition + i * 40, true, true);
				initialize = true;
			} else {
				textVector[i]->SetPos(Game::GetInstance().getWidth() / 2, menuYStartPosition + i * 40, true, true);
			}
		}
	}

	if (!initialize) {
		if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY)) {
			focus--;

			if (focus < 0) {
				focus = 0;
			}
		} else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)) {
			focus++;

			if (focus > (int) textVector.size() - 1) {
				focus = textVector.size() - 1;
			}
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 0) {
			State* stageState = new StageState();
			Game::GetInstance().Push(stageState);
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 2) {
			quitRequested = true;
		}

		timer.Update(dt);
		if (timer.Get() > 1) {
			timer.Restart();
		}
	}
}

void TitleState::Render() {
	bg.Render(0, 0);

	for (int i = 0; i < (int) textVector.size(); i++) {
		if (initialize) {
			textVector[i]->Render();
		} else if (i != focus) {
			textVector[i]->SetColor( { 0, 0, 0 });
			textVector[i]->Render();
		} else if (timer.Get() <= 0.6) {
			textVector[i]->SetColor( { 0, 0, 255 });
			textVector[i]->Render();
		}
	}
}

void TitleState::Pause() {
}

void TitleState::Resume() {
	focus = 0;
	initialize = true;

	textVector.clear();

	textVector.emplace_back(new Text("font/Call me maybe.ttf", 30, Text::SOLID, "JOGAR", { 0, 0, 0 }, 0, 0));
	textVector.emplace_back(new Text("font/Call me maybe.ttf", 30, Text::SOLID, "CREDITOS", { 0, 0, 0 }, 0, 0));
	textVector.emplace_back(new Text("font/Call me maybe.ttf", 30, Text::SOLID, "SAIR", { 0, 0, 0 }, 0, 0));
	textVector[0]->SetPos(30, menuYStartPosition, true, true);
	textVector[1]->SetPos(20, menuYStartPosition + 40, true, true);
	textVector[2]->SetPos(10, menuYStartPosition + 80, true, true);
}

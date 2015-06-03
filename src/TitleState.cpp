#include "TitleState.h"
#include <SDL_pixels.h>
#include <iostream>

#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

const std::string FONT_FILE = "font/OpenSans-Bold.ttf";
const int ITEMS_DISTANCE = 50;

TitleState::TitleState() :
		bg("img/fundo.png"), selector("img/planeta_menu.png"), timer() {

	focus = 0;
	initialize = true;

	menuYStartPosition = Game::GetInstance().getHeight() / 1.5;
	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "JOGAR", { 255,
			255, 255 }, 0, 0));
	textVector.emplace_back(
			new Text(FONT_FILE, 30, Text::SOLID, "INSTRUCOES DE JOGO", { 255,
					255, 255 }, 0, 0));
	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "CREDITOS", {
			255, 255, 255 }, 0, 0));
	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "SAIR", { 255,
			255, 255 }, 0, 0));

	for (unsigned int i = 0; i < textVector.size(); i++) {
		textVector[i]->SetPos(0, menuYStartPosition + i * ITEMS_DISTANCE, true,
				true);
		if(i == 0){
		cout << textVector[i]->GetXCenter() << endl;
		}
	}
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
				if(i == 0) {
					cout << textVector[i]->GetXCenter() << endl;
				}
				textVector[i]->SetPos(textVector[i]->GetXCenter() + 1, menuYStartPosition + i * ITEMS_DISTANCE, true, true);
				initialize = true;
			} else {
				textVector[i]->SetPos(Game::GetInstance().getWidth() / 2, menuYStartPosition + i * ITEMS_DISTANCE, true, true);
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

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 3) {
			quitRequested = true;
		}

		timer.Update(dt);
		if (timer.Get() > 1) {
			timer.Restart();
		}
	}
}

void TitleState::Render() {
	bg.Render(0, -100);

	for (int i = 0; i < (int) textVector.size(); i++) {
		if (initialize) {
			textVector[i]->Render();
		} else if (i != focus) {
			textVector[i]->Render();
		} else {
			selector.Render(textVector[i]->GetX() - 60,
					textVector[i]->GetY() - 10);

			if (timer.Get() <= 0.6) {
				textVector[i]->Render();
			}
		}
	}
}

void TitleState::Pause() {
	textVector.clear();
}

void TitleState::Resume() {
	focus = 0;
	initialize = true;

	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "JOGAR", { 255,
			255, 255 }, 0, 0));
	textVector.emplace_back(
			new Text(FONT_FILE, 30, Text::SOLID, "INSTRUCOES DE JOGO", { 255,
					255, 255 }, 0, 0));
	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "CREDITOS", {
			255, 255, 255 }, 0, 0));
	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "SAIR", { 255,
			255, 255 }, 0, 0));

	for (unsigned int i = 0; i < textVector.size(); i++) {
		textVector[i]->SetPos(0, menuYStartPosition + i * ITEMS_DISTANCE, true,
				true);
	}
}

#include "TitleState.h"

#include <iostream>
#include <sstream>
#include <string>

#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

const std::string FONT_FILE = "font/OpenSans-Bold.ttf";
const int ITEMS_DISTANCE = 50;
const int NUMBER_OF_MENU_PLANETS = 3;

TitleState::TitleState() :
		bg("img/fundo.png"), timer(),music("audio/titlescreenlup.ogg") {

	focus = 0;
	initialize = true;

	menuYStartPosition = Game::GetInstance().getHeight() / 1.5;
	mountMainMenu();

	for (unsigned int i = 0; i < NUMBER_OF_MENU_PLANETS; i++) {
		std::stringstream sstm;
		sstm << "img/planeta_menu" << i << ".png";
		std::string planetFile = sstm.str();

		selector.emplace_back(new Sprite(planetFile));
	}
	music.Play(-1);
}

TitleState::~TitleState() {
	textVector.clear();
	selector.clear();
}

void TitleState::Update(float dt) {
	//popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

	if (initialize) {
		initialize = false;

		for (int i = 0; i < (int) textVector.size(); i++) {
			if (textVector[i]->GetXCenter()
					< Game::GetInstance().getWidth() / 2) {
				if (i == 0) {
					cout << textVector[i]->GetXCenter() << endl;
				}
				textVector[i]->SetPos(textVector[i]->GetXCenter() + 1,
						menuYStartPosition + i * ITEMS_DISTANCE, true, true);
				initialize = true;
			} else {
				textVector[i]->SetPos(Game::GetInstance().getWidth() / 2,
						menuYStartPosition + i * ITEMS_DISTANCE, true, true);
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

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == (int) (textVector.size() - 1)) { //TODO: comparar texto em vez de número
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
			if (i % 2 == 0) {
				selector[i % NUMBER_OF_MENU_PLANETS]->Render(
						textVector[i]->GetX() + textVector[i]->GetWidth(),
						textVector[i]->GetY() - 10);
			} else {
				selector[i % NUMBER_OF_MENU_PLANETS]->Render(textVector[i]->GetX() - 60,
						textVector[i]->GetY() - 10);
			}

			if (timer.Get() <= 0.6) {
				textVector[i]->Render();
			}
		}
	}
}

void TitleState::Pause() {
	textVector.clear();
	music.Stop();
}

void TitleState::Resume() {
	focus = 0;
	initialize = true;

	mountMainMenu();
	music.Play(-1);
}

void TitleState::mountMainMenu() {
	textVector.clear();

	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "JOGAR", { 255,
			255, 255 }, 0, 0));
	textVector.emplace_back(
			new Text(FONT_FILE, 30, Text::SOLID, "INSTRUCOES E CREDITOS", { 255,
					255, 255 }, 0, 0));
	textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "SAIR", { 255,
			255, 255 }, 0, 0));

	for (unsigned int i = 0; i < textVector.size(); i++) {
		textVector[i]->SetPos(0, menuYStartPosition + i * ITEMS_DISTANCE, true,
				true);
		if (i == 0) {
			cout << textVector[i]->GetXCenter() << endl;
		}
	}
}

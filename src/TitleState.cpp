#include "TitleState.h"

#include <SDL_keycode.h>
#include <iostream>
#include <sstream>
#include <string>

#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

//const std::string FONT_FILE = "font/OpenSans-Bold.ttf";
//const int ITEMS_DISTANCE = 50;
//const int NUMBER_OF_MENU_PLANETS = 3;
const int NUMBER_OF_MENU_ITEMS = 4;

TitleState::TitleState() :
		bg("img/fundo.png"), opening("img/cut-scene-1.png"), instructions(
				"img/instructions.png"), menuOptions("img/menu-options.png", 0,
				1, 5), credits("img/credits.png"), timer(), timerSupport(), music(
				"audio/titlescreenlup.ogg") {

	menuOptions.SetLoop(0, 4);
	showInstructions = false;
	showCredits = false;
	frame = 0;
	opening.SetFrame(frame);
	startMenu = false;
	focus = 0;
	//initialize = true;

	//menuYStartPosition = Game::GetInstance().getHeight() / 1.5;
	//mountMainMenu();

	/*for (unsigned int i = 0; i < NUMBER_OF_MENU_PLANETS; i++) {
	 std::stringstream sstm;
	 sstm << "img/planeta_menu" << i << ".png";
	 std::string planetFile = sstm.str();

	 selector.emplace_back(new Sprite(planetFile));
	 }*/
	music.Play(-1);
}

TitleState::~TitleState() {
	//textVector.clear();
	//selector.clear();
}

void TitleState::Update(float dt) {
	//popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();
	timerSupport.Update(dt);

	if (!startMenu) {
		startMenu = InputManager::GetInstance().KeyPress(SDLK_SPACE);

		if (frame >= 0 && frame <= 2) {
			if (timerSupport.Get() > 3.5) {
				frame++;

				switch (frame) {
				case 1:
					opening.Open("img/cut-scene-2.png");
					timerSupport.Restart();
					break;
				case 2:
					opening.Open("img/cut-scene-4.png");
					timerSupport.Restart();
					break;
				default:
					break;
				}
			}
		} else {
			cout << "ae" << endl;
			startMenu = true;
		}
	} else {
		/*if (initialize) {
		 initialize = false;
		 focus = 0;

		 for (int i = 0; i < (int) textVector.size(); i++) {
		 if (textVector[i]->GetXCenter()
		 < Game::GetInstance().getWidth() / 2) {
		 textVector[i]->SetPos(textVector[i]->GetXCenter() + 1,
		 menuYStartPosition + i * ITEMS_DISTANCE, true,
		 true);
		 initialize = true;
		 } else {
		 textVector[i]->SetPos(Game::GetInstance().getWidth() / 2,
		 menuYStartPosition + i * ITEMS_DISTANCE, true,
		 true);
		 }
		 }
		 }*/

		//if (!initialize) {
		if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY)
				&& !showInstructions) {
			focus--;

			if (focus < 0) {
				focus = NUMBER_OF_MENU_ITEMS - 1;
			}
		} else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)
				&& !showInstructions) {
			focus++;

			if (focus > NUMBER_OF_MENU_ITEMS - 1) {
				focus = 0;
			}
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 0
				&& !showInstructions && !showCredits
				&& timerSupport.Get() > 0.5) {
			State* stageState = new StageState();
			Game::GetInstance().Push(stageState);
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 1
				&& !showInstructions && !showCredits
				&& timerSupport.Get() > 0.5) {
			showInstructions = true;
			timerSupport.Restart();
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 2
				&& !showInstructions && !showCredits
				&& timerSupport.Get() > 0.5) {
			showCredits = true;
			timerSupport.Restart();
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY)
				&& focus == NUMBER_OF_MENU_ITEMS - 1 && !showInstructions
				&& !showCredits && timerSupport.Get() > 0.5) {
			quitRequested = true;
		}

		timer.Update(dt);
		if (timer.Get() > 1) {
			timer.Restart();
		}

		if (showInstructions
				&& InputManager::GetInstance().IsKeyDown(RETURN_KEY)
				&& timerSupport.Get() > 0.5) {
			timerSupport.Restart();
			//initialize = true;
			showInstructions = false;
			focus = 1;
		}

		if (showCredits && InputManager::GetInstance().IsKeyDown(RETURN_KEY)
				&& timerSupport.Get() > 0.5) {
			timerSupport.Restart();
			//initialize = true;
			showCredits = false;
			focus = 2;
		}
		//}

		menuOptions.SetFrame(focus);
		menuOptions.Update(1);

		cout << menuOptions.GetCurrentFrame() << endl;
	}
}

void TitleState::Render() {
	if (!startMenu) {
		opening.Render(0, 0);
	} else if (showInstructions) {
		instructions.Render(0, 0);
	} else if (showCredits) {
		credits.Render(0, 0);
	} else {
		bg.Render(0, -100);

		menuOptions.Render(310, 300);

		/*for (int i = 0; i < (int) textVector.size(); i++) {
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
		 selector[i % NUMBER_OF_MENU_PLANETS]->Render(
		 textVector[i]->GetX() - 60,
		 textVector[i]->GetY() - 10);
		 }

		 if (timer.Get() <= 0.6) {
		 textVector[i]->Render();
		 }
		 }
		 }*/
	}
}

void TitleState::Pause() {
	//textVector.clear();
	music.Stop();
}

void TitleState::Resume() {
	focus = 0;
	//initialize = true;

	//mountMainMenu();
	music.Play(-1);
}

/*void TitleState::mountMainMenu() {
 textVector.clear();

 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "JOGAR", { 255,
 255, 255 }, 0, 0));
 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "INSTRU��ES", {
 255, 255, 255 }, 0, 0));
 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "CR�DITOS", {
 255, 255, 255 }, 0, 0));
 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "SAIR", { 255,
 255, 255 }, 0, 0));

 for (unsigned int i = 0; i < textVector.size(); i++) {
 textVector[i]->SetPos(0, menuYStartPosition + i * ITEMS_DISTANCE, true,
 true);
 }
 }*/

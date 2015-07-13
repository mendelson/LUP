#include "TitleState.h"

#include <SDL_keycode.h>
#include <sstream>
#include <string>

#include "FinalState.h"
#include "Game.h"
#include "InputManager.h"
#include "StageState.h"

//const std::string FONT_FILE = "font/OpenSans-Bold.ttf";
//const int ITEMS_DISTANCE = 50;
//const int NUMBER_OF_MENU_PLANETS = 3;
const int NUMBER_OF_MENU_ITEMS = 4;
const unsigned int NUMBER_FRAMES_INITIAL_ANIMATION = 93;
const unsigned int NUMBER_FRAMES_LOGO = 214;
const float FRAME_TIME_INITIAL_ANIMATION = 0.02; // 1 / 30;
const float FRAME_TIME_LOGO = 0.04;

TitleState::TitleState() :
		bg("img/fundo.png"), opening("img/cut-scene-1.png"), instructions(
				"img/instructions.png"), menuOptions("img/menu-options.png", 0,
				1, 5), credits("img/credits.png"), blank("img/blank.png"), timer(), timerSupport(), timerLogo(), menuSong(
				"audio/menuLoop.ogg", false), menuIntroSong(
				"audio/menuIntro.ogg"), introIntroSong(
				"audio/introIntroSong.ogg"), itemSelection(
				"audio/itemSelection.wav"), itemChosen("audio/select.wav") {

	popRequested = false;
	quitRequested = false;
	menuOptions.SetLoop(0, 4);
	showInstructions = false;
	showCredits = false;
	frame = 0;
	frameLogo = 0;
	opening.SetFrame(frame);
	startMenu = false;
	focus = 0;
	initializeMenuSong = true;
	initializeMenuIntroSong = true;
	updateTimer = false;

	//menuYStartPosition = Game::GetInstance().getHeight() / 1.5;
	//mountMainMenu();

	// Initial animation
	for (unsigned int i = 0; i < NUMBER_FRAMES_INITIAL_ANIMATION; i++) {
		std::stringstream sstm;
		sstm << "img/cut-scene-5/Cut_Scene_5_000" << i << ".png";
		std::string frameFile = sstm.str();

		selector.emplace_back(new Sprite(frameFile));
	}

	// Logo animation
	for (unsigned int i = 0; i < NUMBER_FRAMES_LOGO; i++) {
		std::stringstream sstm;

		if (i >= 100) {
			sstm << "img/logo_animation/Logo_Animation_2_00" << i << ".png";
		} else if (i >= 10 && i <= 99) {
			sstm << "img/logo_animation/Logo_Animation_2_000" << i << ".png";
		} else if (i >= 0 && i <= 9) {
			sstm << "img/logo_animation/Logo_Animation_2_0000" << i << ".png";
		}

		std::string frameFile = sstm.str();

		logo.emplace_back(new Sprite(frameFile));
	}

	introIntroSong.Play(1);
}

TitleState::~TitleState() {
	//textVector.clear();
	introIntroSong.Stop();
	menuSong.Stop();
	menuIntroSong.Stop();

	opening.freeMe();

	for (unsigned int i = 0; i < selector.size() - 1; i++) {
		selector[i]->freeMe();
	}
	selector.clear();

	for (unsigned int i = 0; i < 100; i++) {
		logo[i]->freeMe();
	}
	for (unsigned int i = 100; i < 200; i++) {
		logo[i]->freeMe();
	}
	for (unsigned int i = 200; i < logo.size() - 1; i++) {
		logo[i]->freeMe();
	}
	logo.clear();
}

void TitleState::Update(float dt) {
	//popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	quitRequested = InputManager::GetInstance().QuitRequested();

	timerSupport.Update(dt);
	if (updateTimer) {
		timer.Update(dt);
	}

	if (!startMenu) {
		startMenu = InputManager::GetInstance().KeyPress(SDLK_SPACE);

		if (frame == 0) {
			if (timerSupport.Get() > 3) {
				frame++;
				timerSupport.Restart();
			}
		} else if (frame <= 4) {
			if (timerSupport.Get() > 7) {
				frame++;

				switch (frame) {
				case 2:
					opening.Open("img/cut-scene-2.png");
					timerSupport.Restart();
					break;
				case 3:
					opening.Open("img/cut-scene-3.png");
					timerSupport.Restart();
					break;
				case 4:
					opening.Open("img/cut-scene-4.png");
					timerSupport.Restart();
					break;
				default:
					timerSupport.Restart();
					break;
				}
			}
		} else {
			if (initializeMenuSong || initializeMenuIntroSong) {
				if (!initializeMenuIntroSong && timer.Get() >= 16) {
					//menuSong.Open("audio/menuLoop.ogg", false);
					introIntroSong.Stop();
					menuSong.Play(-1);
					initializeMenuSong = false;
				} else if (initializeMenuIntroSong) {
					updateTimer = true;
					introIntroSong.Stop();
					menuIntroSong.Play(1);
					initializeMenuIntroSong = false;
				}
			}

			if (timerSupport.Get() >= FRAME_TIME_INITIAL_ANIMATION) {
				frame++;
				timerSupport.Restart();
			}

			if (frame - 5 >= NUMBER_FRAMES_INITIAL_ANIMATION) {
				startMenu = true;
				//selector.clear();
			}
		}
	} else {
		if (initializeMenuSong || initializeMenuIntroSong) {
			if (!initializeMenuIntroSong && timer.Get() >= 16) {
				//menuSong.Open("audio/menuLoop.ogg", false);
				introIntroSong.Stop();
				menuSong.Play(-1);
				initializeMenuSong = false;
			} else if (initializeMenuIntroSong) {
				updateTimer = true;
				introIntroSong.Stop();
				menuIntroSong.Play(1);
				initializeMenuIntroSong = false;
			}
		}

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

		//Logo animation
		timerLogo.Update(dt);
		if (timerLogo.Get() >= FRAME_TIME_LOGO) {
			frameLogo++;
			timerLogo.Restart();
		}

		if (frameLogo < 0) {
			frameLogo = 0;
		}

		if (frameLogo >= NUMBER_FRAMES_INITIAL_ANIMATION) {
			frameLogo = NUMBER_FRAMES_INITIAL_ANIMATION - 1;
		}

		//if (!initialize) {
		if (InputManager::GetInstance().KeyPress(UP_ARROW_KEY)
				&& !showInstructions) {
			itemSelection.Play(1);

			focus--;

			if (focus < 0) {
				focus = NUMBER_OF_MENU_ITEMS - 1;
			}
		} else if (InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)
				&& !showInstructions) {
			itemSelection.Play(1);

			focus++;

			if (focus > NUMBER_OF_MENU_ITEMS - 1) {
				focus = 0;
			}
		}

		// CHEAT
		if (InputManager::GetInstance().IsKeyDown(SDLK_F2)) {
			itemChosen.Play(1);
			State* finalState = new FinalState();
			Game::GetInstance().Push(finalState);
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 0
				&& !showInstructions && !showCredits
				&& timerSupport.Get() > 0.5) {
			itemChosen.Play(1);
			State* stageState = new StageState();
			Game::GetInstance().Push(stageState);
			/*State* cutScene = new CutScene1();
			 Game::GetInstance().Push(cutScene);*/
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 1
				&& !showInstructions && !showCredits
				&& timerSupport.Get() > 0.5) {
			itemChosen.Play(1);
			showInstructions = true;
			timerSupport.Restart();
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY) && focus == 2
				&& !showInstructions && !showCredits
				&& timerSupport.Get() > 0.5) {
			itemChosen.Play(1);
			showCredits = true;
			timerSupport.Restart();
		}

		if (InputManager::GetInstance().IsKeyDown(RETURN_KEY)
				&& focus == NUMBER_OF_MENU_ITEMS - 1 && !showInstructions
				&& !showCredits && timerSupport.Get() > 0.5) {
			itemChosen.Play(1);
			quitRequested = true;
		}

		if (showInstructions
				&& InputManager::GetInstance().IsKeyDown(RETURN_KEY)
				&& timerSupport.Get() > 0.5) {
			itemChosen.Play(1);
			timerSupport.Restart();
			//initialize = true;
			showInstructions = false;
			focus = 1;
			frameLogo = 0;
		}

		if (showCredits && InputManager::GetInstance().IsKeyDown(RETURN_KEY)
				&& timerSupport.Get() > 0.5) {
			itemChosen.Play(1);
			timerSupport.Restart();
			//initialize = true;
			showCredits = false;
			focus = 2;
			frameLogo = 0;
		}
		//}

		menuOptions.SetFrame(focus);
		menuOptions.Update(1);
	}
}

void TitleState::Render() {
	if (!startMenu) {
		if (frame == 0) {
			blank.Render(0, 0);
		} else if (frame <= 4) {
			opening.Render(0, 0);
		} else {
			selector[frame - 5]->Render(0, 0);
		}
	} else if (showInstructions) {
		instructions.Render(0, 0);
	} else if (showCredits) {
		credits.Render(0, 0);
	} else {
		bg.Render(0, -100);

		logo[frameLogo]->Render(0, -70);

		menuOptions.Render(330, 340);

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

	menuSong.Stop();
	menuIntroSong.Stop();

	opening.freeMe();

	for (unsigned int i = 0; i < selector.size() - 1; i++) {
		selector[i]->freeMe();
	}
	selector.clear();

	for (unsigned int i = 0; i < 100; i++) {
		logo[i]->freeMe();
	}
	for (unsigned int i = 100; i < 200; i++) {
		logo[i]->freeMe();
	}
	for (unsigned int i = 200; i < logo.size() - 1; i++) {
		logo[i]->freeMe();
	}
	logo.clear();
}

void TitleState::Resume() {
	focus = 0;
	//initialize = true;

	for (unsigned int i = 0; i < NUMBER_FRAMES_LOGO; i++) {
		std::stringstream sstm;

		if (i >= 100) {
			sstm << "img/logo_animation/Logo_Animation_2_00" << i << ".png";
		} else if (i >= 10 && i <= 99) {
			sstm << "img/logo_animation/Logo_Animation_2_000" << i << ".png";
		} else if (i >= 0 && i <= 9) {
			sstm << "img/logo_animation/Logo_Animation_2_0000" << i << ".png";
		}

		std::string frameFile = sstm.str();

		logo.emplace_back(new Sprite(frameFile));
	}

	//mountMainMenu();
	menuSong.Open("audio/menuLoop.ogg", false);
	menuIntroSong.Open("audio/menuIntro.ogg");
	menuIntroSong.Play(1);
	updateTimer = true;
	initializeMenuIntroSong = false;
	initializeMenuSong = true;

	//frameLogo = 0;
	//timerLogo.Restart();
}

/*void TitleState::mountMainMenu() {
 textVector.clear();

 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "JOGAR", { 255,
 255, 255 }, 0, 0));
 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "INSTRUÇÕES", {
 255, 255, 255 }, 0, 0));
 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "CRÉDITOS", {
 255, 255, 255 }, 0, 0));
 textVector.emplace_back(new Text(FONT_FILE, 30, Text::SOLID, "SAIR", { 255,
 255, 255 }, 0, 0));

 for (unsigned int i = 0; i < textVector.size(); i++) {
 textVector[i]->SetPos(0, menuYStartPosition + i * ITEMS_DISTANCE, true,
 true);
 }
 }*/

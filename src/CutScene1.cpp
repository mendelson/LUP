#include "CutScene1.h"

#include <SDL_keycode.h>
#include <iostream>

#include "InputManager.h"

const unsigned int NUMBER_FRAMES_ANIMATION = 4;
const float FRAME_TIME_ANIMATION = 5;

CutScene1::CutScene1() :
		blank("img/blank.png"), sprite(
				"img/cut-scene-final/Cutscene_Final_0.png"), timer(), song("audio/finalSong.ogg"){

	popRequested = false;
	quitRequested = false;
	frame = 0;

	/*for (unsigned int i = 0; i < NUMBER_FRAMES_ANIMATION; i++) {
	 std::stringstream sstm;
	 sstm << "img/cut-scene-final/Cutscene_Final_" << i << ".png";
	 std::string frameFile = sstm.str();

	 selector.emplace_back(new Sprite(frameFile));
	 }*/

	showBlank = true;

	song.Play(1);
}

CutScene1::~CutScene1() {
	song.Stop();
	/*for (unsigned int i = 300; i < selector.size() - 1; i++) {
		selector[i]->freeMe();
	}
	selector.clear();*/
	sprite.Open("img/cut-scene-final/Cutscene_Final_0.png");
	sprite.freeMe();
	sprite.Open("img/cut-scene-final/Cutscene_Final_1.png");
	sprite.freeMe();
	sprite.Open("img/cut-scene-final/Cutscene_Final_2.png");
	sprite.freeMe();
	sprite.Open("img/cut-scene-final/Cutscene_Final_3.png");
	sprite.freeMe();
	blank.freeMe();

	cout << "Bye, LUP!" << endl;
}

void CutScene1::Update(float dt) {
	timer.Update(dt);

	if (!popRequested) {
		if (timer.Get() > 1 && showBlank) {
			showBlank = false;
		} else if (timer.Get() > FRAME_TIME_ANIMATION) {
			frame++;

			switch (frame) {
			case 1:
				sprite.Open("img/cut-scene-final/Cutscene_Final_1.png");
				timer.Restart();
				break;
			case 2:
				sprite.Open("img/cut-scene-final/Cutscene_Final_2.png");
				timer.Restart();
				break;
			case 3:
				sprite.Open("img/cut-scene-final/Cutscene_Final_3.png");
				timer.Restart();
				break;
			default:
				timer.Restart();
				break;
			}
		}

		popRequested = InputManager::GetInstance().KeyPress(SDLK_SPACE)
				|| frame >= NUMBER_FRAMES_ANIMATION;
		quitRequested = popRequested;
	}
}

void CutScene1::Render() {
	if (!popRequested) {
		if (showBlank) {
			blank.Render(0, 0);
		} else {
			//selector[frame - 1]->Render(0, 0);
			sprite.Render(0, 0);
		}
	}
}

void CutScene1::Pause() {
	song.Stop();
	/*for (unsigned int i = 300; i < selector.size() - 1; i++) {
		selector[i]->freeMe();
	}
	selector.clear();*/
	blank.freeMe();
}

void CutScene1::Resume() {
	/*for (unsigned int i = 0; i < NUMBER_FRAMES_ANIMATION; i++) {
		std::stringstream sstm;
		sstm << "img/cut-scene-final/Cutscene_Final_" << i << ".png";
		std::string frameFile = sstm.str();

		selector.emplace_back(new Sprite(frameFile));
	}*/

	song.Play(1);
}

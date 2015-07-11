#ifndef SRC_TITLESTATE_H_
#define SRC_TITLESTATE_H_

#include <vector>

#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"

class TitleState: public State {
public:
	TitleState();
	virtual ~TitleState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	//void mountMainMenu();

	Sprite bg;
	Sprite opening;
	Sprite instructions;
	Sprite menuOptions;
	Sprite credits;
	std::vector<Sprite*> selector;
	Timer timer;
	Timer timerSupport;
	//std::vector<Text*> textVector;
	int focus;
	//bool initialize;
	//int menuYStartPosition;
	Music music;
	bool startMenu;
	unsigned int frame;
	bool showInstructions;
	bool showCredits;
};

#endif /* SRC_TITLESTATE_H_ */

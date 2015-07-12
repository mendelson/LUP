#ifndef SRC_TITLESTATE_H_
#define SRC_TITLESTATE_H_

#include <vector>

#include "Music.h"
#include "Sprite.h"
#include "State.h"
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
	Sprite blank;
	std::vector<Sprite*> selector;
	std::vector<Sprite*> logo;
	Timer timer;
	Timer timerSupport;
	//std::vector<Text*> textVector;
	int focus;
	bool initializeMenuSong;
	//int menuYStartPosition;
	Music menuSong;
	Music itemSelection;
	bool startMenu;
	unsigned int frame;
	bool showInstructions;
	bool showCredits;
};

#endif /* SRC_TITLESTATE_H_ */

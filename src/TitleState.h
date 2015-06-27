#ifndef SRC_TITLESTATE_H_
#define SRC_TITLESTATE_H_

#include <vector>

#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"
#include "Music.h"

class TitleState: public State {
public:
	TitleState();
	virtual ~TitleState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	void mountMainMenu();

	Sprite bg;
	std::vector<Sprite*> selector;
	Timer timer;
	std::vector<Text*> textVector;
	int focus;
	bool initialize;
	int menuYStartPosition;
	Music music;

};

#endif /* SRC_TITLESTATE_H_ */

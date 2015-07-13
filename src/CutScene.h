#ifndef SRC_CUTSCENE_H_
#define SRC_CUTSCENE_H_

#include <vector>

#include "Music.h"
#include "Sprite.h"
#include "State.h"
#include "Timer.h"

class CutScene: public State {
public:
	CutScene();
	virtual ~CutScene();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	Sprite blank;
	std::vector<Sprite*> selector;
	Timer timer;
	Music song;
	unsigned int frame;
	bool showBlank;
};

#endif /* SRC_CUTSCENE_H_ */

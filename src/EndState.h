/*
 * EndState.h
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */

#ifndef SRC_ENDSTATE_H_
#define SRC_ENDSTATE_H_
#include "State.h"
#include "StateData.h"
#include "StageState.h"
#include "Music.h"
#include "Text.h"
#include "Sprite.h"

class EndState: public State {
public:
	EndState(StateData stateData);
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	Sprite bg;
	Music music;
	Text instruction;
};

#endif /* SRC_ENDSTATE_H_ */

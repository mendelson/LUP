/*
 * TitleState.h
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */

#ifndef TRAB_TITLESTATE_H_
#define TRAB_TITLESTATE_H_
#include "State.h"
#include "Text.h"
#include "Timer.h"

class TitleState: public State{
public:
	TitleState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	Sprite bg;
	Text text;
	Timer timer;

};



#endif /* TRAB_TITLESTATE_H_ */

/*
 * Timer.h
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */

#ifndef TRAB_TIMER_H_
#define TRAB_TIMER_H_


class Timer{
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();
private:
	float time;
};


#endif /* TRAB_TIMER_H_ */

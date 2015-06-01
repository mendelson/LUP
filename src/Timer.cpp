/*
 * Timer.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Vitor
 */



#include "Timer.h"

Timer::Timer(){
	time = 0;
}

void Timer::Update(float dt){
	time += dt;
}

void Timer::Restart(){
	time = 0;
}

float Timer::Get(){
	return time;
}

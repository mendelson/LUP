/*
 * Sound.h
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */

#ifndef TRAB_SOUND_H_
#define TRAB_SOUND_H_
#include <iostream>
#include "SDL_Mixer.h"

class Sound{
public:
	Sound();
	Sound(std::string file);
	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();
private:
	Mix_Chunk* chunk;
	int channel;
};


#endif /* TRAB_SOUND_H_ */

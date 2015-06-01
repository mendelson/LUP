/*
 * Music.h
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */

#ifndef SRC_MUSIC_H_
#define SRC_MUSIC_H_

#include <iostream>
#include "SDL_Mixer.h"

class Music{
public:
	Music();
	Music(std::string file);
	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();
private:
	Mix_Music* music;
};



#endif /* SRC_MUSIC_H_ */

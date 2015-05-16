/*
 * Sound.cpp
 *
 *  Created on: 11/05/2015
 *      Author: Vitor
 */

#include "Sound.h"
#include "Resources.h"

Sound::Sound(){
	chunk = NULL;
}

Sound::Sound(std::string file){
	Open(file);
}

void Sound::Play(int times){
	channel = Mix_PlayChannel(-1,chunk,times);
}

void Sound::Stop(){
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
	chunk = Resources::GetChunk(file);
	if(chunk == NULL){
		std::cout << "ERRO ao inicializar som!! :(" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}
}


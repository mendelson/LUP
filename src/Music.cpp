#include "Music.h"

#include <SDL_error.h>
#include <cstdlib>
#include <iostream>

#include "Resources.h"

Music::Music() {
	music = NULL;
}

Music::Music(std::string file, bool chunk) {
	this->chunk = chunk;
	Open(file, chunk);
}

void Music::Play(int times) {
	if (chunk) {
		Mix_PlayChannel(-1, music, 0);
	} else {
		Mix_PlayMusic(musicMusic, times);
	}
}

void Music::Stop() {
	Mix_FadeOutMusic(0);
}

void Music::Open(std::string file, bool chunk) {
	this->chunk = chunk;
	if (chunk) {
		music = Resources::GetChunk(file);

		if (music == NULL) {
			std::cout << "ERRO ao inicializar musica!! :(" << std::endl;
			std::cout << SDL_GetError() << std::endl;
			exit(1);
		}
	} else {
		musicMusic = Resources::GetMusic(file);

		if (musicMusic == NULL) {
			std::cout << "ERRO ao inicializar musica!! :(" << std::endl;
			std::cout << SDL_GetError() << std::endl;
			exit(1);
		}
	}

}

bool Music::IsOpen() {
	return this->chunk ? (music != NULL) : (musicMusic != NULL);
}

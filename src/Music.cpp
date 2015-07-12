#include "Music.h"
#include "Resources.h"

Music::Music() {
	music = NULL;
}

Music::Music(std::string file) {
	Open(file);
}

void Music::Play(int times) {
	//Mix_Chunk *sound = Mix_LoadWAV("some-sound-effect.wav");
	//Mix_PlayChannel(-1, music, 0);
	Mix_PlayMusic(music,times);
}

void Music::Stop() {
	Mix_FadeOutMusic(0);
}

void Music::Open(std::string file) {
	music = Resources::GetMusic(file);
	if (music == NULL) {
		std::cout << "ERRO ao inicializar musica!! :(" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}
}

bool Music::IsOpen() {
	return (music != NULL);
}

#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::chunkTable;
std::unordered_map<std::string, TTF_Font*> Resources::fontTable;

SDL_Texture* Resources::GetImage(string file) {
	if (imageTable.find(file) == imageTable.end()) {
		SDL_Texture* texture = IMG_LoadTexture(
				(Game::GetInstance().GetRenderer()), file.c_str());
		imageTable.emplace(file, texture);
	}
	return imageTable.find(file)->second;
}

Mix_Music* Resources::GetMusic(string file) {
	if (musicTable.find(file) == musicTable.end()) {
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		musicTable.emplace(file, music);
	}
	return musicTable.find(file)->second;
}

Mix_Chunk* Resources::GetChunk(string file) {
	if (chunkTable.find(file) == chunkTable.end()) {
		Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
		chunkTable.emplace(file, chunk);
	}
	return chunkTable.find(file)->second;
}

TTF_Font* Resources::GetFont(string file, int fontsize) {
	std::stringstream sstm;
	sstm << file << fontsize;
	string chave = sstm.str();
	if (fontTable.find(chave) == fontTable.end()) {
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontsize);

		if (font == NULL) {
			cout
					<< "Could not open the required font file properly! Font file required: "
					<< file << endl;
		} else {
			fontTable.emplace(chave, font);
		}
	}
	return fontTable.find(chave)->second;
}

void Resources::ClearImages() {
	for (auto it = imageTable.begin(); it != imageTable.end(); ++it) {
		SDL_DestroyTexture(it->second);
	}
	imageTable.clear();
}

void Resources::ClearMusic() {
	for (auto it = musicTable.begin(); it != musicTable.end(); ++it) {
		Mix_FreeMusic(it->second);
	}
	musicTable.clear();
}

void Resources::ClearChunk() {
	for (auto it = chunkTable.begin(); it != chunkTable.end(); ++it) {
		Mix_FreeChunk(it->second);
	}
	chunkTable.clear();
}

void Resources::ClearFont() {
	for (auto it = fontTable.begin(); it != fontTable.end(); ++it) {
		TTF_CloseFont(it->second);
	}
	fontTable.clear();
}

void Resources::removeImage(string file) {
	if (imageTable.find(file) != imageTable.end()) {
		SDL_DestroyTexture(imageTable.find(file)->second);
	}
}

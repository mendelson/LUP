/*
 * Resources.h
 *
 *  Created on: 05/04/2015
 *      Author: Vitor
 */

#ifndef TRAB_RESOURCES_H_
#define TRAB_RESOURCES_H_
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_Mixer.h"
#include "SDL_ttf.h"
#include<iostream>
#include <unordered_map>
#include <sstream>
using std::string;
class Resources{
public:
	static SDL_Texture* GetImage(string file);
	static void ClearImages();
	static Mix_Music* GetMusic(string file);
	static void ClearMusic();
	static Mix_Chunk* GetChunk(string file);
	static void ClearChunk();
	static TTF_Font* GetFont(string file,int fontsize);
	static void ClearFont();

private:
	static std::unordered_map<std::string,SDL_Texture*> imageTable;
	static std::unordered_map<std::string,Mix_Music*> musicTable;
	static std::unordered_map<std::string,Mix_Chunk*> chunkTable;
	static std::unordered_map<std::string,TTF_Font*> fontTable;
};



#endif /* TRAB_RESOURCES_H_ */

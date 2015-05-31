/*
 * Sprite.h
 *
 *  Created on: 21/03/2015
 *      Author: Vitor
 */

#ifndef TRAB_SPRITE_H_
#define TRAB_SPRITE_H_
#include "SDL.h"
#include <iostream>
#include <stdlib.h>
using std::string;

class Sprite{
public:
	Sprite();
	Sprite(string file,int frameCount = 1,float frameTime = 1, float rows = 1, float columns = 1);
	~Sprite();
	void Open(string file);
	void SetClip(int x, int y,int w,int h);
	void Render(int x,int y,float angle = 0);
	int GetWidth();
	int GetFrameWidth();
	int GetHeight();
	bool IsOpen();
	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void SetFlipH(bool flipH);
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	float scaleX;
	float scaleY;
	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
	int rows;
	int columns;
	bool flipH;
};



#endif /* TRAB_SPRITE_H_ */

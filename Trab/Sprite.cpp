/*
 * Sprite.cpp
 *
 *  Created on: 21/03/2015
 *      Author: Vitor
 */

#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(){
	texture = NULL;
	scaleX = 1;
	scaleY = 1;
	width = 0;
	height = 0;
	frameCount = 1;
	frameTime = 1;
	currentFrame = 0;
	timeElapsed = 0;
}

Sprite::Sprite(string file,int frameCount,float frameTime){
	texture = NULL;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	currentFrame = 0;
	timeElapsed = 0;
	Open(file);
	scaleX = 1;
	scaleY = 1;

}

Sprite::~Sprite(){
//	if(texture != NULL){
//		SDL_DestroyTexture(texture);
//	}
}

void Sprite::Open(string file){

	texture = Resources::GetImage(file);
	if(texture == NULL){
		cout << "ERRO ao inicializar texture!! :(" << endl;
		cout << SDL_GetError() << endl;
		exit(1);
	}

	SDL_QueryTexture(texture,NULL,NULL,&width,&height);

	width = width/frameCount;

	SetClip(0,0,width,height);
}

void Sprite::SetClip(int x, int y,int w,int h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;

}


void Sprite::Render(int x,int y,float angle){
	SDL_Rect auxrect;
	auxrect.x = x;
	auxrect.y = y;
	auxrect.w = clipRect.w*scaleX;
	auxrect.h = clipRect.h*scaleY;
	if (flipH)
		SDL_RenderCopyEx((Game::GetInstance().GetRenderer()),texture,&clipRect,&auxrect,angle,NULL,SDL_FLIP_HORIZONTAL );
	else
		SDL_RenderCopyEx((Game::GetInstance().GetRenderer()),texture,&clipRect,&auxrect,angle,NULL,SDL_FLIP_NONE );
}

int Sprite::GetHeight(){
	return height*scaleY;
}

int Sprite::GetWidth(){
	return width*scaleX*frameCount;
}

bool Sprite::IsOpen(){
	if(texture == NULL){
		return false;
	}
	return true;
}

void Sprite::SetScaleX(float scale){
	scaleX = scale;

}

void Sprite::SetScaleY(float scale){
	scaleY = scale;

}

void Sprite::Update(float dt){
	timeElapsed+=dt;

	if(timeElapsed >= frameTime){
		currentFrame++;
		timeElapsed = 0;
		if(currentFrame >= frameCount){
			currentFrame = 0;
			timeElapsed = 0;
		}
		SetClip(currentFrame*width,0,width,height);
	}
}

void Sprite::SetFrame(int frame){
	currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime){
	this->frameTime = frameTime;
}

int Sprite::GetFrameWidth(){
	return width*scaleX;
}

void Sprite::SetFlipH(bool flipH)
{
	this->flipH = flipH;
}

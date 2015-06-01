/*
 * InputManager.cpp
 *
 *  Created on: 08/04/2015
 *      Author: Vitor
 */

#include "InputManager.h"

InputManager& InputManager::GetInstance(){
	static InputManager inputManager;
	return inputManager;
}

InputManager::~InputManager(){

}

InputManager::InputManager(){
	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
	for(int i =0 ;i < 6;i++){
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}
	for(int i =0 ;i < 46;i++){
			keyState[i] = false;
			keyUpdate[i] = 0;
		}
}

void InputManager::Update(){
	SDL_Event event;
	 SDL_GetMouseState(&mouseX, &mouseY);
	 quitRequested = false;
	 if(SDL_QuitRequested()){
		 quitRequested = true;
	 }
	 updateCounter++;
	while (SDL_PollEvent(&event)){
		if(!event.key.repeat == 1){
			if(event.type == SDL_QUIT) {
				quitRequested = true;
			}
			if(event.type == SDL_MOUSEBUTTONDOWN){
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if(event.type == SDL_MOUSEBUTTONUP){
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if(event.type == SDL_KEYDOWN){
				int chave = event.key.keysym.sym;
				if(chave >= 0x40000000){
					chave -= 0x3FFFFF81;
				}
				keyState[chave] = true;
				keyUpdate[chave] = updateCounter;
			}
			if(event.type == SDL_KEYUP){
				int chave = event.key.keysym.sym;
				if(chave >= 0x40000000){
					chave -= 0x3FFFFF81;
				}
				keyState[chave] = false;
				keyUpdate[chave] = updateCounter;
			}
		}
	}
}

bool InputManager::KeyPress(int key){
	if(key >= 0x40000000){
		key -= 0x3FFFFF81;
	}
	if(updateCounter == keyUpdate[key] && keyState[key]){
		return true;
	}
	return false;
}

bool InputManager::KeyRelease(int key){
	if(key >= 0x40000000){
		key -= 0x3FFFFF81;
	}
	if(updateCounter == keyUpdate[key] && !keyState[key]){
		return true;
	}
	return false;
}

bool InputManager::IsKeyDown(int key){
	if(key >= 0x40000000){
		key -= 0x3FFFFF81;
	}
	return keyState[key];
}



bool InputManager::MousePress(int button){
	if(updateCounter == mouseUpdate[button] && mouseState[button]){
		return true;
	}
	return false;
}

bool InputManager::MouseRelease(int button){
	if(updateCounter == mouseUpdate[button] && !mouseState[button]){
		return true;
	}
	return false;
}

bool InputManager::IsMouseDown(int button){
	return mouseState[button];
}

int InputManager::GetMouseX(){
	return mouseX;
}

int InputManager::GetMouseY(){
	return mouseY;
}

bool InputManager::QuitRequested(){
	return quitRequested;
}

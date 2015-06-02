#ifndef SRC_INPUTMANAGER_H_
#define SRC_INPUTMANAGER_H_

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY SDLK_SPACE
#define RETURN_KEY SDLK_RETURN

#include <iostream>
#include <unordered_map>
#include "SDL.h"

using std::cout;
using std::string;
using std::endl;

class InputManager {
public:
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	bool QuitRequested();
	static InputManager& GetInstance();
private:
	InputManager();
	~InputManager();
	bool mouseState[6];
	int mouseUpdate[6];
	bool keyState[46];
	int keyUpdate[46];
	bool quitRequested;
	int updateCounter;
	int mouseX;
	int mouseY;
};

#endif /* SRC_INPUTMANAGER_H_ */

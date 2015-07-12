#include "Game.h"

#include "InputManager.h"
#include "Resources.h"

Game* Game::instance = NULL;

Game::Game(string title, int width, int height){
	if(instance != NULL){
		cout << "ERRO! Classe ja instanciada! Abortando programa! :(" << endl;
		exit(1);
	}else{
		instance = this;
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
			cout << "ERRO ao inicializar SDL! Abortando programa! :(" << endl;
			cout << SDL_GetError();
			exit(1);
		}
		if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) ){
			cout<< "ERRO ao inicializar Imagens! Abortando! :(" << endl;
			exit(1);
		}
		//if(Mix_Init(MIX_INIT_FLAC|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MOD|MIX_INIT_FLUIDSYNTH|MIX_INIT_MODPLUG) != (MIX_INIT_FLAC|MIX_INIT_MP3|MIX_INIT_OGG|MIX_INIT_MOD|MIX_INIT_FLUIDSYNTH|MIX_INIT_MODPLUG)){
		//	cout<< "ERRO ao inicializar musica! Abortando! :(" << endl;
		//	exit(1);
		//}
		if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) != 0){
			cout<< "ERRO ao inicializar decoder! Abortando! :(" << endl;
			exit(1);
		}
		if(TTF_Init() != 0 ){
			cout<< "ERRO ao inicializar textos! Abortando! :(" << endl;
			exit(1);
		}
		this->width = width;
		this->height = height;
		window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
		if(window == NULL){
			cout << "ERRO ao inicializar janela! Abortando! :(" << endl;
			exit(1);
		}
		renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
		if(renderer == NULL){
			cout<<"ERRO ao inicializar renderer! Abortando! :(" << endl;
			exit(1);
		}
		dt = 0;
		frameStart = 0;
		storedState = NULL;
		State* initState = new TitleState();
		Push(initState);
	}
}

Game::~Game(){
	if(storedState!=NULL){
		delete(storedState);
	}
	while(!stateStack.empty()){
		stateStack.pop();
	}
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

Game& Game::GetInstance(){
	return *instance;
}

State& Game::GetCurrentState(){
	return *stateStack.top();
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

void Game::Run(){
	if(storedState != NULL){
				stateStack.emplace(storedState);
				storedState = NULL;
		while(!stateStack.empty() && !GetCurrentState().QuitRequested()){
			if(GetCurrentState().PopRequested()){
				GetCurrentState().Pause();
				stateStack.pop();
				if(stateStack.empty()){
					break;
				}
				stateStack.top()->Resume();
			}
			if(storedState != NULL){
				stateStack.top()->Pause();
				stateStack.emplace(storedState);
				stateStack.top()->Resume();
				storedState = NULL;
			}

			CalculateDeltaTime();
			InputManager::GetInstance().Update();
			GetCurrentState().Update(Game::GetInstance().GetDeltaTime());
			GetCurrentState().Render();
			SDL_RenderPresent(renderer);
			SDL_Delay(20);
		}
		Resources::ClearImages();
		Resources::ClearMusic();
		Resources::ClearChunk();
		Resources::ClearFont();
	}
}

int Game::getWidth(){
	return width;
}

int Game::getHeight(){
	return height;
}

void Game::CalculateDeltaTime(){
	int old = frameStart;
	frameStart = SDL_GetTicks();
	dt = ((frameStart - old)/1000.0);
}

float Game::GetDeltaTime(){
	return dt;
}

void Game::Push(State* state){
	storedState = state;
}

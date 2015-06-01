#include "StageState.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"
#include "Collision.h"

StageState::StageState() :
		tileSet(64, 64, "img/tileset.png"), tileMap("map/tileMap.txt",
				&tileSet), bg("img/ocean.jpg"), music("audio/stageState.ogg"), ui(3) {
	quitRequested = false;
	srand((unsigned int) time(NULL));
	GameObject* penguin = new Penguins(1920, 100);
	objectArray.emplace_back(penguin);
	Camera::Follow(penguin);
}

void StageState::Update(float dt) {
	Camera::Update(dt);
	quitRequested = InputManager::GetInstance().QuitRequested();
	popRequested = InputManager::GetInstance().KeyPress(ESCAPE_KEY);
	UpdateArray(dt);
	ui.Update(dt);
}

void StageState::Render() {
	bg.Render(0, 0);
	tileMap.RenderLayer(0, Camera::pos.getX(), Camera::pos.getY());
	RenderArray();
	tileMap.Render(Camera::pos.getX(), Camera::pos.getY());
	ui.Render();
}

StageState::~StageState() {
	objectArray.clear();
}

void StageState::Pause() {
	music.Stop();

}

void StageState::Resume() {
	music.Play(-1);
}

float StageState::getTileMapHeight(int x) {
	return tileMap.GetFloorHeight(x);
}

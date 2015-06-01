#ifndef SRC_STAGESTATE_H_
#define SRC_STAGESTATE_H_

#include "SDL.h"
#include "Sprite.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Alien.h"
#include "Minion.h"
#include "Penguins.h"
#include "State.h"
#include "Music.h"
#include "UI.h"

using std::string;

class StageState: public State {
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	float getTileMapHeight(int x);
private:
	TileSet tileSet;
	TileMap tileMap;
	Sprite bg;
	Music music;
	UI ui;
};

#endif /* SRC_STAGESTATE_H_ */

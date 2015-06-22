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
#include "Minion.h"
#include "Player.h"
#include "Weapon.h"
#include "EnemyTank.h"
#include "Support.h"
#include "State.h"
#include "Music.h"
#include "UI.h"
#include "Plataforma.h"
#include "Planet.h"
#include "Planta.h"

using std::string;

class StageState: public State {
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
private:
	TileSet tileSet;
	TileMap tileMap;
	Sprite bg;
	Music music;
	UI ui;
	float xBg;
};

#endif /* SRC_STAGESTATE_H_ */

/*
 * State.h
 *
 *  Created on: 21/03/2015
 *      Author: Vitor
 */

#ifndef TRAB_STAGESTATE_H_
#define TRAB_STAGESTATE_H_
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
#include "Player.h"
#include "Weapon.h"
#include "EnemyTank.h"
#include "Support.h"
#include "State.h"
#include "Music.h"
using std::string;

class StageState : public State{
public:
	StageState();
	~StageState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	float getTileMapHeight(int x,int y);
	float getTileMapAngle(int x);
private:
	TileSet tileSet;
	TileMap tileMap;
	Sprite bg;
	Music music;
};


#endif /* TRAB_STAGESTATE_H_ */

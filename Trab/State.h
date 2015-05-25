/*
 * State.h
 *
 *  Created on: 06/05/2015
 *      Author: Vitor
 */

#ifndef TRAB_STATE_H_
#define TRAB_STATE_H_
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include "GameObject.h"


class State{
public:
	State();
	virtual ~State();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void AddObject(GameObject* object);
	bool PopRequested();
	void SetPopRequested(bool pop);
	bool QuitRequested();
	virtual float getTileMapHeight(int x){ return 0;};
protected:
	virtual void UpdateArray(float dt);
	virtual void RenderArray();
	bool popRequested;
	bool quitRequested;
	std::vector<std::unique_ptr<GameObject>> objectArray;
};


#endif /* TRAB_STATE_H_ */

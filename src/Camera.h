/*
 * Camera.h
 *
 *  Created on: 08/04/2015
 *      Author: Vitor
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_
#include <iostream>
#include "GameObject.h"
#include "Point.h"

class Camera{
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
	static Point pos;
	static Point speed;
	static float rotation;
private:
	static GameObject* focus;
};



#endif /* SRC_CAMERA_H_ */

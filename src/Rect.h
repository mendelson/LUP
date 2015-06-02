/*
 * Rect.h
 *
 *  Created on: 25/03/2015
 *      Author: Vitor
 */

#ifndef SRC_RECT_H_
#define SRC_RECT_H_
#include "Point.h"

class Rect{
public:
	float x;
	float y;
	float w;
	float h;

	Rect();
	Rect(float aux_x,float aux_y,float aux_w, float aux_h);
	void setX(float aux_x);
	void setY(float aux_y);
	void setW(float aux_w);
	void setH(float aux_h);
	float getX();
	float getY();
	float getW();
	float getH();
	float getCenterX();
	float getCenterY();
	void somaPonto(Point ponto);
	Point pegaCentro() const;
	float pegaDistFromCenter(Rect rect);
	bool isPontoInside(Point ponto);
};




#endif /* SRC_RECT_H_ */

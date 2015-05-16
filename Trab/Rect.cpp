/*
 * Rect.cpp
 *
 *  Created on: 25/03/2015
 *      Author: Vitor
 */

#include "Rect.h"

Rect::Rect(){
	x = 0;
	y = 0;
	h = 0;
	w = 0;
}


Rect::Rect(float aux_x, float aux_y, float aux_w, float aux_h){
	x = aux_x;
	y = aux_y;
	h = aux_h;
	w = aux_w;
}

void Rect::setX(float aux_x){
	x = aux_x;
}

void Rect::setY(float aux_y){
	y = aux_y;
}

void Rect::setH(float aux_h){
	h = aux_h;
}

void Rect::setW(float aux_w){
	w = aux_w;
}

float Rect::getX(){
	return x;
}

float Rect::getY(){
	return y;
}

float Rect::getW(){
	return w;
}

float Rect::getH(){
	return h;
}

float Rect::getCenterX(){
	return x+(w/2);
}

float Rect::getCenterY(){
	return y+(h/2);
}
void Rect::somaPonto(Point ponto){
	x += ponto.getX();
	y += ponto.getY();
}

Point Rect::pegaCentro() const{
	Point* ponto = new Point();
	ponto->setX(x + (w/2));
	ponto->setY(y + (h/2));
	return *ponto;
}

float Rect::pegaDistFromCenter(Rect rect){
	Point aux1 = pegaCentro();
	Point aux2 = rect.pegaCentro();
	float dist = aux1.getDist(aux2);
	delete(&aux1);
	delete(&aux2);
	return dist;
}

bool Rect::isPontoInside(Point ponto){
	if(ponto.getX() > x && ponto.getX() < (x+w) && ponto.getY() > y && ponto.getY() < (y+h)){
		return true;
	}
	return false;
}

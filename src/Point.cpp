/*
 * Point.cpp
 *
 *  Created on: 25/03/2015
 *      Author: Vitor
 */


#include "Point.h"
#include "Game.h"

Point::Point(){
	x= 0;
	y = 0;
}

Point::Point(float aux_x, float aux_y){
	x = aux_x;
	y = aux_y;
}

void Point::setX(float aux_x){
	x = aux_x;
}

void Point::setY(float aux_y){
	y = aux_y;
}

float Point::getX(){
	return x;
}

float Point::getY(){
	return y;
}

float Point::getDist(Point ponto){
	float distX = ponto.getX() - x;
	float distY = ponto.getY() - y;
	distX = pow(distX,2);
	distY = pow(distY,2);
	float dist = sqrt(distX + distY);
	return dist;
}

void Point::somaPonto(Point ponto){
	x += ponto.getX();
	y += ponto.getY();
}

float Point::getInclinationFromTop(){
	return (float) atan(y/x);
}

float Point::getInclinationFromBottom(){
	float aux_y = Game::GetInstance().getHeight() - y;
	return (float) atan(aux_y/x);
}

void Point::vetMultEscalar(float esc){
	x = x*esc;
	y = y*esc;
}

void Point::rotateVector(float angle){
	float novoX = (x*cos(angle)) - (y*sin(angle));
	float novoY = (x*sin(angle)) + (y*cos(angle));
	x = novoX;
	y = novoY;
}

void Point::rotateVectorFromBottom(float angle){
	float aux_y = Game::GetInstance().getHeight() - y;
	float novoX = (x*cos(angle)) - (aux_y*sin(angle));
	float novoY = (x*sin(angle)) + (aux_y*cos(angle));
	x = novoX;
	aux_y = novoY;
	y = Game::GetInstance().getHeight() - aux_y;
}

void Point::negateVector(){
	x = -x;
	y = -y;
}

float Point::magVector(){
	return sqrt(pow(x,2) + pow(y,2));
}

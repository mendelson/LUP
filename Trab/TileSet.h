/*
 * TileSet.h
 *
 *  Created on: 01/04/2015
 *      Author: Vitor
 */

#ifndef TRAB_TILESET_H_
#define TRAB_TILESET_H_

#include<iostream>
#include <math.h>
#include "Sprite.h"
using std::string;
using std::cout;
using std::endl;
class TileSet{
public:
	TileSet(int aux_tileWidth,int aux_tileHeight,string file);
	void Render(unsigned int index,float x, float y);
	int GetTileWidth();
	int GetTileHeight();
private:
	Sprite tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;
};



#endif /* TRAB_TILESET_H_ */

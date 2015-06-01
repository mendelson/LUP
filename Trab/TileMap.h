/*
 * TileMap.h
 *
 *  Created on: 07/04/2015
 *      Author: Vitor
 */

#ifndef TRAB_TILEMAP_H_
#define TRAB_TILEMAP_H_
#include<iostream>
#include<stdio.h>
#include<vector>
#include "TileSet.h"
using std::string;
using std::cout;
using std::endl;

class TileMap{
public:
	TileMap(string file, TileSet* tileSet);
	void Load(string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z);
	void Render(int cameraX,int cameraY);
	void RenderLayer(int layer, int cameraX, int cameraY);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	float GetFloorHeight(int x,int cameraX);
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};



#endif /* TRAB_TILEMAP_H_ */

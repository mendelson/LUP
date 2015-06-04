#ifndef SRC_TILEMAP_H_
#define SRC_TILEMAP_H_

#include<iostream>
#include<stdio.h>
#include<vector>
#include "TileSet.h"

using std::string;
using std::cout;
using std::endl;

class TileMap {
public:
	TileMap(string file, TileSet* tileSet);
	void Load(string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z);
	void Render(int cameraX, int cameraY);
	void RenderLayer(int layer, int cameraX, int cameraY);
	int GetWidth();
	int GetHeight();
	int GetDepth();
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};

#endif /* SRC_TILEMAP_H_ */

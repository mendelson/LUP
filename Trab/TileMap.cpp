/*
 * TileMap.cpp
 *
 *  Created on: 01/04/2015
 *      Author: Vitor
 */

#include "TileMap.h"
#include "Camera.h"
#include "InputManager.h"

TileMap::TileMap(string file, TileSet* tileSet){
	Load(file);
	this->tileSet = tileSet;
}

void TileMap::Load(string file){
	FILE* fp;
	fp = fopen(file.c_str(),"r");
	fscanf(fp,"%d,",&mapWidth);
	fscanf(fp,"%d,",&mapHeight);
	fscanf(fp,"%d,",&mapDepth);
	int aux;
	while(!feof(fp)){
		fscanf(fp,"%d,",&aux);
		tileMatrix.emplace_back(aux-1);
	}
}

void TileMap::SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z = 0){
	if(x>mapWidth || y>mapHeight || z > mapDepth){
		cout << "Indice errado!!" << endl;
		exit(1);
	}
	int aux = (z*(mapWidth*mapHeight)) + (y*mapWidth) + x;
	return tileMatrix[aux];
}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0){
	int raioPlaneta = 1000;
	int qntTiles = 600/tileSet->GetTileWidth();
	for(int i=0;i<mapHeight;i++){
		for(int j=0;j<(mapWidth*3);j++){
			int auxj = abs(j)%mapWidth;
			int aux = At(0,0,layer);
			int tileAtualCam = -cameraX/tileSet->GetTileWidth();
			float angle = j - tileAtualCam;
			float posX = raioPlaneta*cos(qntTiles*angle);
			float posy = raioPlaneta*sin(qntTiles*angle) + i*tileSet->GetTileHeight();
			posX = 1920 + posX + cameraX*(layer+1);
			posy = posy  + cameraY*(layer+1) + 250 + raioPlaneta;
			if(aux >= 0){
				//cout << "Imprimiu tile!" << cameraX << " - "  << posX  << " - "  << cameraY  << " - "  << posy << endl;
				angle += 3.1415/2;
				tileSet->Render(0,posX  ,posy,angle*180/3.1415);
			}
			if(InputManager::GetInstance().KeyPress(SDLK_p)){
				cout << tileAtualCam << endl;
			}
		}
	}
}

void TileMap::Render(int cameraX,int cameraY){
	for(int i=1;i<mapDepth;i++){
		RenderLayer(i,cameraX,cameraY);
	}
}

int TileMap::GetWidth(){
	return mapWidth;
}

int TileMap::GetHeight(){
	return mapHeight;
}

int TileMap::GetDepth(){
	return mapDepth;
}

float TileMap::GetFloorHeight(int x){
	int tileX = x/tileSet->GetTileWidth();
	while(tileX > 25){
		tileX -= 25;
	}

	for(int j=0;j<mapHeight;j++){
		for(int i=mapDepth-1;i>=0;i--){
			int aux = At(tileX,j,i);
			if(aux > 0){
				//250 é a altura inicial dos Tiles
				return j*tileSet->GetTileHeight() + 250;
			}
		}
	}
	return 0;
}

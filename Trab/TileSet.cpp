/*
 * TileSet.cpp
 *
 *  Created on: 01/04/2015
 *      Author: Vitor
 */

#include "TileSet.h"

TileSet::TileSet(int aux_tileWidth, int aux_tileHeight, string file) : tileSet(file){
	tileWidth = aux_tileWidth;
	tileHeight = aux_tileHeight;
	if(!tileSet.IsOpen()){
		cout<<"Erro ao abrir sprite do tile set!!" << endl;
		exit(1);
	}
	rows = tileSet.GetHeight()/tileHeight;
	cout<< "rows : " << rows << endl;
	columns = tileSet.GetWidth()/tileWidth;
	cout<< "columns : " << columns << endl;
}


void TileSet::Render(unsigned int index,float x,float y,float angle){
	if(index > ((rows*columns) - 1)){
		cout << "Index de tileSet inv�lido!!  - " << index << endl;
		exit(1);
	}
	int sp_x = index%columns;
	int sp_y = floor(index/columns);
	tileSet.SetClip(sp_x*tileWidth,sp_y*tileHeight,tileWidth,tileHeight);
	tileSet.Render(x,y,angle);
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;
}

#include "TileSet.h"

TileSet::TileSet(int aux_tileWidth, int aux_tileHeight, string file) :
		tileSet("img/tileset.png") {
	tileWidth = aux_tileWidth;
	tileHeight = aux_tileHeight;
	if (!tileSet.IsOpen()) {
		cout << "Erro ao abrir sprite do tile set!!" << endl;
		exit(1);
	}
	rows = tileSet.GetHeight() / tileHeight;
	columns = tileSet.GetWidth() / tileWidth;
}

void TileSet::Render(unsigned int index, float x, float y) {
	if (index > ((rows * columns) - 1)) {
		cout << "Index de tileSet inválido!!" << endl;
		exit(1);
	}
	int sp_x = index % columns;
	int sp_y = floor(index / columns);
	tileSet.SetClip(sp_x * tileWidth, sp_y * tileHeight, tileWidth, tileHeight);
	tileSet.Render(x, y);
}

int TileSet::GetTileWidth() {
	return tileWidth;
}

int TileSet::GetTileHeight() {
	return tileHeight;
}

#include "Game.h"
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::string;
using std::endl;

int main(int argc, char** argv) {
	Game* game = new Game("LUP", 1024, 600);
	game->Run();
	return 0;
}

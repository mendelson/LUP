/*
 * Main.cpp
 *
 *  Created on: 21/03/2015
 *      Author: Vitor
 */

#include "Game.h"
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::string;
using std::endl;

int main (int argc, char** argv) {
	Game* game = new Game("Vitor Quaresma-110143566",1024,600);
	game->Run();
    return 0;
}




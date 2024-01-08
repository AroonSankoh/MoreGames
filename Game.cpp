//Game.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for abstract Game class 

#include "Game.h"

using namespace std;

Game::Game(int argc, const char* argv[]) {
    for (int i = first_player_name; i < argc; ++i) {
        names.push_back(argv[i]);
    }
};
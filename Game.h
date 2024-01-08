//Game.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for abstract Game class 
#pragma once 

#include <iostream> 
#include <vector>

enum GameValues {
    first_player_name = 2, 
    game_over = 0
};

class Game {
    protected: 
        std::vector<std::string> names;

    public: 
        Game(int argc, const char* argv[]);
        virtual int play() = 0;  
};
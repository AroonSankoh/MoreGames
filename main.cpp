//main.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains main function that runs a Pinochle or HoldEm Game

#include "Suit.h"
#include "PinochleDeck.h"
#include "HoldEmDeck.h"
#include "PinochleGame.h"
#include "HoldEmGame.h"
#include "GoFishGame_T.h"
#include <memory>

using namespace std;

enum cardStats {
    numSuits = 4
};

enum command_line {
    game_type = 1, 
    go_fish_deck_type = 2,
    pinochle_arg_count = 6,
    holdem_min_arg_count = 4,
    holdem_max_arg_count = 11, 
    gofish_min_arg_count = 5, 
    gofish_max_arg_count = 8
};

enum return_values {
    pass,
    no_command_line_args,
    invalid_game_type,
    invalid_player_count,
    failed_shared_ptr_allocation    
};


/*
* create(int argc, const char* argv[]) creates a shared_ptr that is dynamically initialized as 
* a PinochleGame, HoldEmGame, GoFishGame, or null_ptr depending on the command line arguments
*
* @param argc the number of command line arguments 
* @param argv the C-Style string array storing the command line arguments
* @return the game_ptr
*/
shared_ptr<Game> create(int argc, const char* argv[]) {
    shared_ptr<Game> game_ptr;
    if (string(argv[game_type]) == "Pinochle") {
        game_ptr = make_shared<PinochleGame>(argc, argv);
    }
    else if (string(argv[game_type]) == "HoldEm") {
        game_ptr = make_shared<HoldEmGame>(argc, argv);
    }
    else if (string(argv[game_type]) == "GoFish") {
        if (string(argv[go_fish_deck_type]) == "Pinochle") {
            game_ptr = make_shared< GoFishGame<PinochleRank, Suit, PinochleDeck> >(argc, argv); 
        }
        else if (string(argv[go_fish_deck_type]) == "HoldEm") {
            game_ptr = make_shared< GoFishGame<HoldEmRank, Suit, HoldEmDeck> >(argc, argv); 
        }
        else {
            game_ptr = make_shared< GoFishGame<UnoRank, Color, UnoDeck> >(argc, argv); 
        }
    }
    else {
        throw invalid_argument("Game type is not specified in command line arguments.");
    }
    return game_ptr;
}

/*
* check_arguments(int argc, const char* argv[]) checks if the command line arguments entered 
* by the user are valid for a PinochleGame or HoldEmGame
*
* @param argc the number of command line arguments 
* @param argv the C-Style string array storing the command line arguments
* @return int depending on the validity of the command line arguments
*/
int check_arguments(int argc, const char* argv[]) { 
    if (argc > game_type) {
        if (string(argv[game_type]) == "Pinochle") {
            if (argc == pinochle_arg_count) {
                return pass;
            }
            else {
                return invalid_player_count;
            }
        }
        else if (string(argv[game_type]) == "HoldEm") {
            if (argc >= holdem_min_arg_count && argc <= holdem_max_arg_count) {
                return pass;
            }
            else {
                return invalid_player_count;
            }
        }
        else if (string(argv[game_type]) == "GoFish") {
            if (argc >= gofish_min_arg_count && argc <= gofish_max_arg_count) {
                if ( (string(argv[go_fish_deck_type]) == "Pinochle") ||
                    (string(argv[go_fish_deck_type]) == "HoldEm") ||
                    (string(argv[go_fish_deck_type]) == "Uno") ) {
                    return pass;
                }
            }
            else {
                return invalid_player_count;
            }
        }
        else {
            return invalid_game_type;
        }
    }
    return no_command_line_args;   
}

void usage_message() {
    cout << "Run the executable in the command line followed by: " << endl;
    cout << "1) \"Pinochle\" and four player names or " << endl;
    cout << "2) \"HoldEm\" and between two and nine player names" << endl;
    cout << "3) \"GoFish\" and either \"Pinochle\", \"HoldEm\", or \"Uno\" and between two and five player names" << endl;
}

int main(int argc, const char* argv[]) {
    int game_state = check_arguments(argc, argv);
    shared_ptr<Game> game_ptr;
    if (game_state == pass) {
        try {
            game_ptr = create(argc, argv);
        }
        catch (const exception& e) {
            cerr << "Exception Caught: " << e.what() << endl;
        }
        if (game_ptr) {
            return game_ptr->play();
        }
        else {
            return failed_shared_ptr_allocation;
        }
    }
    else {
        usage_message();
        return game_state;
    }
}
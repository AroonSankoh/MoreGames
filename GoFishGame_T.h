//GoFishGame_T.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for GoFishGame class template 

#pragma once 

#include "Game.h"
#include "HoldEmDeck.h"
#include "PinochleDeck.h"
#include "UnoDeck.h"
#include "CardSet_T.h"
#include <type_traits>

template<typename Rank = HoldEmRank, typename Suit = Suit, typename Deck = HoldEmDeck>
class GoFishGame: public Game {
    static_assert(std::is_base_of<CardSet<Rank, Suit>, Deck>::value, "Deck must be derived from CardSet<Rank, Suit>");
    
    protected: 
        Deck deck;
        std::vector< CardSet<Rank, Suit> > hands;
        std::vector< CardSet<Rank, Suit> > books;
        bool turn(unsigned int player);
        void print_game_stats();
        void print_end_game();
        void prompt(std::string& input, unsigned int player);
        bool check_input(std::string input, unsigned int player);
        bool retrieve(unsigned int player, int target_player, std::string rank_string);
        virtual void deal();

    public: 
        GoFishGame(int argc, const char* argv[]);
        virtual ~GoFishGame();
        virtual int play();  
        bool check_game_conditions(int remaining_players);
        bool collect_books(unsigned int player); 
};

enum GoFishGameValues {
    two = 2, 
    num_cards_for_two_players = 7, 
    default_num_cards = 5
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE 
#include "GoFishGame_T.cpp"
#endif
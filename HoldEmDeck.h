//HoldEmDeck.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for HoldEmDeck class and associated functions

#pragma once 

#include "Deck_T.h"
#include "Card_T.h"
#include <map>

enum class HoldEmRank {
    two, 
    three, 
    four, 
    five, 
    six, 
    seven, 
    eight,
    nine,
    ten, 
    jack, 
    queen, 
    king, 
    ace, 
    undefined
};

//Derived Class
class HoldEmDeck: public Deck<HoldEmRank, Suit> {
    public: 
        HoldEmDeck();
};

std::ostream& operator<<(std::ostream& stream, const HoldEmRank &rank);
HoldEmRank& operator++(HoldEmRank &rank);
void set_rank(std::string rank_string, HoldEmRank& rank);



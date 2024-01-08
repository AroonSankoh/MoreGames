//PinochleDeck.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for PinochleDeck class and associated functions

#pragma once 

#include "Deck_T.h"
#include "Card_T.h"
#include <map>

enum class PinochleRank {
    nine, 
    jack, 
    queen, 
    king,
    ten, 
    ace, 
    undefined
};

//Derived Class
class PinochleDeck: public Deck<PinochleRank, Suit> {
    public: 
        PinochleDeck();
};

std::ostream& operator<<(std::ostream& stream, const PinochleRank &rank);
PinochleRank& operator++(PinochleRank &rank);
PinochleRank& operator--(PinochleRank &rank);
void set_rank(std::string rank_string, PinochleRank& rank);



 
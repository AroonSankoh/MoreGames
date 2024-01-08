//UnoDeck.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for UnoDeck class and associated functions

#pragma once 

#include "Deck_T.h"
#include "Card_T.h"
#include <map>

enum class Color {
    red, 
    blue, 
    green, 
    yellow, 
    black, 
    undefined
};

enum class UnoRank {
    zero, 
    one, 
    two, 
    three, 
    four, 
    five, 
    six, 
    seven, 
    eight, 
    nine, 
    skip, 
    reverse, 
    drawtwo, 
    drawfour, 
    wild, 
    blank, 
    undefined       
};

//Derived Class
class UnoDeck: public Deck<UnoRank, Color> {
    public: 
        UnoDeck();
};

std::ostream& operator<<(std::ostream& stream, const UnoRank &rank);
std::ostream& operator<<(std::ostream& stream, const Color &color);
UnoRank& operator++(UnoRank &rank);
Color& operator++(Color &color);
void set_rank(std::string rank_string, UnoRank& rank);




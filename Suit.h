//Suit.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for Suit class and associated functions

#pragma once 

#include <iostream>

enum class Suit {
    clubs, 
    diamonds, 
    hearts, 
    spades, 
    undefined
};

std::ostream& operator<<(std::ostream& stream, const Suit &suit);
Suit operator++(Suit &suit);
Suit operator--(Suit &suit);




//Suit.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for Suit class and associated functions

#include "Suit.h"
#include "PinochleDeck.h"
#include "HoldEmDeck.h"

using namespace std; 

std::ostream& operator<<(std::ostream& stream, const Suit &suit) {
    switch (suit) {
        case Suit::clubs: stream << "C";
            return stream;
            break;
        case Suit::diamonds: stream << "D";
            return stream;
            break;
        case Suit::hearts: stream << "H";
            return stream;
            break;
        case Suit::spades: stream << "S";
            return stream;
            break;
        case Suit::undefined: stream << "?";
            return stream;
            break;
    }
    return stream;
}

Suit operator++(Suit &suit) {
    switch (suit) { 
        case Suit::clubs:
            suit = Suit::diamonds;
            return Suit::diamonds;
            break;
        case Suit::diamonds:
            suit = Suit::hearts;
            return Suit::hearts;
            break;
        case Suit::hearts:
            suit = Suit::spades;
            return Suit::spades;
            break;
        case Suit::spades:
            suit = Suit::undefined;
            return Suit::undefined;
            break;
        case Suit::undefined:
            return Suit::undefined;
            break;
    }
    return suit;
}

Suit operator--(Suit &suit) {
    switch (suit) {
        case Suit::clubs:
            return Suit::clubs;
            break;
        case Suit::diamonds:
            suit = Suit::clubs;
            return Suit::clubs;
            break;
        case Suit::hearts:
            suit = Suit::diamonds;
            return Suit::diamonds;
            break;
        case Suit::spades:
            suit = Suit::hearts;
            return Suit::hearts;
            break;
        case Suit::undefined:
            suit = Suit::spades;
            return Suit::spades;
            break;
    }
    return suit;
}


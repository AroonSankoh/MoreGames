//PinochleDeck.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for PinochleDeck class and associated functions

#include "PinochleDeck.h"

using namespace std; 

PinochleDeck::PinochleDeck() {
    for (Suit suitIter = Suit::clubs; suitIter < Suit::undefined; ++suitIter) {
        for (PinochleRank rankIter = PinochleRank::nine; rankIter < PinochleRank::undefined; ++rankIter) {
            card_type card(rankIter, suitIter);
            pile.push_back(card); 
            pile.push_back(card);
        }
    }
};

std::ostream& operator<<(std::ostream& stream, const PinochleRank &rank) {
    switch (rank) {
        case PinochleRank::nine: stream << "9";
            return stream;
            break;
        case PinochleRank::jack: stream << "J";
            return stream;
            break;
        case PinochleRank::queen: stream << "Q";
            return stream;
            break;
        case PinochleRank::king: stream << "K";
            return stream;
            break;
        case PinochleRank::ten: stream << "10";
            return stream;
            break;
        case PinochleRank::ace: stream << "A";
            return stream;
            break;
        case PinochleRank::undefined: stream << "?";
            return stream;
            break;
    }
    return stream;
}

PinochleRank& operator++(PinochleRank &rank) {
    switch (rank) { 
        case PinochleRank::nine:
            rank = PinochleRank::jack;
            break;
        case PinochleRank::jack:
            rank = PinochleRank::queen;
            break;
        case PinochleRank::queen:
            rank = PinochleRank::king;
            break;
        case PinochleRank::king:
            rank = PinochleRank::ten;
            break;
        case PinochleRank::ten:
            rank = PinochleRank::ace;
            break;
        case PinochleRank::ace:
            rank = PinochleRank::undefined;
            break;
        case PinochleRank::undefined:
            break;
    }
    return rank;
}

PinochleRank& operator--(PinochleRank &rank) {
    switch (rank) { 
        case PinochleRank::nine:
            break;
        case PinochleRank::jack:
            rank = PinochleRank::nine;
            break;
        case PinochleRank::queen:
            rank = PinochleRank::jack;
            break;
        case PinochleRank::king:
            rank = PinochleRank::queen;
            break;
        case PinochleRank::ten:
            rank = PinochleRank::king;
            break;
        case PinochleRank::ace:
            rank = PinochleRank::ten;
            break;
        case PinochleRank::undefined:
            rank = PinochleRank::ace;
            break;
    }
    return rank;
}

void set_rank(std::string rank_string, PinochleRank& rank) {
    map<string, PinochleRank> string_to_rank = {
        {"9", PinochleRank::nine},
        {"J", PinochleRank::jack},
        {"Q", PinochleRank::queen},
        {"K", PinochleRank::king},
        {"10", PinochleRank::ten},
        {"A", PinochleRank::ace}
    };
    if (string_to_rank.find(rank_string) != string_to_rank.end()) {
        rank = string_to_rank[rank_string];
    }
}
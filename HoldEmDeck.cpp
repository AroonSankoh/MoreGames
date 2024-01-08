//HoldEmDeck.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for HoldEmDeck class and associated functions

#include "HoldEmDeck.h"

using namespace std; 

HoldEmDeck::HoldEmDeck() {
    for (Suit suitIter = Suit::clubs; suitIter < Suit::undefined; ++suitIter) {
        for (HoldEmRank rankIter = HoldEmRank::two; rankIter < HoldEmRank::undefined; ++rankIter) {
            card_type card(rankIter, suitIter);
            pile.push_back(card);
        }
    }
};

std::ostream& operator<<(std::ostream& stream, const HoldEmRank &rank) {
    switch (rank) {
         case HoldEmRank::two: stream << "2";
            return stream;
            break;
         case HoldEmRank::three: stream << "3";
            return stream;
            break;
         case HoldEmRank::four: stream << "4";
            return stream;
            break;
         case HoldEmRank::five: stream << "5";
            return stream;
            break;
         case HoldEmRank::six: stream << "6";
            return stream;
            break;
         case HoldEmRank::seven: stream << "7";
            return stream;
            break;
         case HoldEmRank::eight: stream << "8";
            return stream;
            break;
        case HoldEmRank::nine: stream << "9";
            return stream;
            break;
        case HoldEmRank::ten: stream << "10";
            return stream;
            break;
        case HoldEmRank::jack: stream << "J";
            return stream;
            break;
        case HoldEmRank::queen: stream << "Q";
            return stream;
            break;
        case HoldEmRank::king: stream << "K";
            return stream;
            break;
        case HoldEmRank::ace: stream << "A";
            return stream;
            break;
        case HoldEmRank::undefined: stream << "?";
            return stream;
            break;
    }
    return stream;
}

HoldEmRank& operator++(HoldEmRank &rank) {
    switch (rank) {
        case HoldEmRank::two:
            rank = HoldEmRank::three;
            break;
        case HoldEmRank::three:
            rank = HoldEmRank::four;
            break;
        case HoldEmRank::four:
            rank = HoldEmRank::five;
            break;
        case HoldEmRank::five:
            rank = HoldEmRank::six;
            break;
        case HoldEmRank::six:
            rank = HoldEmRank::seven;
            break;
        case HoldEmRank::seven:
            rank = HoldEmRank::eight;
            break;
        case HoldEmRank::eight:
            rank = HoldEmRank::nine;
            break;
        case HoldEmRank::nine:
            rank = HoldEmRank::ten;
            break; 
        case HoldEmRank::ten:
            rank = HoldEmRank::jack;
            break;
        case HoldEmRank::jack:
            rank = HoldEmRank::queen;
            break;
        case HoldEmRank::queen:
            rank = HoldEmRank::king;
            break;
        case HoldEmRank::king:
            rank = HoldEmRank::ace;
            break;
        case HoldEmRank::ace:
            rank = HoldEmRank::undefined;
            break;
        case HoldEmRank::undefined:
            break;
    }
    return rank;
}

void set_rank(string rank_string, HoldEmRank& rank) {
    map<string, HoldEmRank> string_to_rank = {
        {"2", HoldEmRank::two},
        {"3", HoldEmRank::three},
        {"4", HoldEmRank::four},
        {"5", HoldEmRank::five},
        {"6", HoldEmRank::six},
        {"7", HoldEmRank::seven},
        {"8", HoldEmRank::eight},
        {"9", HoldEmRank::nine},
        {"10", HoldEmRank::ten},
        {"J", HoldEmRank::jack},
        {"Q", HoldEmRank::queen},
        {"K", HoldEmRank::king},
        {"A", HoldEmRank::ace}
    };
    if (string_to_rank.find(rank_string) != string_to_rank.end()) {
        rank = string_to_rank[rank_string];
    }
}

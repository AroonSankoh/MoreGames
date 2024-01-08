//UnoDeck.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for UnoDeck class and associated functions

#include "UnoDeck.h"

using namespace std; 

UnoDeck::UnoDeck() {
    for (Color colorIter = Color::red; colorIter < Color::black; ++colorIter) {
        card_type card(UnoRank::zero, colorIter);
        pile.push_back(card);
    }
    for (Color colorIter = Color::red; colorIter < Color::black; ++colorIter) {
        for (UnoRank rankIter = UnoRank::one; rankIter < UnoRank::drawfour; ++rankIter) {
            card_type card_1(rankIter, colorIter);
            card_type card_2(rankIter, colorIter);
            pile.push_back(card_1);
            pile.push_back(card_2);
        }
    }
    for (UnoRank rankIter = UnoRank::drawfour; rankIter < UnoRank::undefined; ++rankIter) {
        unsigned int num_black_cards = 4;
        for (unsigned int i = 0; i < num_black_cards; ++i) {
            card_type card(rankIter, Color::black);
            pile.push_back(card);
        }
    }
};

std::ostream& operator<<(std::ostream& stream, const UnoRank &rank) {
    switch (rank) {
         case UnoRank::zero: stream << "0";
            return stream;
            break;
         case UnoRank::one: stream << "1";
            return stream;
            break;
         case UnoRank::two: stream << "2";
            return stream;
            break;
         case UnoRank::three: stream << "3";
            return stream;
            break;
         case UnoRank::four: stream << "4";
            return stream;
            break;
         case UnoRank::five: stream << "5";
            return stream;
            break;
         case UnoRank::six: stream << "6";
            return stream;
            break;
        case UnoRank::seven: stream << "7";
            return stream;
            break;
        case UnoRank::eight: stream << "8";
            return stream;
            break;
        case UnoRank::nine: stream << "9";
            return stream;
            break;
        case UnoRank::skip: stream << "skip";
            return stream;
            break;
        case UnoRank::reverse: stream << "reverse";
            return stream;
            break;
        case UnoRank::drawtwo: stream << "drawtwo";
            return stream;
            break;
        case UnoRank::drawfour: stream << "drawfour";
            return stream;
            break;
        case UnoRank::wild: stream << "wild";
            return stream;
            break;
        case UnoRank::blank: stream << "blank";
            return stream;
            break;
        case UnoRank::undefined: stream << "?";
            return stream;
            break;
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Color &color) {
    switch (color) {
         case Color::red: stream << "red";
            return stream;
            break;
         case Color::blue: stream << "blue";
            return stream;
            break;
         case Color::green: stream << "green";
            return stream;
            break;
         case Color::yellow: stream << "yellow";
            return stream;
            break;
        case Color::black: stream << "black";
            return stream;
            break;
        case Color::undefined: stream << "?";
            return stream;
            break;
    }
    return stream;
}

UnoRank& operator++(UnoRank &rank) {
    switch (rank) {
        case UnoRank::zero:
            rank = UnoRank::one;
            break;
        case UnoRank::one:
            rank = UnoRank::two;
            break;
        case UnoRank::two:
            rank = UnoRank::three;
            break;
        case UnoRank::three:
            rank = UnoRank::four;
            break;
        case UnoRank::four:
            rank = UnoRank::five;
            break;
        case UnoRank::five:
            rank = UnoRank::six;
            break;
        case UnoRank::six:
            rank = UnoRank::seven;
            break;
        case UnoRank::seven:
            rank = UnoRank::eight;
            break; 
        case UnoRank::eight:
            rank = UnoRank::nine;
            break;
        case UnoRank::nine:
            rank = UnoRank::skip;
            break;
        case UnoRank::skip:
            rank = UnoRank::reverse;
            break;
        case UnoRank::reverse:
            rank = UnoRank::drawtwo;
            break;
        case UnoRank::drawtwo:
            rank = UnoRank::drawfour;
            break;
        case UnoRank::drawfour:
            rank = UnoRank::wild;
            break;
        case UnoRank::wild:
            rank = UnoRank::blank;
            break;
        case UnoRank::blank:
            rank = UnoRank::undefined;
            break;
        case UnoRank::undefined:
            break;
    }
    return rank;
}

Color& operator++(Color &color) {
    switch(color) {
        case Color::red:
            color = Color::blue;
            break;
        case Color::blue:
            color = Color::green;
            break;
        case Color::green:
            color = Color::yellow;
            break;
        case Color::yellow:
            color = Color::black;
            break;
        case Color::black:
            color = Color::undefined;
            break;
        case Color::undefined:
            break;
    }
    return color;
}

void set_rank(string rank_string, UnoRank& rank) {
    map<string, UnoRank> string_to_rank = {
        {"0", UnoRank::zero},
        {"1", UnoRank::one},
        {"2", UnoRank::two},
        {"3", UnoRank::three},
        {"4", UnoRank::four},
        {"5", UnoRank::five},
        {"6", UnoRank::six},
        {"7", UnoRank::seven},
        {"8", UnoRank::eight},
        {"9", UnoRank::nine},
        {"skip", UnoRank::skip},
        {"reverse", UnoRank::reverse},
        {"drawtwo", UnoRank::drawtwo},
        {"drawfour", UnoRank::drawfour},
        {"wild", UnoRank::wild},
        {"blank", UnoRank::blank},
    };
    if (string_to_rank.find(rank_string) != string_to_rank.end()) {
        rank = string_to_rank[rank_string];
    }
}
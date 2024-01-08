//PinochleGame.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for PinochleGame class and associated functuons
#pragma once 

#include "Game.h"
#include "PinochleDeck.h"
#include "CardSet_T.h"
#include <map>
#include <algorithm>

enum class PinochleMelds {
    dix, 
    offsuitmarriage, 
    fortyjacks, 
    pinochle, 
    insuitmarriage, 
    sixtyqueens, 
    eightykings, 
    hundredaces, 
    insuitrun, 
    doublepinochle, 
    fourhundredjacks, 
    sixhundredqueens, 
    eighthundredkings, 
    thousandaces, 
    insuitdoublerun
};

typedef vector< Card< PinochleRank, Suit> >::iterator pinochle_vec_iterator;

class PinochleGame: public Game {
    void print();
    void collect_hands();
    bool continue_game();
    void suit_independent_evaluation(const CardSet<PinochleRank, Suit> &hand, std::vector<PinochleMelds> &melds);
    void sort_cards(CardSet<PinochleRank, Suit> &hand);
    void check_melds(CardSet<PinochleRank, Suit> &hand, std::vector<PinochleMelds> &melds);

    bool eight_rank(pinochle_vec_iterator front, pinochle_vec_iterator back, PinochleRank rank);
    bool four_rank(pinochle_vec_iterator front, pinochle_vec_iterator back, PinochleRank rank);
    bool double_pinochle(pinochle_vec_iterator front, pinochle_vec_iterator back);
    bool pinochle(pinochle_vec_iterator front, pinochle_vec_iterator back);
    
    protected: 
        PinochleDeck deck;
        std::vector< CardSet<PinochleRank, Suit> > hands;
        virtual void deal();
        
    public:
        PinochleGame(int argc, const char* argv[]);
        virtual int play();
        //Used a map instead of an array because the size doesn't need to be known before initialization
        static std::map<PinochleMelds, unsigned int> meld_values;
};

std::ostream & operator<<(std::ostream& stream, const PinochleMelds &meld);




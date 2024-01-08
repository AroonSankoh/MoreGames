//HoldEmGame.h
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains declarations for HoldEmGame class and associated functions

#pragma once 

#include "Game.h"
#include "HoldEmDeck.h"
#include "CardSet_T.h"
#include <map>
#include <algorithm>

enum class HoldEmHandRank {
    xhigh,          
    pair,           
    twopair,        
    threeofakind,   
    straight,       
    flush,          
    fullhouse,      
    fourofakind,    
    straightflush,  
    undefined       
};

enum HoldEmGameValues {
    preflop_card_count = 2, 
    hand_size = 5,
    card1 = 0, 
    card2 = 1, 
    card3 = 2, 
    card4 = 3, 
    card5 = 4
};

enum class HoldEmState {
    preflop, 
    flop, 
    turn, 
    river, 
    undefined
}; 

typedef vector< Card< HoldEmRank, Suit> >::iterator holdem_vec_iterator;

class HoldEmGame: public Game {
    void preflop_deal();
    void print_players();
    void print_board(string state);
    void collect_hands();
    bool continue_game();
    HoldEmHandRank holdem_hand_evaluation(const CardSet<HoldEmRank, Suit> &hand);
    HoldEmHandRank check_hands(CardSet<HoldEmRank, Suit> &hand);

    bool valid_hand(holdem_vec_iterator front, holdem_vec_iterator back);
    bool straight_flush(holdem_vec_iterator front, holdem_vec_iterator back);
    bool four_of_a_kind(holdem_vec_iterator front, holdem_vec_iterator back);
    bool full_house(holdem_vec_iterator front, holdem_vec_iterator back);
    bool flush(holdem_vec_iterator front, holdem_vec_iterator back);
    bool straight(holdem_vec_iterator front, holdem_vec_iterator back);
    bool three_of_a_kind(holdem_vec_iterator front, holdem_vec_iterator back);
    bool two_pair(holdem_vec_iterator front, holdem_vec_iterator back);
    bool pair(holdem_vec_iterator front, holdem_vec_iterator back);
    
    protected: 
        HoldEmState state; 
        HoldEmDeck deck;  
        std::vector< CardSet<HoldEmRank, Suit> > hands;
        CardSet<HoldEmRank, Suit> board;
        virtual void deal();
        
    public:
        HoldEmGame(int argc, const char* argv[]);
        virtual int play();
        struct player;
        void evaluate_players(vector<player> &player_list);
        void sort_players(vector<player> &player_list);
};

std::ostream & operator<<(std::ostream& stream, const HoldEmHandRank &rank);
bool operator<(const HoldEmGame::player &a, const HoldEmGame::player &b);

bool compare_equal_hands(CardSet<HoldEmRank, Suit> &hand_1, CardSet<HoldEmRank, Suit> &hand_2, HoldEmHandRank rank);
void choose_priority(CardSet<HoldEmRank, Suit> &hand_1, CardSet<HoldEmRank, Suit> &hand_2, HoldEmHandRank rank);

void prioritize(CardSet<HoldEmRank, Suit> &hand);
void prioritize_pair(CardSet<HoldEmRank, Suit> &hand);
void prioritize_two_pair(CardSet<HoldEmRank, Suit> &hand);
void prioritize_three_of_a_kind(CardSet<HoldEmRank, Suit> &hand);
void prioritize_full_house(CardSet<HoldEmRank, Suit> &hand);
void prioritize_four_of_a_kind(CardSet<HoldEmRank, Suit> &hand);




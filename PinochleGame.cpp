//PinochleGame.cpp
//Aroon Sankoh <a.j.sankoh@wustl.edu>
//Contains definitions for PinochleGame class and associated functions

#include "PinochleGame.h"

using namespace std;

PinochleGame::PinochleGame(int argc, const char* argv[]): Game(argc, argv) {
    for (unsigned int i = 0; i < names.size(); ++i) {
        CardSet<PinochleRank, Suit> hand;
        hands.push_back(hand);
    }
};

void PinochleGame::deal() {
    while (!deck.is_empty()) { 
        for (unsigned int i = 0; i < names.size(); ++i) {
            try {
                deck >> hands[i] >> hands[i] >> hands[i];
            }
            catch (const exception& e) {
                cerr << "Exception Caught: " << e.what() << endl;
            }
        }
    }
}

void PinochleGame::collect_hands() {
    for (unsigned int i = 0; i < names.size(); ++i) {
        deck.collect(hands[i]);
    }
}

void PinochleGame::print() {
    vector<PinochleMelds> player_melds;
    for (unsigned int i = 0; i < names.size(); ++i) {
        cout << names[i] << ": "; 
        for (unsigned int j = 0; j < hands[i].size(); ++j) {
            cout << hands[i].get_card(j) << " ";
        }
        cout << endl;
        player_melds.clear();
        suit_independent_evaluation(hands[i], player_melds);
        for (unsigned int j = 0; j < player_melds.size(); ++j) {
            cout << player_melds[j] << endl;
        }
    }
}

bool PinochleGame::continue_game() {
    string user_response;
    cout << "Would you like to continue playing?" << endl; 
    getline(cin, user_response);
    if (user_response == "yes") {
        return true;
    }
    else {
        return false;
    }
}

/*
* eight_rank(pinochle_vec_iterator front, pinochle_vec_iterator back, PinochleRank rank) checks if there are all eight 
* Aces, Kings, Queens, or Jacks in a cardset
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
* @param rank the rank (Ace, King, Queen, Jack) to check
* @return true if the correct meld is found, false otherwise
*/
bool PinochleGame::eight_rank(pinochle_vec_iterator front, pinochle_vec_iterator back, PinochleRank rank) {
    unsigned int rank_count = 0;
    unsigned int expected_ranks = 8;
    pinochle_vec_iterator i;
    for (i = front; i != back; ++i) {
        if (i->rank == rank) {
            ++rank_count;
        }
    }
    if (rank_count >= expected_ranks) {
        return true;
    }
    return false;
}

/*
* four_rank(pinochle_vec_iterator front, pinochle_vec_iterator back, PinochleRank rank) checks if there is an  
* Ace, King, Queen, or Jack of each suit in a cardset
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
* @param rank the rank (Ace, King, Queen, Jack) to check
* @return true if the correct meld is found, false otherwise
*/
bool PinochleGame::four_rank(pinochle_vec_iterator front, pinochle_vec_iterator back, PinochleRank rank) {
    unsigned int rank_count = 0;
    unsigned int expected_ranks = 4;
    map<Suit, int> suit_frequency;
    pinochle_vec_iterator i;
    for (i = front; i != back; ++i) {
        if (i->rank == rank) {
            ++rank_count;
            suit_frequency[i->suit]++;
        }
    }

    
    //Should be at least one of each suit
    for (Suit suitIter = Suit::clubs; suitIter < Suit::undefined; ++suitIter) {
        if (suit_frequency[suitIter] < 1) {
            return false;
        }
    }

    if (rank_count >= expected_ranks) {
        return true;
    }
    return false;
}

/*
* double_pinochle(pinochle_vec_iterator front, pinochle_vec_iterator back) checks if there are two 
* jacks of diamonds and two queen of spades
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
* @return true if the correct meld is found, false otherwise
*/
bool PinochleGame::double_pinochle(pinochle_vec_iterator front, pinochle_vec_iterator back) {
    int num_jack_diamonds = 0;
    int num_queen_spades = 0;
    int expected_rank = 2;
    pinochle_vec_iterator i;
    for (i = front; i != back; ++i) { 
        if (i->rank == PinochleRank::queen && i->suit == Suit::spades) {
            ++num_queen_spades;
        }
        if (i->rank == PinochleRank::jack && i->suit == Suit::diamonds) {
            ++num_jack_diamonds;
        }
    }
    if (num_jack_diamonds == expected_rank && num_queen_spades == expected_rank) {
        return true;
    }
    return false;
}

/*
* pinochle(pinochle_vec_iterator front, pinochle_vec_iterator back) checks if there is a 
* jack of diamonds and queen of spades
*
* @param front a vector iterator to the front of the hand 
* @param back a vector iterator to the back of the hand 
* @return true if the correct meld is found, false otherwise
*/
bool PinochleGame::pinochle(pinochle_vec_iterator front, pinochle_vec_iterator back) {
    pinochle_vec_iterator i;
    pinochle_vec_iterator j;
    for (i = front; i != back; ++i) { 
        for (j = i; j != back; ++j) {
            if ( (i->rank== PinochleRank::queen && i->suit == Suit::spades) 
            && (j->rank == PinochleRank::jack && j->suit == Suit::diamonds) ) {
                return true;
            }
        }
    }
    return false;
}

void PinochleGame::sort_cards(CardSet<PinochleRank, Suit> &hand) {
    hand.sort_set();
    reverse(hand.get_front(), hand.get_back());
}

void PinochleGame::check_melds(CardSet<PinochleRank, Suit> &hand, std::vector<PinochleMelds> &melds) {
    pinochle_vec_iterator front = hand.get_front();
    pinochle_vec_iterator back = hand.get_back();
    if (eight_rank(front, back, PinochleRank::ace)) {
        melds.push_back(PinochleMelds::thousandaces);
    } 
    else if (four_rank(front, back, PinochleRank::ace)) {
        melds.push_back(PinochleMelds::hundredaces);
    }
    if (eight_rank(front, back, PinochleRank::king)) {
        melds.push_back(PinochleMelds::eighthundredkings);
    }
    else if (four_rank(front, back, PinochleRank::king)) {
        melds.push_back(PinochleMelds::eightykings);
    }
    if (eight_rank(front, back, PinochleRank::queen)) {
        melds.push_back(PinochleMelds::sixhundredqueens);
    }
    else if (four_rank(front, back, PinochleRank::queen)) {
        melds.push_back(PinochleMelds::sixtyqueens);
    }
    if (eight_rank(front, back, PinochleRank::jack)) {
        melds.push_back(PinochleMelds::fourhundredjacks);
    }
    else if (four_rank(front, back, PinochleRank::jack)) {
        melds.push_back(PinochleMelds::fortyjacks);
    }
    if (double_pinochle(front, back)) {
        melds.push_back(PinochleMelds::doublepinochle);
    }
    else if (pinochle(front, back)) {
        melds.push_back(PinochleMelds::pinochle);
    }
}

/*
* suit_independent_evaluation(const CardSet<PinochleRank, Suit> &hand, std::vector<PinochleMelds> &melds) 
* checks a player's hand for Pinochle melds and pushes melds into the vector accordingly 
*
* @param hand the passed in cardset
* @param melds the vector to push melds into 
*/
void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, Suit> &hand, std::vector<PinochleMelds> &melds) {
    CardSet<PinochleRank, Suit> c_set(hand);
    sort_cards(c_set);
    check_melds(c_set, melds);
}

int PinochleGame::play() {
    bool game_state = true;
    while (game_state) {
        deck.shuffle();
        deal();
        print();
        collect_hands();
        game_state = continue_game();
    }
    return game_over;
}

std::map<PinochleMelds, unsigned int> PinochleGame::meld_values = {
    {PinochleMelds::dix, 10},
    {PinochleMelds::offsuitmarriage, 20},
    {PinochleMelds::fortyjacks, 40},
    {PinochleMelds::pinochle, 40},
    {PinochleMelds::insuitmarriage, 40},
    {PinochleMelds::sixtyqueens, 60},
    {PinochleMelds::eightykings, 80},
    {PinochleMelds::hundredaces, 100},
    {PinochleMelds::insuitrun, 150},
    {PinochleMelds::doublepinochle, 300},
    {PinochleMelds::fourhundredjacks, 400},
    {PinochleMelds::sixhundredqueens, 600},
    {PinochleMelds::eighthundredkings, 800},
    {PinochleMelds::thousandaces, 1000},
    {PinochleMelds::insuitdoublerun, 1500}
};

ostream & operator<<(ostream& stream, const PinochleMelds &meld) {
    switch (meld) {
        case PinochleMelds::dix: stream << "Dix: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::offsuitmarriage: stream << "Off Suit Marraige: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::fortyjacks: stream << "Forty Jacks: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::pinochle: stream << "Pinochle: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::insuitmarriage: stream << "In Suit Marraige: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::sixtyqueens: stream << "Sixty Queens: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::eightykings: stream << "Eighty Kings: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::hundredaces: stream << "Hundred Aces: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::insuitrun: stream << "In Suit Run: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::doublepinochle: stream << "Double Pinochle: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::fourhundredjacks: stream << "Four Hundred Jacks: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::sixhundredqueens: stream << "Six Hundred Queens: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::eighthundredkings: stream << "Eight Hundred Kings: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::thousandaces: stream << "Thousand Aces: " << PinochleGame::meld_values[meld];
            return stream;
            break;
        case PinochleMelds::insuitdoublerun: stream << "In Suit Double Run: " << PinochleGame::meld_values[meld];
            return stream;
            break;
    }
    return stream;
}


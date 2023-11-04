#ifndef Gameboard_hpp
#define Gameboard_hpp
// Header Files
#include "PokerHand.hpp"

// Object representing 3 Card Poker table
class Gameboard {
public:
    Gameboard();
    
    // MARK: Mutators
    void shuffleDeck();
    void dealPlayerHand();
    void dealHouseHand();
    
    // MARK: Accessors
    Hand getPlayerHand() const { return this->playerHand; }
    Hand getHouseHand()  const { return this->houseHand;  }
    
    // MARK: Print Functions
    void printHandFaceDown();
    void printHandFaceUp(const Hand& hand);
    
    // MARK: Game Functions
    HandRankings rankHand(Hand& hand);
    void determineWinner();
    void printResults();
    
    friend class PokerGame;
    
private:
    Card deck[DECKSIZE];
    Hand playerHand;
    Hand houseHand;
    Results results;
};

#endif // Gameboard_hpp

#ifndef PokerHand_hpp
#define PokerHand_hpp

// Libraries
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>

// MARK: Global constants
// Total number of playing cards in a standard deck (No Jokers)
const int DECKSIZE = 52;
// Number of cards dealt per game
const int HANDSIZE = 3;
// Unicode for suit symbols
const char heart[]   = "\u2665";
const char diamond[] = "\u2666";
const char club[]    = "\u2663";
const char spade[]   = "\u2660";

enum GameOutcomes {
    PLAYERWON = 1,
    HOUSEWON  = 2,
    TIE       = 3
};

// Dealt hands are assigned a rank and compared using this enumerated data type
enum HandRankings {
    MINIROYALFLUSH = 7,
    STRAIGHTFLUSH  = 6,
    THREEOFAKIND   = 5,
    STRAIGHT       = 4,
    FLUSH          = 3,
    ONEPAIR        = 2,
    HIGHCARD       = 1,
    NONE           = 0
};

struct Results {
    HandRankings winningRank;
    GameOutcomes outcome;
};

// Represents the suit of a Card
enum Suit {
    HEARTS   = 1,
    DIAMONDS = 2,
    CLUBS    = 3,
    SPADES   = 4
};

// Structure that represents a playing card
struct Card {
    Suit suit;
    int value;
};

// Structure that represents a dealt hand
struct Hand {
    Card cards[HANDSIZE];
    HandRankings ranking;
    
    Hand getSortedCards(const Hand& hand) const {
        Hand orderedCards;
        orderedCards.cards[0] = hand.cards[0];
        
        // MARK: Sort cards by value
        if(hand.cards[1].value < orderedCards.cards[0].value) {
            // Move old lowest value to second position
            orderedCards.cards[1] = orderedCards.cards[0];
            // Insert new lowest value to first position
            orderedCards.cards[0] = hand.cards[1];
            
        }
        else {
            // Insert higher value at second position
            orderedCards.cards[1] = hand.cards[1];
        }
        if(hand.cards[2].value < orderedCards.cards[1].value) {
            
            orderedCards.cards[2] = orderedCards.cards[1];
            orderedCards.cards[1] = hand.cards[2];
            if(hand.cards[2].value < orderedCards.cards[0].value) {
                orderedCards.cards[1] = orderedCards.cards[0];
                orderedCards.cards[0] = hand.cards[2];
            }
        }
        else {
            orderedCards.cards[2] = hand.cards[2];
        }
        
        return orderedCards;
    }
        
    bool hasOnePair(const Hand& hand) const {
        return(hand.cards[0].value == hand.cards[1].value ||
               hand.cards[0].value == hand.cards[2].value ||
               hand.cards[1].value == hand.cards[2].value);
    }
    bool hasFlush(const Hand& hand) const {
        return(hand.cards[0].suit == hand.cards[1].suit &&
               hand.cards[1].suit == hand.cards[2].suit);
    }
    bool hasStraight(const Hand& hand) const {
        Hand orderedCards;
        orderedCards = hand.getSortedCards(hand);
        
        return(orderedCards.cards[0].value + 1 == orderedCards.cards[1].value &&
               orderedCards.cards[1].value + 1 == orderedCards.cards[2].value);
    }
    bool hasThreeOfAKind(const Hand& hand) const {
        return(hand.cards[0].value == hand.cards[1].value &&
               hand.cards[1].value == hand.cards[2].value);
    }
    bool hasStraightFlush(const Hand& hand) const {
        return(hand.hasStraight(hand) && hand.hasFlush(hand)) ? true : false;
    }
    bool hasMiniRoyalFlush(const Hand& hand) const {
        Hand orderedCards;
        // Sort cards by value (low -> high)
        orderedCards = hand.getSortedCards(hand);
        
        // Determine if hand has flush
        if(orderedCards.hasFlush(hand)) {
            // Determine if hand contains Queen, King, and Ace
            if(orderedCards.cards[0].value == 12 &&
               orderedCards.cards[1].value == 13 &&
               orderedCards.cards[2].value == 14) {
                return true;
            }
        }
        // Else
        return false;
    }
};

struct PlayerBets {
    PlayerBets() {
        this->pairPlusBet  = 0;
        this->anteBonusBet = 0;
        this->playBet      = 0;
    }

    static int playerMoney;
    int pairPlusBet, anteBonusBet, playBet;
    
};

#endif // PokerHand_hpp

#include "Gameboard.hpp"
#include <iostream>

Gameboard::Gameboard() {
    // Control index of arrays
    int index = 0;
    
    // MARK: Fill card deck with 52 playing cards
    for(int i = 1; i <= 4; i++) {
        for(int j = 2; j <= 14; j++) {
            this->deck[index].suit  = static_cast<Suit>(i);
            this->deck[index].value = j;
            index++;
        }
    }
}

void Gameboard::shuffleDeck() {
    int timesShuffled;
    int numCardsMoved;
    int pos1, pos2;
    Card temp;
    
    timesShuffled = rand() % 20 + 5;
    numCardsMoved = rand() % 22 + 30;
    
    for(int i = 0; i < timesShuffled; i++) {
        for(int j = 0; j < numCardsMoved; j++) {
            // Prevent self swap
            do {
                pos1 = rand() % 51 + 0;
                pos2 = rand() % 51 + 0;
            }while(pos1 == pos2);
            // Swap Cards
            temp.value = this->deck[pos1].value;
            temp.suit  = this->deck[pos1].suit;
            this->deck[pos1].value = this->deck[pos2].value;
            this->deck[pos1].suit  = this->deck[pos2].suit;
            this->deck[pos2].value = temp.value;
            this->deck[pos2].suit  = temp.suit;
        }
    }
}

void Gameboard::dealPlayerHand() {
    // Deals top 3 cards to player (dealt first)
    for(int i = 0; i < 3; i++)
        this->playerHand.cards[i] = this->deck[i];
}

void Gameboard::dealHouseHand() {
    // Deals the following top 3 cards to house (dealt second)
    for(int i = 0; i < 3; i++)
        this->houseHand.cards[i] = this->deck[i+3];
}

void Gameboard::printHandFaceDown() {
    // Print tops of cards
    for(int i = 0; i < 3; i++) {
        std::cout << " _____ " << ' ';
    }
    
    std::cout << std::endl;
    
    // Print the cards' designs
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == 0 || i == 3) {
                std::cout << "|* * *| ";
            }
            else {
                std::cout << "| * * | ";
            }
        }
        std::cout << std::endl;
    }
    
    // Print bottom of cards
    for(int i = 0; i < 3; i++) {
        std::cout << " ‾‾‾‾‾ " << ' ';
    }
    
    std::cout << std::endl;
}

void Gameboard::printHandFaceUp(const Hand& hand) {
    // Print tops of cards
    for(int i = 0; i < 3; i++) {
        std::cout << " _____ " << ' ';
    }
    
    std::cout << std::endl;
    
    // Print lines containing values of cards
    for(int i = 0; i < 3; i++) {
        // Output characters for face cards
        switch(hand.cards[i].value) {
            case 14:  // Ace
                std::cout << "|" << 'A' << "    | ";
                break;
            case 13: // King
                std::cout << "|" << 'K' << "    | ";
                break;
            case 12: // Queen
                std::cout << "|" << 'Q' << "    | ";
                break;
            case 11: // Jack
                std::cout << "|" << 'J' << "    | ";
                break;
            case 10: // Added custom print for double digit value to avoid spacing issues
                std::cout << "|" << 10  << "   | ";
                break;
            default: // 2 - 9
                std::cout << "|" << hand.cards[i].value << "    | ";
                break;
        }
    }
    
    std::cout << std::endl;
    
    for(int i = 0; i < 3; i++) {
        // Print line containing card suit
        switch(hand.cards[i].suit) {
            case HEARTS:
                std::cout << "|" << heart   << "    | ";
                break;
            case DIAMONDS:
                std::cout << "|" << diamond << "    | ";
                break;
            case CLUBS:
                std::cout << "|" << club    << "    | ";
                break;
            case SPADES:
                std::cout << "|" << spade   << "    | ";
        }
    }
    
    std::cout << std::endl;
    
    // Print remains of visual card
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            switch(i) {
                case 0:
                case 1:
                    std::cout << "|     |" << ' ';
                    break;
                case 2:
                    std::cout << " ‾‾‾‾‾ " << ' ';
                    break;
            }
        }
        std::cout << std::endl;
    }
}

HandRankings Gameboard::rankHand(Hand& hand) {
    if(hand.hasMiniRoyalFlush(hand)) {
        return MINIROYALFLUSH;
    }
    else if(hand.hasStraightFlush(hand)) {
        return STRAIGHTFLUSH;
    }
    else if(hand.hasThreeOfAKind(hand)) {
        return THREEOFAKIND;
    }
    else if(hand.hasStraight(hand)) {
        return STRAIGHT;
    }
    else if(hand.hasFlush(hand)) {
        return FLUSH;
    }
    else if(hand.hasOnePair(hand)) {
        return ONEPAIR;
    }
    // Else
    return HIGHCARD;
}

void Gameboard::determineWinner() {
    Hand player, house;
    
    player = this->getPlayerHand();
    house  = this->getHouseHand();
    player.ranking = this->rankHand(player);
    house.ranking  = this->rankHand(house);
    
    if(player.ranking > house.ranking) {
        this->results.outcome = PLAYERWON;
        this->results.winningRank = player.ranking;
    }
    else if(house.ranking > player.ranking) {
        this->results.outcome = HOUSEWON;
        this->results.winningRank = house.ranking;
    }
    else if(player.ranking == house.ranking) {
        // Sort cards by value from low to high
        player = player.getSortedCards(player);
        house  = house.getSortedCards(house);
        
        // Check highest card
        if(player.cards[2].value > house.cards[2].value) {
            this->results.outcome = PLAYERWON;
            this->results.winningRank = HandRankings::HIGHCARD;
        }
        else if(house.cards[2].value > player.cards[2].value) {
            this->results.outcome = HOUSEWON;
            this->results.winningRank = HandRankings::HIGHCARD;
        }
        else if(house.cards[2].value == player.cards[2].value) {
            // Highest cards have equal value, check second highest value
            if(player.cards[1].value > house.cards[1].value) {
                this->results.outcome = PLAYERWON;
                this->results.winningRank = HandRankings::HIGHCARD;
            }
            else if(house.cards[1].value > player.cards[1].value) {
                this->results.outcome = HOUSEWON;
                this->results.winningRank = HandRankings::HIGHCARD;
            }
            else if(house.cards[1].value == player.cards[1].value) {
                // Second highest cards have equal value, check third highest value
                if(player.cards[0].value > house.cards[0].value) {
                    this->results.outcome = PLAYERWON;
                    this->results.winningRank = HandRankings::HIGHCARD;
                }
                else if(house.cards[0].value > player.cards[0].value) {
                    this->results.outcome = HOUSEWON;
                    this->results.winningRank = HandRankings::HIGHCARD;
                }
                else if(house.cards[0].value == player.cards[0].value) {
                    // All 3 cards of each hand have the same value, house and player tie
                    this->results.outcome = TIE;
                    this->results.winningRank = HandRankings::NONE;
                }
            }
        }
    }
}

void Gameboard::printResults() {
    std::string winningHand;
    
    switch(this->results.winningRank) {
        case MINIROYALFLUSH: winningHand = "Mini Royal Flush";
            break;
        case STRAIGHTFLUSH: winningHand = "Straight Flush";
            break;
        case THREEOFAKIND: winningHand = "Three of a Kind";
            break;
        case STRAIGHT: winningHand = "Straight";
            break;
        case FLUSH: winningHand = "Flush";
            break;
        case ONEPAIR: winningHand = "One Pair";
            break;
        case HIGHCARD: winningHand = "High Card";
            break;
        case NONE: winningHand = "";
            break;
        default: winningHand = "";
            break;
    }
    
    switch(this->results.outcome) {
        case PLAYERWON:
            std::cout << "Player won - [" + winningHand + "]" << std::endl;
            std::cout << "Congratulations, you won!" << std::endl;
            break;
        case HOUSEWON:
            std::cout << "House won - [" + winningHand + "]" << std::endl;
            std::cout << "Sorry, you lost." << std::endl;
            break;
        case TIE:
            std::cout << "Tie!" << std::endl;
            break;
        default:
            std::cout << "Unknown outcome" << std::endl;
            break;
    }
    std::cout << std::endl;
}


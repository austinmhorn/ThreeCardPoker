#include "Gameboard.hpp"
#include <stdio.h>

int main(int argc, const char * argv[]) {
    // Seed time to system
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    
    // Allocate memory for Gameboard object
    Gameboard * game = new Gameboard();

    // Randomize card positions
    game->shuffleDeck();

    // Deal Player cards
    game->dealPlayerHand();
    // Deal House cards
    game->dealHouseHand();
    
    std::cout << std::endl << "      Dealer Hand   " << std::endl;
    // Display hidden House hand
    game->printHandFaceDown();
    
    std::cout << "      Player Hand   " << std::endl;
    // Display hidden Player hand
    game->printHandFaceDown();
    
    std::cout << std::endl << ">> Press RETURN to see the results <<";
    std::cin.ignore();

    std::cout << std::endl << "      Dealer Hand   " << std::endl;
    // Display revealed House hand
    game->printHandFaceUp( game->getHouseHand() );
    
    std::cout << "      Player Hand   " << std::endl;
    // Display revealed Player hand
    game->printHandFaceUp( game->getPlayerHand() );

    // Determine game results
    game->determineWinner();
    // Print results
    game->printResults();

    // Deallocate memory for Gameboard object
    delete game;
    
    return 0;
}

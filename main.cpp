#include <iostream>
#include <array>
#include <iterator>
#include <optional>
#include <unordered_map>
#include <thread>
#include "deck.h"
#include "utils.h"
#include "constants.h"
#include "hand.h"
#include "game_state.h"

int main(int argc, const char * argv[]) {
    Deck baseDeck{};
    baseDeck.init();
    
    int numPlayers{};
    while (1)
    {
        std::cout << "Enter number of players: ";
        if (std::cin >> numPlayers)
        {
            if (numPlayers >= 2 && numPlayers <= 9)
            {
                break;
            }
            else
            {
                std::cout << "Number of players must be 2 through 9\n"
                << std::endl;
            }
        }
        else
        {
            std::cout << "Please enter a valid integer (2-9)\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
    
    std::vector<std::vector<Card>> playerList(numPlayers);
    baseDeck.getHoleCards(playerList);
    
    Deck t1Deck = baseDeck;
    t1Deck.reseed();
    Deck t2Deck = baseDeck;
    t2Deck.reseed();

    std::vector<float> t1Results(playerList.size());
    std::thread t1{
        results,
        t1Deck,
        std::cref(playerList),
        std::ref(t1Results)};
    
    std::vector<float> t2Results(playerList.size());
    std::thread t2{
        results,
        t2Deck,
        std::cref(playerList),
        std::ref(t2Results)};
    
    t1.join();
    t2.join();
    
    std::vector<float> mergedResults(playerList.size());
    for (std::size_t i{}; i < playerList.size(); ++i)
    {
        mergedResults[i] = t1Results[i] + t2Results[i];
    }

    calculateEquity(mergedResults);

    return 0;
}

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
    std::cout << "Enter number of players: ";
    std::cin >> numPlayers;
    if (numPlayers <= 1 || numPlayers > RESULT_SIZE)
    {
        throw std::invalid_argument(
            "Number of players must be 2 through RESULT_SIZE");
    }
    
    std::vector<std::vector<Card>> playerList(numPlayers);
    baseDeck.getHoleCards(playerList);
    Deck t1Deck = baseDeck;
    Deck t2Deck = baseDeck;

    std::array<float, RESULT_SIZE> t1Results{};
    std::thread t1{
        results,
        t1Deck,
        std::cref(playerList),
        std::ref(t1Results)};
    
    std::array<float, RESULT_SIZE> t2Results{};
    std::thread t2{
        results,
        t2Deck,
        std::cref(playerList),
        std::ref(t2Results)};
    
    t1.join();
    t2.join();
    
    std::array<float, RESULT_SIZE> mergedResults{};
    for (std::size_t i{}; i < RESULT_SIZE; ++i)
    {
        mergedResults[i] = t1Results[i] + t2Results[i];
    }

    calculateEquity(mergedResults);

    return 0;
}

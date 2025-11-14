#include "game_state.h"
#include "utils.h"
#include "hand.h"
#include <iostream>

void printGame(const std::vector<std::vector<Card>>& playerList,
               const std::vector<HandValue>& playerValues,
               const std::vector<Card>& board)
{
    std::vector<HandValue> winners = compareHands(playerValues);
    for (auto num : winners)
    {
        std::cout << "Winning hand type: " <<
        rankToType(static_cast<int>(num.type)) <<
        "\t Winning hand index: " << num.index << std::endl;
    }
    std::cout << "Board: ";
    printCards(board);
    std::cout << std::endl << "Players: ";
    for (auto player : playerList)
    {
        printCards(player);
        std::cout << "\t";
    }
    std::cout << std::endl;
}

void calculateEquity(std::array<float, RESULT_SIZE> winCount)
{
    for (int i{}; i < winCount.size(); ++i)
    {
        if (winCount[i] != 0)
        {
            std::cout << "Player " << i + 1 << " equity: " <<
            (winCount[i] / TRIALS) * 100 / THREAD_COUNT << "%" << std::endl;
        }
    }
}

void results(Deck deck,
             const std::vector<std::vector<Card>>& playerList,
             std::array<float, RESULT_SIZE>& threadResults)
{
    std::vector<HandValue> playerValues{};
    playerValues.reserve(playerList.size());
    std::vector<Card> board;
    board.reserve(BOARD_SIZE);
    for (size_t i{}; i < TRIALS; ++i)
    {
        deck.shuffle();
        deck.deal(board, BOARD_SIZE);
        for (size_t i{}; i < playerList.size(); ++i)
        {
            playerValues.push_back(evaluateHand(board, playerList[i]));
        }
        std::vector<HandValue> winners = compareHands(playerValues);
        float split = 1.0f / winners.size();
        for (auto winner : winners)
        {
            threadResults[winner.index] += split;
        }
        board.clear();
        playerValues.clear();
    }
}

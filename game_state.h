#pragma once
#include "hand.h"
#include "deck.h"

void printGame(const std::vector<std::vector<Card>>& playerList,
               const std::vector<HandValue>& playerValues,
               const std::vector<Card>& board);

void calculateEquity(std::array<float, RESULT_SIZE> winCount);

void results(Deck deck,
             const std::vector<std::vector<Card>>& playerList,
             std::array<float, RESULT_SIZE>& threadResults);


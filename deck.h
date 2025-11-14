#pragma once
#include "card.h"
#include <vector>
#include <random>

class Deck
{
public:
    void init();
    void shuffle();
    void deal(std::vector<Card>& spot, std::size_t cardsDealt);
    void getHoleCards(std::vector<std::vector<Card>>& playerList);

private:
    std::vector<Card> cards;
    std::mt19937 rng{std::random_device{}()};
    std::size_t nextCard{};
};


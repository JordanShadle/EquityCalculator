#include "deck.h"
#include <iostream>
#include <algorithm>
#include <array>
#include "utils.h"

void Deck::init()
{
    cards.reserve(52);
    std::array<Suit, 4> suits = {Suit::c, Suit::d, Suit::h, Suit::s};
    for (auto suit : suits)
    {
        for (int rank = 2; rank <= 14; ++rank)
        {
            cards.push_back({rank, suit});
        }
    }
}

void Deck::shuffle()
{
    std::shuffle(cards.begin(), cards.end(), rng);
    nextCard = 0;
}

void Deck::deal(std::vector<Card>& spot, std::size_t cardsDealt)
{
    if (nextCard + cardsDealt > cards.size())
    {
        throw std::invalid_argument("Not enough cards in deck");
    }
    else
    {
        for (std::size_t i{}; i < cardsDealt; i++)
        {
            spot.push_back(cards[nextCard++]);
        }
    }
}

void Deck::getHoleCards(std::vector<std::vector<Card>>& playerList)
{
    const std::size_t cardCount = playerList.size() * 2;
    Card currentCard{};
    char currentChar;
    int cardIndex{};
    std::vector<int> indicesList;
    indicesList.reserve(cardCount);
    
    std::cout << "Enter cards: ";
    
    for (size_t i{}; i < cardCount; ++i)
    {
        std::cin >> currentCard.rank;
        std::cin >> currentChar;
        currentCard.suit = charToSuit(currentChar);
        
        cardIndex = (currentCard.rank - 2) +
        (static_cast<int>(currentCard.suit) * 13);
        
        for (int index : indicesList)
        {
            if (currentCard.rank == cards[index].rank &&
                currentCard.suit == cards[index].suit)
            {
                throw std::invalid_argument("Duplicate hole cards not allowed");
            }
        }
        indicesList.push_back(cardIndex);

        
        playerList[i/2].push_back(currentCard);
    }
    
    std::sort(indicesList.begin(), indicesList.end(), std::greater<int>());
    for (int index : indicesList)
    {
        cards.erase(cards.begin() + index);
    }
}

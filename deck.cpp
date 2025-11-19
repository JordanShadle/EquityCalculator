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
    std::string cardInput;
    std::vector<int> indexList;
    indexList.reserve(cardCount);
    
    while(1)
    {
        bool validInput = true;
        for (auto& player : playerList)
        {
            player.clear();
        }
        indexList.clear();
        std::cout << "Enter cards: ";

        for (size_t i{}; i < cardCount; ++i)
        {
            std::cin >> cardInput;
            
            if (cardInput.size() < 2 || cardInput.size() > 3)
            {
                std::cout << "Invalid card\n";
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                validInput = false;
                break;
            }
            
            if (cardInput[0] == '1' &&
                (cardInput[1] >= '0' && cardInput[1] <= '4'))
            {
                currentCard.rank = 10 + (cardInput[1] - '0');
            }
            else
            {
                currentCard.rank = charToRank(cardInput[0]);
                if (currentCard.rank < 2 || currentCard.rank > 14)
                {
                    std::cout << "Invalid rank: " << currentCard.rank << "\n";
                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(), '\n');
                    validInput = false;
                    break;
                }
            }
            
            if (cardInput.size() == 2)
            {
                currentCard.suit = charToSuit(cardInput[1]);
            }
            else if (cardInput.size() == 3)
            {
                currentCard.suit = charToSuit(cardInput[2]);
            }
            
            if (currentCard.suit == Suit::invalid_suit)
            {
                std::cout << "Invalid suit: " <<
                suitToChar(currentCard.suit) << "\n";
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                validInput = false;
                break;
            }
            
            int cardIndex = (currentCard.rank - 2) +
            (static_cast<int>(currentCard.suit) * 13);
            
            if (std::find(indexList.begin(), indexList.end(), cardIndex)
                != indexList.end())
            {
                std::cout << "Duplicate hole cards not allowed\n";
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                validInput = false;
                break;
            }
            
            indexList.push_back(cardIndex);
            playerList[i/2].push_back(currentCard);
        }
        
        if (validInput)
        {
            break;
        }
    }
    
    std::sort(indexList.begin(), indexList.end(), std::greater<int>());
    for (int index : indexList)
    {
        cards.erase(cards.begin() + index);
    }
}

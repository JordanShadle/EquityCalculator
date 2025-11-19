#include "utils.h"
#include "constants.h"
#include <iostream>

char suitToChar(Suit suit)
{
    switch (suit)
    {
        case Suit::c: return 'c';
        case Suit::d: return 'd';
        case Suit::h: return 'h';
        case Suit::s: return 's';
        default:
            return '?';
    }
}

Suit charToSuit(char suit)
{
    switch (suit)
    {
        case 'c': return Suit::c;
        case 'd': return Suit::d;
        case 'h': return Suit::h;
        case 's': return Suit::s;
        default:
            return Suit::invalid_suit;
    }
}

char rankToChar(int rank)
{
    if (rank >= MIN_RANK && rank <= 9)
    {
        return static_cast<char>('0' + rank);
    }
    switch (rank)
    {
        case MAX_RANK: return 'A';
        case 13: return 'K';
        case 12: return 'Q';
        case 11: return 'J';
        case 10: return 'T';
    }
    return '?';
}

int charToRank(char rank)
{
    switch (rank)
    {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
            return 11;
        case 'T':
            return 10;
            break;
        default:
            if (rank >= '2' && rank <= '9')
            {
                return rank - '0';
            }
    }
    return 0;
}

std::string rankToType(int rank)
{
    switch (rank)
    {
        case 0: return "High Card";
        case 1: return "Pair";
        case 2: return "Two Pair";
        case 3: return "Trips";
        case 4: return "Straight";
        case 5: return "Flush";
        case 6: return "Full House";
        case 7: return "Quads";
        case 8: return "Straight Flush";
    }
    return "Invalid type";
}

void printCards(const std::vector<Card>& cards)
{
    for (const auto& card : cards)
    {
        std::cout << rankToChar(card.rank) << suitToChar(card.suit) << " ";
    }
}

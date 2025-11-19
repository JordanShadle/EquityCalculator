#pragma once

enum class Suit { c, d, h, s, invalid_suit };

struct Card
{
    int rank;
    Suit suit;
};

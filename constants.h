#pragma once

constexpr int MAX_RANK = 14;
constexpr int MIN_RANK = 2;
constexpr int QUADS_COUNT = 4;
constexpr int TRIPS_COUNT = 3;
constexpr int PAIR_COUNT = 2;
constexpr int STRAIGHT_LEN = 5;
constexpr int TRIALS = 50000;
constexpr int BOARD_SIZE = 5;
constexpr int THREAD_COUNT = 2;

enum class HandType
{
    unassigned = -1,
    highCard = 0,
    pair = 1,
    twoPair = 2,
    trips = 3,
    straight = 4,
    flush = 5,
    fullHouse = 6,
    quads = 7,
    straightFlush = 8
};

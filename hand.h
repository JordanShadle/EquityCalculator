#pragma once
#include <vector>
#include <array>
#include <optional>
#include "card.h"
#include "constants.h"

struct HandValue
{
    HandType type = HandType::unassigned;
    std::array<int, 5> ranks = {0};
    int index = -1;
};

void pairTrack(const std::vector<Card>& hand,
               std::vector<std::pair<int, int>>& pairCount,
               std::vector<int>& orderedKickers);

std::optional<HandValue> isStraightFlush(const std::vector<Card>& hand,
                                         HandValue& flushValue);
std::optional<HandValue> isQuads(
                            const std::vector<std::pair<int,int>>& pairCount,
                            const std::vector<int>& orderedKickers);
std::optional<HandValue> isFullHouse(
                            const std::vector<std::pair<int,int>>& pairCount,
                            const std::vector<int>& orderedKickers);
std::optional<HandValue> isStraight(std::vector<Card>& hand);
std::optional<HandValue> isTrips(
                            const std::vector<std::pair<int,int>>& pairCount,
                            const std::vector<int>& orderedKickers);
std::optional<HandValue> isTwoPair(
                            const std::vector<std::pair<int,int>>& pairCount,
                            const std::vector<int>& orderedKickers);
std::optional<HandValue> isPair(
                            const std::vector<std::pair<int,int>>& pairCount,
                            const std::vector<int>& orderedKickers);

HandValue evaluateHand(const std::vector<Card>& board, std::vector<Card> hand);
std::vector<HandValue> compareHands(std::vector<HandValue> hands);

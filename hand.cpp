#include "hand.h"
#include <algorithm>
#include <unordered_map>

void pairTrack(const std::vector<Card>& hand,
               std::vector<std::pair<int, int>>& pairCount,
               std::vector<int>& orderedKickers)
{
    pairCount.clear();
    orderedKickers.clear();
    std::array<int, 15> rankCount{};
    for (const auto& card: hand)
    {
        rankCount[card.rank] += 1;
    }
    for (int r = MAX_RANK; r >= MIN_RANK; --r)
    {
        if (rankCount[r] == 1)
        {
            orderedKickers.push_back(r);
        }
    }
    for (std::size_t i = MIN_RANK; i <= MAX_RANK; ++i)
    {
        if (rankCount[i] >= PAIR_COUNT)
        {
            pairCount.push_back({ rankCount[i], i });
        }
    }
    std::sort(pairCount.begin(), pairCount.end(),
              [](auto& a, auto& b){
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    });
}

std::optional<HandValue> isStraightFlush(const std::vector<Card>& hand,
                                         HandValue& flushValue)
{
    HandValue returnValue{};
    std::unordered_map<Suit, std::vector<int>> flushMap;
    for (std::size_t i{}; i < hand.size(); ++i)
    {
        flushMap[hand[i].suit].push_back(hand[i].rank);
    }
    for (auto& element : flushMap)
    {
        if (element.second.size() >= STRAIGHT_LEN)
        {
            std::sort(element.second.begin(), element.second.end());
            int straightCount = 1;
            for (auto it = element.second.begin();
                 std::next(it) != element.second.end();
                 ++it)
            {
                int nextVal = *std::next(it);
                if (*it + 1 == nextVal)
                {
                    ++straightCount;
                }
                else
                {
                    straightCount = 1;
                }
                if (straightCount == STRAIGHT_LEN ||
                    (straightCount == STRAIGHT_LEN - 1 &&
                     nextVal == 5 &&
                     element.second.back() == MAX_RANK))
                {
                    returnValue.type = HandType::straightFlush;
                    returnValue.ranks[0] = nextVal;
                    return returnValue;
                }
            }
            // flushValue is set for later use in evaluateHand()
            flushValue.type = HandType::flush;
            std::copy_n(element.second.rbegin(), 5, flushValue.ranks.begin());
            return std::nullopt;
        }
    }
    return std::nullopt;
}

std::optional<HandValue> isQuads(
                            const std::vector<std::pair<int, int>>& pairCount,
                            const std::vector<int>& orderedKickers)
{
    if (pairCount.empty() || pairCount[0].first < QUADS_COUNT)
    {
        return std::nullopt;
    }
    HandValue returnValue{};
    returnValue.type = HandType::quads;
    returnValue.ranks[0] = pairCount[0].second;
    if (!orderedKickers.empty())
    {
        if (orderedKickers[0] != pairCount[0].second)
        {
            returnValue.ranks[1] = orderedKickers[0];
        }
        else if (orderedKickers.size() > 1)
        {
            returnValue.ranks[1] = orderedKickers[1];
        }
    }
    return returnValue;
}

std::optional<HandValue> isFullHouse(
                            const std::vector<std::pair<int, int>>& pairCount,
                            const std::vector<int>& orderedKickers)
{
    if (pairCount.size() < 2 || pairCount[0].first != TRIPS_COUNT)
    {
        return std::nullopt;
    }
    HandValue returnValue{};
    returnValue.type = HandType::fullHouse;
    returnValue.ranks[0] = pairCount[0].second;
    if (pairCount.size() == 2)
    {
        returnValue.ranks[1] = pairCount[1].second;
    }
    else
    {
        returnValue.ranks[1] = std::max(pairCount[1].second,
                                        pairCount[2].second);
    }
    return returnValue;
}

std::optional<HandValue> isStraight(std::vector<Card>& hand)
{
    HandValue returnValue{};
    std::sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
        return a.rank < b.rank;
    });
    int straightCount = 1;
    for (auto it = hand.begin();
         std::next(it) != hand.end();
         ++it)
    {
        int nextVal = std::next(it)->rank;
        if (it->rank + 1 == nextVal)
        {
            ++straightCount;
        }
        else if (it->rank + 1 < nextVal)
        {
            straightCount = 1;
        }
        if (straightCount == STRAIGHT_LEN ||
            (straightCount == STRAIGHT_LEN - 1 &&
             nextVal == 5 &&
             hand.back().rank == MAX_RANK))
        {
            returnValue.type = HandType::straight;
            returnValue.ranks[0] = nextVal;
            return returnValue;
        }
    }
    return std::nullopt;
}

std::optional<HandValue> isTrips(
                            const std::vector<std::pair<int, int>>& pairCount,
                            const std::vector<int>& orderedKickers)
{
    if (pairCount.empty() || pairCount[0].first < TRIPS_COUNT)
    {
        return std::nullopt;
    }
    HandValue returnValue{};
    returnValue.type = HandType::trips;
    returnValue.ranks[0] = pairCount[0].second;
    returnValue.ranks[1] = orderedKickers[0];
    returnValue.ranks[2] = orderedKickers[1];
    return returnValue;
}

std::optional<HandValue> isTwoPair(
                            const std::vector<std::pair<int, int>>& pairCount,
                            const std::vector<int>& orderedKickers)
{
    if (pairCount.size() < 2 || pairCount[1].first < PAIR_COUNT)
    {
        return std::nullopt;
    }
    HandValue returnValue{};
    returnValue.type = HandType::twoPair;
    returnValue.ranks[0] = pairCount[0].second;
    returnValue.ranks[1] = pairCount[1].second;
    returnValue.ranks[2] = orderedKickers[0];
    return returnValue;
}

std::optional<HandValue> isPair(
                            const std::vector<std::pair<int, int>>& pairCount,
                            const std::vector<int>& orderedKickers)
{
    if (pairCount.empty())
    {
        return std::nullopt;
    }
    HandValue returnValue{};
    returnValue.type = HandType::pair;
    returnValue.ranks[0] = pairCount[0].second;
    for (std::size_t i = 1; i < returnValue.ranks.size(); ++i)
    {
        returnValue.ranks[i] = orderedKickers[i-1];
    }
    return returnValue;
}

HandValue evaluateHand(const std::vector<Card>& board, std::vector<Card> hand)
{
    hand.insert(hand.end(), board.begin(), board.end());
    HandValue handValue{};
    HandValue flushValue{};
    
    if (auto result = isStraightFlush(hand, flushValue))
    {
        return result.value();
    }
    std::vector<std::pair<int, int>> pairCount;
    std::vector<int> orderedKickers;
    pairTrack(hand, pairCount, orderedKickers);
    if (auto result = isQuads(pairCount, orderedKickers))
    {
        return result.value();
    }
    if (auto result = isFullHouse(pairCount, orderedKickers))
    {
        return result.value();
    }
    if (handValue.type == HandType::flush)
    {
        return flushValue;
    }
    if (auto result = isStraight(hand))
    {
        return result.value();
    }
    if (auto result = isTrips(pairCount, orderedKickers))
    {
        return result.value();
    }
    if (auto result = isTwoPair(pairCount, orderedKickers))
    {
        return result.value();
    }
    if (auto result = isPair(pairCount, orderedKickers))
    {
        return result.value();
    }
    handValue.type = HandType::highCard;
    std::copy_n(orderedKickers.begin(), 5, handValue.ranks.begin());
    return handValue;
}

std::vector<HandValue> compareHands(std::vector<HandValue> hands)
{
    std::vector<HandValue> candidates{};
    for (std::size_t i{}; i < hands.size(); ++i)
    {
        hands[i].index = static_cast<int>(i);
        if (candidates.empty() || (candidates.front().type < hands[i].type))
        {
            candidates.clear();
            candidates.push_back(hands[i]);
        }
        else if (candidates[0].type == hands[i].type)
        {
            for (std::size_t j{}; j < hands[i].ranks.size(); ++j)
            {
                if (candidates[0].ranks[j] < hands[i].ranks[j])
                {
                    candidates.clear();
                    candidates.push_back(hands[i]);
                    break;
                }
                else if (candidates[0].ranks[j] > hands[i].ranks[j])
                {
                    break;
                }
                else if (j == 4)
                {
                    candidates.push_back(hands[i]);
                }
            }
        }
    }
    return candidates;
}

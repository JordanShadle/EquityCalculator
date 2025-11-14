#pragma once
#include <vector>
#include <string>
#include "deck.h"

char suitToChar(Suit s);
char rankToChar(int rank);
Suit charToSuit(char suit);
std::string rankToType(int rank);
void printCards(const std::vector<Card>& cards);

//
// Created by orion on 9/23/26.
//

#include "Card_Identifier.h"

#define OFFSET 13
#define NUMBER_OF_SUIT 4
static const std::unordered_map<std::string, pokerSymbol> lookupTable =
{
    {"1", ONE},
    {"2", TWO},
    {"3", THREE},
    {"4", FOUR},
    {"5", FIVE},
    {"6", SIX},
    {"7", SEVEN},
    {"8", EIGHT},
    {"9", NINE},
    {"10", TEN},
    {"J", JACK},
    {"Q", QUEEN},
    {"K", KING},
    {"diamond", DIAMOND},
    {"heart", HEART},
    {"spade", SPADE},
    {"clover", CLOVER}
};

bool Card_Identifier::processData(const DarkHelp::PredictionResults& dataVector)
{
    int timeOccurred_Shape[NUMBER_OF_SUIT] = {0, 0, 0, 0};
    pokerSymbol finalNumber = EMPTY;
    int numOfChange_finalNumber = 0;
    for (const auto& result : dataVector)
    {
        pokerSymbol currentVectorValue = lookupTable.at(result.name);
        if (currentVectorValue > OFFSET)
        {
            timeOccurred_Shape[currentVectorValue - OFFSET]++;
        } else if (finalNumber != currentVectorValue)
        {
            finalNumber = currentVectorValue;
            numOfChange_finalNumber++;
        }
    }

    Card resultCard = identifier(timeOccurred_Shape, finalNumber, numOfChange_finalNumber);
    if (resultCard.getCardNumber() == EMPTY)
        return false;

    cardDetectedHistory.push_back(resultCard);
    return true;

}

Card_Identifier::Card Card_Identifier::identifier(const int timeOccurred_Shape[], pokerSymbol finalNumber, int numOfChange_finalNumber)
{
    // one time: EMPTY -> final number
    if (numOfChange_finalNumber != 1)
        return Card{};

    pokerSymbol mostOccurredSuit = EMPTY;
    int numAppearance = 0;
    for (int i = 1; i < NUMBER_OF_SUIT; i++)
    {
        if (timeOccurred_Shape[i] > numAppearance)
        {
            numAppearance = timeOccurred_Shape[i];
            mostOccurredSuit = static_cast<pokerSymbol>(i + OFFSET);
        }
    }
    // Make sure the model detects at least one suit
    if (mostOccurredSuit == EMPTY)
        return Card{};

    return Card{mostOccurredSuit, finalNumber};
}

std::vector<Card_Identifier::Card>::const_iterator Card_Identifier::getCardDetectedHistory()
{
    return cardDetectedHistory.begin();
}

Card_Identifier::Card Card_Identifier::getLastDetectedCard()
{
    if (cardDetectedHistory.empty())
        throw std::out_of_range("no card in history");
    return cardDetectedHistory.back();
}

Card_Identifier::Card Card_Identifier::getSecondLastDetectedCard()
{
    if (cardDetectedHistory.size() < 2)
        throw std::out_of_range("there are less than 2 cards in history");
    return *std::prev(cardDetectedHistory.end());
}

void Card_Identifier::resetCardDetectedHistory()
{
    cardDetectedHistory.clear();
}


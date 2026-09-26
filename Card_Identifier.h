//
// Created by orion on 9/23/26.
//
#ifndef CARD_IDENTIFIER_H
#define CARD_IDENTIFIER_H

#include <string>
#include <memory>
#include "DarkHelpNN.hpp"

//#TODO Prediction has to be made outside of the class
enum pokerSymbol {EMPTY, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, DIAMOND, HEART, SPADE, CLOVER};

class Card_Identifier
{
    class Card
    {
    public:
        Card(): cardSuit(EMPTY), cardNumber(EMPTY){}
        Card(pokerSymbol suit, pokerSymbol number): cardSuit(suit), cardNumber(number){}


        [[nodiscard]] pokerSymbol getCardSuit() const { return cardSuit;}
        [[nodiscard]] pokerSymbol getCardNumber() const {return cardNumber;}
        void setCardSuit(pokerSymbol newSuit) {cardSuit = newSuit;}
        void setCardNumber(pokerSymbol newNumber) {cardNumber = newNumber;}
    private:
        pokerSymbol cardSuit;
        pokerSymbol cardNumber;
    };
public:
    Card_Identifier() = default;
    /* Purpose: Process the detected data and turn it into object only create object when it doesn't have to guess
     * Input:   1. PredictionResults Vector
     *          2. Number of cards you want to detect
     * Output:  True when it received enough data to make a decision
     */
    std::vector<Card> getCardDetectedHistory();
    bool processData(const DarkHelp::PredictionResults&);

    std::vector<Card> cardDetectedHistory;
private:
    Card identifier(const int[], pokerSymbol, int);




};


#endif//CARD_IDENTIFIER_H

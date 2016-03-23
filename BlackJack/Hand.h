#ifndef HAND_H
#define HAND_H

#include <vector>
#include <iostream>
#include "Card.h"

using std::vector;

class Hand {
public:
    Hand(){}
    ~Hand(){cards.clear();}

    int getHandValue() const {
        int value =0;
        //bool Has ace
        for (int i=0;i<cards.size();i++) {
            value += cards[i].getValue();
        }
        int nAces = getAceCount();
        if (nAces > 1) {
            value-=(nAces-1)*10;
        }
        if (value > 21 && nAces){
            value -= 10;
        }
        return value;
    }
    void addCard(const Card &card) {
        cards.push_back(card);
    }
    bool bust() const {
        return getHandValue() > 21;
    }
    Card firstCard() { // only for Dealer
        return cards[0];
    }
    int getAceCount() const {
        int cnt = 0;
        for(int i=0;i<cards.size();i++) {
            if (cards[i].value == 'A') {
                cnt++;
            }
        }
        return cnt;
    }
    bool isSoft() const {
        return getAceCount() == 1 && cards.size() == 2;
    }
    bool isBlackJack() const { //splitting may fuck up
        if (cards.size() == 2) {
            return (getHandValue() == 21);
        }
    }
    void clear() {
        this->cards.clear();
    }
    friend std::ostream& operator<<(std::ostream &os, const Hand &hand) {
        for(int i=0;i<hand.cards.size();i++) {
            os << hand.cards[i] << " ";
        }
        return os;
    }
private:
    
    vector<Card> cards;
};


#endif
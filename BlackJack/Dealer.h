
#ifndef DEALER_H
#define DEALER_H

#include "Player.h"

class Dealer: public Player {
public:
    Dealer() {
    }
    virtual ~Dealer() {

    }
	virtual void play(Deck &deck, const Card &upCard) override {
		//Hit Until 17 (hit on soft 17)
		while (myHand.getHandValue() < 17 || (myHand.getHandValue() == 17 && myHand.getAceCount()>0)) {
			myHand.addCard(deck.deal());
		}
	}
	virtual void tie() {}
    Card getUpCard() {
        return myHand.firstCard();
    }
private:

};
#endif
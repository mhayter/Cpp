#ifndef SIMPLE_PLAYER_H
#define SIMPLE_PLAYER_H

#include "Player.h" 

class SimplePlayer : public Player {
public:
	SimplePlayer() {}
	virtual ~SimplePlayer() {}
	virtual void play(Deck &deck) override {
		//Hit
        while (myHand.getHandValue()<17) {
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
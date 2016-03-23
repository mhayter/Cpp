
#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "Deck.h"

class Player {
public:
    Player(): money(1000), wager(STANDARD_WAGER) {
    }
    virtual ~Player() {}

	virtual void play(Deck &deck, const Card& upCard)=0;
	void lose() {
        money-=wager;
    }
	void win(bool blackjackWin=false) {
        money+= wager+blackjackWin*wager*0.5;
        wager = STANDARD_WAGER;
    }
	virtual void tie() {}

	bool hasBlackJack() {
		return myHand.isBlackJack();
	}
    Hand myHand;

	double money;
	int wager;
	const static int STANDARD_WAGER = 25;
};
#endif
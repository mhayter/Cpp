
#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "Deck.h"

class Player {
public:
    Player(): money(1000), wager(25) {
    }
    virtual ~Player() {}

	virtual void play(Deck &deck)=0;
	void lose() {
        money-=wager;
    }
	void win() {
        money+=wager;
    }
	virtual void tie() {}

    Hand myHand;

	int money;
	int wager;
};
#endif
#ifndef ADVANCED_PLAYER_H
#define ADVANCED_PLAYER_H

#include "Player.h" 
#include "Dealer.h"

class AdvancedPlayer : public Player {
public:
	AdvancedPlayer() {}
	virtual ~AdvancedPlayer() {}
	virtual void play(Deck &deck, const Card &upCard) override {
		//100% coverage on double down
		//Hit
		//if dealer upcard is 2-6 && I have 12-16 hard stand
		if (upCard.getValue() >=2 && upCard.getValue() <= 6) {
			if (myHand.getHandValue() >= 12 && myHand.getHandValue() <=16) {//stand
				return;
			}
		}
		//add double down logic (only hard)
		if (	 myHand.getHandValue() == 11 ||
				(myHand.getHandValue() == 10 && upCard.getValue() <= 9) ||
				(myHand.getHandValue() == 9  && upCard.getValue() >=3 && upCard.getValue() <=6) ) {
			doubleDown(deck);
		} else {
			//soft doubleDown scenarios
			//seems to be working incorrectly
			if (myHand.isSoft()) {
				if (upCard.getValue()>=5 && upCard.getValue() <=6 && 
					myHand.getHandValue()>=13 && myHand.getHandValue() <=18) {
					doubleDown(deck);
				}else if (upCard.getValue() == 4 && 
					myHand.getHandValue()>=15 && myHand.getHandValue() <=18) {
					doubleDown(deck);
				} else if(upCard.getValue() == 3 &&
					myHand.getHandValue()>=17 && myHand.getHandValue() <=18){
					doubleDown(deck);
				} else if (upCard.getValue() == 2 &&
					myHand.getHandValue() == 18) {
					doubleDown(deck);
				} else if (upCard.getValue() == 6 &&
					myHand.getHandValue() == 19) {
					doubleDown(deck);
				}
			} else { // hitting11
		        while (myHand.getHandValue()<17) {
		            myHand.addCard(deck.deal());
		        }
		    }
		} 
	}
	void doubleDown(Deck &deck) {
		myHand.addCard(deck.deal());
		wager = 2*Player::STANDARD_WAGER;
	}
	virtual void tie() {}
	
private:
};

#endif
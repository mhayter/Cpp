#include <iostream>
#include <vector>
using namespace std;

class Card {
public:
	Card (char value,char suit) {
		this->value = value;
		this->suit = suit;
	}
private:
	char value;
	char suit;
}

class Deck {
public: 
    Deck(){}
    Deck(int num) {
        deck = new [DECK_SIZE * num];
        for(int i=0;i<DECK_SIZE*num;i++) {
        	deck[i] = Card(VALUES[i%13],SUITS[i%4]);
        }
        shuffle();
    }
    void shuffle() {
        random_shuffle(deck,deck+DECK_SIZE*num);
    }
private:
    static const int DECK_SIZE = 52;
    static const string VALUES = "23456789TJQKA";
    static const string SUITS = "CSDH";
    Card *deck;
};

class Player {
public:
	virtual void play(Card dealerUpCard)=0;
	virtual void lose()=0;
	virtual void win()=0;
	virtual void tie()=0;
	virtual int getBust()=0;
	vector<Card>myHand;
	int money;
	int wager;
	bool bust;
};

class Dealer:public Player{
public:
	virtual void play() {
		//Hit Until 17 (hit on soft 17)
		while (!bust) {
			int value = getHandValue();
			if (value <17) 
				hit();
			else if (value > 21) {
				bust=true;
			} else break;
		}
	}
	virtual void win() {
		money+=wager;
	}
	virtual void lose() {
		money-=wager;
	}
	virtual void tie() {}
	virtual int getBust{}
private:
	int getValueHand() {
		int value =0;
		//bool Has ace
		for (int i=0;i<myHand.size();i++) {
			value += getValue(myHand[i])
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
};
class SimplePlayer : public Player {
public:
	virtual void play() {
		if (getdeal)
	}
	virtual void win() {
		money+=wager;
	}
	virtual void lose() {
		money-=wager;
	}
	virtual void tie() {}
	virtual int getBust{}
private:
}

class BlackJack{
public:
    BlackJack(int nDecks=4, int nPlayers=2) {
        deck = new Deck(nDecks);
        players.push_back(new Dealer());
        for (int i=0;i+1<nPlayers;i++)
        	players.push_back(new SimplePlayer());
    }
    void play() {
    	//deal cards 
    	dealHands();
    	
    	//check for options
    	offerInitialOptions();
    	
    	//while I don't bust or stand ask for hit
    	for (int i=1;i<players.size();i++) {
    		(players[i])->play();
    	}
    	bool atLeastOneNotBusted = getOneNotBusted();
    	
    	if (atLeastOneNotBusted) {
    		players[0]->play();
    	} else { // dealer win
    		for (int i=1;i<players.size();i++) {
    			players[i]->lose();
    		}
    	}
    	
    	//if I didn't bust and he did I win
    	for (int i=1;i<players.size();i++) {
    		if (!players[i]->getBust() && players[0]->getBust()) {//player wins
    			players[i]->win();
    		} else if (players[i]->getTotal() > players[0]->getTotal()) { //player wins
    			players[i]->win();
    		} else if (players[i]->getTotal() == players[0]->getTotal()) {
    			players[i]->tie();
    		} else { //I lose
    			players[i]->lose();
    		}
    	}
    }
    bool getOneNotBusted() {
    	for (int i=1;i<players.size();i++) {
	    	if (!(players[i])->getBust()) {
	    		return true;
	    	}
    	}
    	return false;
    }
    void dealHands() {
    	for(int i=0;i<players.size();i++) {
    		players[i]->myHand.push_back(deck.deal());
    		players[i]->myHand.push_back(deck.deal());
    	}
    }
private:
    Deck *deck;
    vector<Player*>players;
};

int main() {
   
   BlackJack bj;
   //bj.play();
   return 0;
}


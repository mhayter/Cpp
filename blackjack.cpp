#include <iostream>
#include <vector>
using namespace std;

#include "Hand.h"
#include "Card.h"
#include "Deck.h"

#include "Dealer.h"
#include "SimplePlayer.h"




class BlackJack{
public:
    BlackJack(int nDecks=4, int nPlayers=2) {
        deck = new Deck(nDecks);
        player = new SimplePlayer();
        dealer = new Dealer();
        start();
    }
    void start() {
        while (true) {
        	//deal cards 
        	dealHands();

        	//while I don't bust or stand ask for hit
        	player->play();
        	
        	//if I didn't bust and he did I win
        	if (player->bust()) {//bust
                dealer->win();
                player->lose();
            } else {
                dealer->play();

                if (dealer->bust()) {// bust player wins
                    player->win();
                    dealer->lose();
                } else if (player->getHandValue() > dealer->getHandValue()) {
                    player->win();
                    dealer->lose();
                } else if (player->getHandValue() < dealer->getHandValue()) {
                    dealer->win();
                    player->lose();
                } else { // tie
                    dealer->tie();
                    player->tie();
                }
            }
        }
    }
    void dealHands() {
    	dealer->addCard(deck.deal());
        dealer->addCard(deck.deal());

        player->addCard(deck.deal());
        player->addCard(deck.deal());
    }
private:
    Dealer *dealer;
    Deck *deck;
    Player *player;
};

int main() {
   
   BlackJack bj;
   //bj.play();
   return 0;
}


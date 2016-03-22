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
            cout << "New Hand " << player->money << endl;
            int z; cin >> z;
            if (player->money <= 0) {
                cout << "YOu Lost" << endl;
            }
            clearHands();
        	//deal cards 
        	dealHands();

        	//while I don't bust or stand ask for hit
        	player->play(*deck);
        	
            cout << player->myHand << endl;

        	//if I didn't bust and he did I win
        	if (player->myHand.bust()) {//bust
                cout << "Player bust" << endl;
                dealer->win();
                player->lose();

            } else {
                dealer->play(*deck);

                cout << dealer->myHand << endl;

                if (dealer->myHand.bust()) {// bust player wins
                    cout << "Dealer Bust" << endl;
                    player->win();
                    dealer->lose();
                } else if (player->myHand.getHandValue() > dealer->myHand.getHandValue()) {
                    cout << "Player Win!" << endl;
                    player->win();
                    dealer->lose();
                } else if (player->myHand.getHandValue() < dealer->myHand.getHandValue()) {
                    cout << "Player Lose :(" << endl;
                    dealer->win();
                    player->lose();
                } else { // tie
                    cout << "Push ---" << endl;
                    dealer->tie();
                    player->tie();
                }
            }
        }
    }
    void clearHands() {
        dealer->myHand.clear();
        player->myHand.clear();
    }
    void dealHands() {

    	dealer->myHand.addCard(deck->deal());
        dealer->myHand.addCard(deck->deal());

        player->myHand.addCard(deck->deal());
        player->myHand.addCard(deck->deal());
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


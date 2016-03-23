#include <iostream>
#include <vector>
using namespace std;

#include "Hand.h"
#include "Card.h"
#include "Deck.h"

#include "Dealer.h"
#include "SimplePlayer.h"
#include "AdvancedPlayer.h"



class BlackJack{
public:
    BlackJack(int nDecks=4, int nPlayers=2) : 
        deck(nDecks)
    {
        player = new AdvancedPlayer();
        dealer = new Dealer();
    }
    ~BlackJack() {
        delete player;
        delete dealer;
    }
    double getResult(int nBets = 100) {
        while (nBets-- > 0 && player->money > 0) {
            //cout << "New Hand " << player->money << endl;
            //int z; cin >> z;
            if (player->money <= 0) {
                cout << "You Lost" << endl;
                break;
            }

            reset();
            clearHands();
        	//deal cards 
        	dealHands();
            if (player->hasBlackJack() && !dealer->hasBlackJack()) {//pay player 1.5x
                player->win(true);
                //cerr << "True BJ!!!" << endl;
                dealer->lose();
            }
            else if (player->hasBlackJack() && dealer->hasBlackJack()) {//push
                player->tie();
                dealer->tie();
            }
            else if (dealer->hasBlackJack() && !player->hasBlackJack()) { // dealer wins
                dealer->win();
                player->lose();
                
            } else {
        	   //while I don't bust or stand ask for hit
        	   player->play(deck, dealer->getUpCard());
            
                //cout << player->myHand << endl;

            	//if I didn't bust and he did I win
            	if (player->myHand.bust()) {//bust
                    //cout << "Player bust" << endl;
                    dealer->win();
                    player->lose();

                } else {
                    dealer->play(deck, dealer->getUpCard()); // doesn't need upCard (eliminate?)

                    //cout << dealer->myHand << endl;

                    if (dealer->myHand.bust()) {// bust player wins
                        //cout << "Dealer Bust" << endl;
                        player->win();
                        dealer->lose();
                    } else if (player->myHand.getHandValue() > dealer->myHand.getHandValue()) {
                        //cout << "Player Win!" << endl;
                        player->win();
                        dealer->lose();
                    } else if (player->myHand.getHandValue() < dealer->myHand.getHandValue()) {
                        //cout << "Player Lose :(" << endl;
                        dealer->win();
                        player->lose();
                    } else { // tie
                        //cout << "Push ---" << endl;
                        dealer->tie();
                        player->tie();
                    }
                }
            }
        }
        return player->money;
    }
    void reset() {
        deck = Deck(4);
        clearHands();
    }
    void clearHands() {
        dealer->myHand.clear();
        player->myHand.clear();
    }
    void dealHands() {

    	dealer->myHand.addCard(deck.deal());
        dealer->myHand.addCard(deck.deal());

        player->myHand.addCard(deck.deal());
        player->myHand.addCard(deck.deal());
    }
private:
    Dealer *dealer;
    Deck deck;
    Player *player;
};

int main(int argc, char *argv[]) {
   int nSims = 100000;

   int nBets = 10; 

   vector<double> results;

   for (int i=0;i<nSims;i++) {
        BlackJack bj;
        results.push_back(bj.getResult(nBets));
        //cerr << (1000-results[i])/(25*nBets) << endl;
        //cerr << "******* Result " << results[i] << endl;
   }

   //total wagered for eack bet *nBets
   cerr << "Overall \n";
   double tot = 0;
   for(int i=0;i<nSims;i++) {
        tot+=results[i];
   }
   cerr << (tot/nSims-1000)/(nBets) << " " << (tot/nSims-1000) << " " << nBets << endl;
   cerr << (tot/nSims-1000)/(nBets*25) << endl;
   //bj.play();
   return 0;
}


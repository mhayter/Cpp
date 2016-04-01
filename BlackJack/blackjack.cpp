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
    double getResult(int nBets = 100, int wager=25) {
        while (nBets-- > 0 && player->money > 0) {
            //cout << "New Hand " << player->money << endl;
            //int z; cin >> z;
            if (player->money <= 0) {
                cout << "You Lost" << endl;
                break;
            }
            reset();
        	//deal cards 
            //cout << "Before dealHands" << endl;
        	dealHands(wager);
            //cout << "dealHands" << endl;
            // for each of the hands evaluate
            player->evaluateHands(dealer,deck);
            
            
        }
        return player->money;
    }
    
private:
    void reset() {
        deck = Deck(4);
        dealer->clear();
        player->clear();
    }
    void dealHands(int wager) {
        Hand dealerHand(wager); // dealer isn't a player truly
        dealerHand.addCard(deck.deal());
        dealerHand.addCard(deck.deal());

        dealer->addHand(dealerHand);

        Hand playerHand (wager);
        playerHand.addCard(deck.deal());
        playerHand.addCard(deck.deal());

        player->addHand(playerHand);
    }
    
    Dealer *dealer;
    Deck deck;
    Player *player;
};

int main(int argc, char *argv[]) {
   int nSims = 10;

   int nBets = 10; 

   if (argc == 2) {
        nSims = atoi(argv[1]);
   }
   vector<double> results;

   for (int i=0;i<nSims;i++) {
        BlackJack bj;
        results.push_back(bj.getResult(nBets));
        cerr << (results[i]-1000)/(25*nBets) << endl;
        cerr << "******* Result " << results[i] << endl;
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


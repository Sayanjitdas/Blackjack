// Blackjack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "utils.h"
using namespace std;

const int CARD_TYPE_NUMBER = 4;
const int CARD_FACE_NUMBER = 13;
const int SCORE_LIMIT = 21;


enum CardType {
    HEARTS = 0,
    DIAMONDS,
    SPADES,
    CLUBS
};

enum CardFaces {
    NOVALUE = 0,
    ACE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JOKER = 11,
    QUEEN = 12,
    KING = 13
};


struct Card {
    int cardType; 
    int cardFace;
};

struct Dealer {
    Card* cardArray = new Card[50];
    int sum = 0;
    int index = 0;
    int showinitialCard = false;
};

struct Player {
    Card *cardArray = new Card[50];
    int sum = 0;
    int index = 0;
};

int FaceValueAssignment(int cardFaceNumber) {

    switch (cardFaceNumber)
    {
    case ACE: {
        char validInputs[] = { 's','h' };
        char input = GetCharInput("You have an ACE\nPress 's' for soft hand or 'h' for hard hand",validInputs,2);
        
        if (input == 's') {
            return 11;
        }
        else {
            return 1;
        }
    }
    case JOKER:
        return 10;
    case QUEEN:
        return 10;
    case KING:
        return 10;
    default:
        return cardFaceNumber;
    }
}


Card DrawCard(int cardDeck[CARD_TYPE_NUMBER][CARD_FACE_NUMBER]) {

    //card Category 
    int cardCatNumber;
    int cardFaceNumber;
    bool repetition = false;
    Card card;

    //check for repetition
    do {
        cardCatNumber = RandomNumber(0, 3);
        cardFaceNumber = RandomNumber(0, 12);
        //cout << cardDeck[cardCatNumber][cardFaceNumber] << endl;
        if (cardDeck[cardCatNumber][cardFaceNumber] == NOVALUE) {
            repetition = true;
        }
        else {
            repetition = false;
        }
        

    } while(repetition);

    //asigning card type
    card.cardType = cardCatNumber;

    //assigning card face
    card.cardFace = cardFaceNumber;

    cardDeck[cardCatNumber][cardFaceNumber] = NOVALUE;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cout << cardDeck[i][j] << " ";
        }
        cout << endl;
    }

    return card;
}


void DisplayNameFormat(char* cardType,char* cardFace,int card_type, int card_face) {

    switch (card_type)
    {
    case HEARTS:
        strcpy_s(cardType, 10,"Hearts");
        break;
    case DIAMONDS:
        strcpy_s(cardType, 10, "Diamonds");
        break;
    case SPADES:
        strcpy_s(cardType, 10, "Spades");
        break;
    case CLUBS:
        strcpy_s(cardType, 10, "Clubs");
        break;
    default:
        break;
    }

    switch (card_face)
    {
    case ACE:
        strcpy_s(cardFace, 10, "Ace");
        break;
    case TWO:
        strcpy_s(cardFace, 10, "Two");
        break;
    case THREE:
        strcpy_s(cardFace, 10, "Three");
    case FOUR:
        strcpy_s(cardFace, 10, "Four");
        break;
    case FIVE:
        strcpy_s(cardFace, 10, "Five");
        break;
    case SIX:
        strcpy_s(cardFace, 10, "Six");
        break;
    case SEVEN:
        strcpy_s(cardFace, 10, "Seven");
        break;
    case EIGHT:
        strcpy_s(cardFace, 10, "Eight");
        break;
    case NINE:
        strcpy_s(cardFace, 10, "Nine");
        break;
    case TEN:
        strcpy_s(cardFace, 10, "Ten");
        break;
    case JOKER:
        strcpy_s(cardFace, 10, "Joker");
        break;
    case QUEEN:
        strcpy_s(cardFace, 10, "Queen");
        break;
    case KING:
        strcpy_s(cardFace, 10, "King");
        break;
    default:
        break;
    }

    
}


void DisplayPlayerHands(Player* player) {

    cout << "PLAYER: " << endl;
    cout << "\tHand: " << endl;
    cout << "\t---------------------" << endl;
    for (int i = 0; i < player->index; i++) {
        char cardType[10];
        char cardFace[10];
        DisplayNameFormat(cardType,cardFace,player->cardArray[i].cardType, player->cardArray[i].cardFace);
        cout << "\t" << cardFace << " of " << cardType << endl;
    }
    cout << "\t---------------------" << endl;

}


void DisplayDealerHands(Dealer* dealer) {

    if (dealer->showinitialCard) {
        cout << "DEALER: " << endl;
        cout << "\tHand: " << endl;
        cout << "\t---------------------" << endl;
        for (int i = 0; i < dealer->index; i++) {
            char cardType[10];
            char cardFace[10];
            DisplayNameFormat(cardType,cardFace,dealer->cardArray[i].cardType, dealer->cardArray[i].cardFace);
            cout << "\t" << cardFace << " of " << cardType << endl;
        }
        cout << "\t---------------------" << endl;

    }
    else {
        cout << "DEALER: " << endl;
        cout << "\tHand: " << endl;
        cout << "\t---------------------" << endl;
        cout << "\t[***]" << endl;
        for (int i = 1; i < dealer->index; i++) {
            char cardType[10];
            char cardFace[10];
            DisplayNameFormat(cardType,cardFace,dealer->cardArray[i].cardType, dealer->cardArray[i].cardFace);
            cout << "\t" << cardFace << " of " << cardType << endl;
        }
        cout << "\t---------------------" << endl;

    }
}


void CalculateFaceValueDealer(Dealer* dealer) {
    dealer->sum = 0;
    for (int i = 0; i < dealer->index; i++) {
        dealer->sum += FaceValueAssignment(dealer->cardArray[i].cardFace);
    }
}

void CalculateFaceValue(Player* player) {
    player->sum = 0;
    for (int i=0; i < player->index; i++) {
        player->sum += FaceValueAssignment(player->cardArray[i].cardFace);
    }

}


void CheckTie(int cardDeck[CARD_TYPE_NUMBER][CARD_FACE_NUMBER], Player* player, Dealer* dealer) {

    if (player->sum == dealer->sum) {
        cout << "IT IS A TIE !!" << endl;
        cout << "Draw card for both dealer and player" << endl;
        dealer->cardArray[dealer->index] = DrawCard(cardDeck);
        dealer->index++;
    }
}


void HitorTake(int cardDeck[CARD_TYPE_NUMBER][CARD_FACE_NUMBER],Player* player,Dealer* dealer) {

    CalculateFaceValue(player);
    if (player->sum == 21) return; //blackjack

    char validInputs[] = { 'h','r' };
    char input = GetCharInput("Press 'h' to hit or 'r' to reveal : ", validInputs,2);

    switch (input)
    {
    case 'h':
        cout << "Will take a card" << endl;
        player->cardArray[player->index] = DrawCard(cardDeck);
        player->index++;
        CalculateFaceValue(player);
        DisplayPlayerHands(player);
        break;
    case 'r':
        cout << "will reveal the hand of dealer" << endl;
        dealer->showinitialCard = true;
        DisplayDealerHands(dealer);
        CalculateFaceValueDealer(dealer);
        CheckTie(cardDeck, player, dealer);
        break;
    default:
        break;
    }

}


bool GameNotOver(Player* player, Dealer* dealer, int cardDeck[CARD_TYPE_NUMBER][CARD_FACE_NUMBER]) {
    
  
    /*
    * Game over conditions
    *   -> When it is a blackjack for player/dealer
    *   -> When player score is greater than dealer and vice versa
    *   -> when player score exceeds SCORE_LIMIT bust 
    *   -> When dealer score exceeds SCORE_LIMIT bust
    */
    bool gameNotOver = true;
    cout << player->sum << endl;
    cout << dealer->sum << endl;
    //cout << "BEFORE: " << gameNotOver << endl;
   
    if (player->sum == 21) {
        cout << "Player wins with blackjack!!!!" << endl;
        gameNotOver = false;
    } 
    else if (dealer->sum == 21 && dealer->showinitialCard == true) {
        cout << "Dealer Wins with Blackjack!!!" << endl;
        gameNotOver = false;
    }
    else if (player->sum < SCORE_LIMIT && dealer->sum < SCORE_LIMIT && dealer->showinitialCard == true) {
        cout << "Coming Here.." << endl;
        if (player->sum > dealer->sum) {
            cout << "Player wins!!" << endl;
            gameNotOver = false;
        }
        else {
            cout << "Dealer wins!!" << endl;
            gameNotOver = false;
        }
    }
    

    //-> when player score exceeds SCORE_LIMIT
    if (player->sum > SCORE_LIMIT || dealer->sum > SCORE_LIMIT) {
        cout << "Dealer Wins!!" << endl;
        gameNotOver = false;
    }
    else if (dealer->sum > SCORE_LIMIT) {
        cout << "Player Wins!!" << endl;
        gameNotOver = false;
    };

    /*cout << "AFTER: " << gameNotOver << endl;*/

    return gameNotOver;
}



//playGame
//--------------
void PlayGame(Player* player,Dealer* dealer,int cardDeck[CARD_TYPE_NUMBER][CARD_FACE_NUMBER]) {

    int initSwap = 0;
    //initial hands
    for (int i = 0; i < 4; i++) {
        
        if (initSwap == 0) {
            //dealer
            Card card = DrawCard(cardDeck);
            dealer->cardArray[dealer->index] = card;
            //dealer->sum += card.faceValue;
            dealer->index < 50 ? dealer->index++ : dealer->index;
            initSwap = 1;
        }
        else {
            //Player
            Card card = DrawCard(cardDeck);
            player->cardArray[player->index] = card;
            //player->sum += card.faceValue;
            player->index < 50 ? player->index++ : player->index;
            initSwap = 0;
        }
    }

    do {
        clearScreen();
        DisplayDealerHands(dealer);
        DisplayPlayerHands(player);
        HitorTake(cardDeck, player, dealer);


    } while (GameNotOver(player,dealer,cardDeck));
   
}



//wantToPlayAgain
//-------------------
bool WantToPlayAgain() {

    char validInput[] = { 'y','n' };
    char input = GetCharInput("Want to play Again? y/n", validInput, 2);
    cout << input << endl;
    if (tolower(input) == 'y') {
        return true;
    }
    else {
        return false;
    }
}




int main()
{

    do {
        //Deck of Cards
        //------------------
        int(*cardPtr)[13] = new int[CARD_TYPE_NUMBER][CARD_FACE_NUMBER]{
                         {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JOKER,QUEEN,KING},
                         {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JOKER,QUEEN,KING},
                         {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JOKER,QUEEN,KING},
                         {ACE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JOKER,QUEEN,KING}
        };

        Player player;
        Dealer dealer;
        Player *playerPtr = &player;
        Dealer *dealerPtr = &dealer;


        //call PlayGame
        //--------------
        PlayGame(playerPtr, dealerPtr, cardPtr);

        delete[] playerPtr->cardArray;
        delete[] dealerPtr->cardArray;
        delete[] cardPtr;

    } while (WantToPlayAgain());





}


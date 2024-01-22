#include "DateValidator.cpp"
#include "CreditCard.cpp"
#include <ctime>
#include "NumberValidator.cpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class Node {
public:
    CreditCard* data;
    Node* next;

    Node (CreditCard* card) 
    {
        this->data = card;
        this->next = NULL; 
    }
};

class LinkedList {
public:
    Node* head;
    
    LinkedList() {
        head = NULL;
    }

    void addCard (CreditCard* card) {
        Node* newNode = new Node(card);

        if (head == NULL) {
            head = newNode;
        }else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void printCards() {
        Node* temp = head;
        
        if (head == NULL) { 
            cout << "List empty" << endl;
            return;} 
  
        while (temp != NULL) { 
            temp->data->printCard(); 
            temp = temp->next; 
        } 
    }
};

bool checkCVV(int cnum) {
    string updatedCVV = to_string(cnum);
    if (updatedCVV.length() != 3) {
        return false;
    }else 
        return true;
}

vector<unique_ptr<CreditCard>> cardFactory(){
    ifstream myfile; 
    myfile.open("CardData.csv");

    string currLine;
    int cardNum[16];

    vector<unique_ptr<CreditCard>> cardList;

    if(myfile.is_open()){
        while ( myfile ) {
            getline(myfile, currLine);
            stringstream stream(currLine);

            string cvvStr;
            string expireMonthStr; 
            string expireYearStr;
            
            getline(stream, cvvStr, ',');
            getline(stream, expireMonthStr, ',');
            getline(stream, expireYearStr, ',');

            int cvv = stoi(cvvStr);
            int expireMonth = stoi(expireMonthStr);
            int expireYear = stoi(expireYearStr);

            for (int i = 0; i < 16; ++i) {
                string numStr;
                getline(stream, numStr, ',');
                cardNum[i] = stoi(numStr);
            }
            CreditCard newCard(cvv, expireMonth, expireYear, cardNum);
            cardList.push_back(make_unique<CreditCard>(newCard));
        }
    }
    myfile.close();
    return cardList;
}

int main() {
    vector<unique_ptr<CreditCard>> cardList = cardFactory();

    LinkedList validCards;
    LinkedList invalidCards;

    for (int i = 0; i < cardList.size(); ++i) {
        unique_ptr<CreditCard>& cardPtr = cardList[i];
        CreditCard& card = *cardPtr; 

        string strNum = card.getCardNumber();
        int cardNumber[16];

        for (int i = 0; i < 16; ++i) {
            cardNumber[i] = strNum[i] - '0';
        }

        NumberValidator checkNum(cardNumber);
        bool validNum = checkNum.updateArray(cardNumber);

        if (validNum == 1) {

            int cvv = card.getCVV();
            bool validCVV = checkCVV(cvv);

            if (validCVV == 1) {

                int month = card.getExpirationMonth();
                int year = card.getExpirationYear();

                DateValidator verifyDate(month, year);
                bool dateResult = verifyDate.checkDate();

                if (dateResult == 1) {
                    validCards.addCard(&card);
                } else {
                    invalidCards.addCard(&card);
                }
            } else {
                invalidCards.addCard(&card);
            }
        } else {
            invalidCards.addCard(&card);
        }
    }

    cout << "VALID CREDIT CARDS:" << endl;
    validCards.printCards();

    cout << endl;

    cout << "INVALID CREDIT CARDS:" << endl;
    invalidCards.printCards();

    return 0;
}

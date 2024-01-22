#include <iostream>
#include <string>
#include <array>
using namespace std;

class CreditCard{
public: 
    int cvv;
    int expireMonth;
    int expireYear;
    int cardNumber[16];

    CreditCard() {
        cvv = 000;
        expireMonth = 0;
        expireYear = 0000;
    }
        
    CreditCard(int cv, int em, int ey, int* num){
        cvv = cv;
        expireMonth = em;
        expireYear = ey;
        for (int i = 0; i < 16; ++i) {
            cardNumber[i] = num[i];
        }
    }

    int getExpirationMonth(){
        return expireMonth;
    }

    int getExpirationYear(){
        return expireYear;
    }

    int getCVV(){
        return cvv;
    }

    string getCardNumber(){
        string number;
        for (int i = 0; i < 16; ++i) {
            number += to_string(cardNumber[i]);
        }
        return number;
    }

    int printCard() {
        cout << "Card Number: " << getCardNumber() <<", " << "Expiration Date: " 
        << expireMonth << "/" << expireYear << ", CVV: " << cvv << endl;
        return 0;
    }
};

#include<iostream>
#include <numeric>
#include <array>  
using namespace std;
 
class NumberValidator
{   
    public:    
        int cardNumber[16];

        // Constructor (initialize member variables) STEP 1
        NumberValidator(int* num){
            for (int i = 0; i < 16; ++i) {
            cardNumber[i] = num[i];
            }
        }

        bool checkValidity(int sum) { //STEP 5
            int result = sum%10;
            if(result == 0){
                return true;
            } else
                return false; 
        }

        bool addDigits(int*cardNum) { //STEP 4
            for (int i = 0; i < 16; ++i) {
                cardNumber[i] = cardNum[i];
            }
            int n = 16, sum = 0;
            sum = accumulate(cardNumber, cardNumber+n, sum);
            bool solution = checkValidity(sum);
            return solution;
        }

        int doubleProduct(int number) { //STEP 3
            int result = number*2;
            if(result > 9){
                result -= 9;
            }
            return result;
        }

        int updateArray(int* cardNumber) { //STEP 2
            int i = 14;
            while (i >= 0) { 
                int product = doubleProduct(cardNumber[i]);
                cardNumber[i] = product;
                i-=2;
            }
            std::array<int, 16> result;
            
            for (int i = 0; i < 16; ++i) {
                result[i] = cardNumber[i];
            }

            bool solution = addDigits(result.data());
            return solution;
        }
     
};
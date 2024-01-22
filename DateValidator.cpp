#include <ctime>
using namespace std;

#include <iostream>

class DateValidator{   
    public:   
        int expireMonth;
        int expireYear; 

        DateValidator(int em, int ey) {
            expireMonth = em;
            expireYear = ey;
        }

        int getCurrentMonth(){
            time_t totalTime = time(0);
            tm *currentTime = localtime(&totalTime);

            int month = 1 + currentTime->tm_mon;
            return month;
        }

        int getCurrentYear(){
            time_t totalTime = time(0);
            tm *currentTime = localtime(&totalTime);

            int year = 1900 + currentTime->tm_year;
            return year;

        }

        bool checkDate(){
            int cardMonth = expireMonth;
            int cardYear = expireYear;

            int currentMonth = getCurrentMonth();
            int currentYear = getCurrentYear();

            if (cardYear > currentYear){
                return true;
            } else if (cardMonth > currentMonth) {
                return true;
            } else {
                return false;
            }
        }
};

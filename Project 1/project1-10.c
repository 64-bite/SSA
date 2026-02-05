#include <stdio.h>
#include <stdbool.h>

typedef enum {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC} Month;
typedef enum {GREGORIAN, JULIAN} CalendarType;

typedef struct {
    int day;
    Month month;
    int year;
} Date;

bool isLeap(int year, CalendarType type) {
    if(type == GREGORIAN) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    } else {
        return (year % 4 == 0);
    }
}

int daysInMonth(Month m, int year, CalendarType type) {
    switch(m){
        case FEB: return isLeap(year, type) ? 29 : 28;
        case APR: case JUN: case SEP: case NOV: return 30;
        default: return 31;
    }
}

void nextDate(Date *d, CalendarType t){
    d->day++;
    if(d->day > daysInMonth(d->month, d->year, t)){
        d->day = 1;
        d->month++;
        if(d->month > 12) {
            d->month = JAN;
            d->year++;
        }
    }
}

int main(){
    Date today = {29, FEB, 2024};
    CalendarType cal = JULIAN;
    printf("Today: %02d.%02d.%d (Calendar: %s)\n", today.day, today.month, today.year, cal == GREGORIAN ? "Gregorian" : "Julian");
    nextDate(&today,cal);
    printf("Today: %02d.%02d.%d (Calendar: %s)\n", today.day, today.month, today.year, cal == GREGORIAN ? "Gregorian" : "Julian");
    return 0;
}


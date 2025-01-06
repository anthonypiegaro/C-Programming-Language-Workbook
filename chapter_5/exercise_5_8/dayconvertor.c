#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int day, int *pmonth, int *pday);

int main() {
    int month, day;

    printf("Day of Year:\n");
    printf("Invalid Month Month\t%3d\n", day_of_year(2025, 0, 20));
    printf("Invalid Day\t%3d\n", day_of_year(2025, 6, 0));
    printf("Invalid Date\t%3d\n", day_of_year(2025, 2, 29));
    printf("February 29, 2024\t%3d\n", day_of_year(2024, 2, 29));
    printf("December, 17, 1999\t%3d\n", day_of_year(1999, 12, 17));
    printf("Invalid Month\t%3d\n", day_of_year(2012, 13, 10));

    printf("\n");

    printf("Date\n");

    month_day(1999, 0, &month, &day);
    printf("Invalid Day: %d, %d\n", month, day);

    month_day(2025, 366, &month, &day);
    printf("Invalid Day: %d, %d\n", month, day);

    month_day(2024, 366, &month, &day);
    printf("366 Day of 2024: %d, %d\n", month, day);

    month_day(1999, 351, &month, &day);
    printf("351 day of 1999: %d, %d\n", month, day);


    return 0;
}

int day_of_year(int year, int month, int day) {
    int leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (month <= 0 || 12 < month) {
        printf("error: month %d does not exist\n", month);
        return -1;
    }

    if (day <= 0 || daytab[leap][month] < day) {
        printf("error: month %d does not have %d days\n", month, day);
        return -1;
    }

    for (int i = 1; i < month; ++i) {
        day += daytab[leap][i];
    }

    return day;
}

void month_day(int year, int day, int *pmonth, int *pday) {
    int month, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (day > 366 || (day > 365 && !leap)) {
        printf("error: Too many days for given year\n");
        return;
    }

    if (day <= 0) {
        printf("error: invalid days, day cannot be less than 1\n");
    }

    for (month = 0; day > daytab[leap][month]; ++month) {
        day -= daytab[leap][month];
    }

    *pmonth = month;
    *pday = day;
}

#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    printf("March 5, 2023 => %d day of that year\n", day_of_year(2023, 3, 5));
    printf("March 5, 2024 => %d day of that year\n", day_of_year(2024, 3, 5));

    printf("January 1, 2023 => %d day of that year\n", day_of_year(2023, 1, 1));
    printf("December 31, 2023 => %d day of that year\n", day_of_year(2023, 12, 31));

    printf("January 1, 2024 => %d day of that year\n", day_of_year(2024, 1, 1));
    printf("December 31, 2024 => %d day of that year\n", day_of_year(2024, 12, 31));

    printf("February 29, 2023 => %d day of that year\n", day_of_year(2023, 2, 29));
    printf("February 29, 2024 => %d day of that year\n", day_of_year(2024, 2, 29));
    printf("March 1, 2023 => %d day of that year\n", day_of_year(2023, 3, 1));
    printf("March 1, 2024 => %d day of that year\n", day_of_year(2024, 3, 1));

    printf("0 5, 2023 => %d day of that year\n", day_of_year(2023, 0, 5));
    printf("13 5, 2024 => %d day of that year\n", day_of_year(2024, 13, 5));

    int month, day, yearday, year;

    year = 2023;
    yearday = 0;
    month_day(year, yearday, &month, &day);
    printf("%d day of the year %d: month=%d, day=%d\n", yearday, year, month, day);

    year = 2023;
    yearday = 366;
    month_day(year, yearday, &month, &day);
    printf("%d day of the year %d: month=%d, day=%d\n", yearday, year, month, day);

    year = 2024;
    yearday = 366;
    month_day(year, yearday, &month, &day);
    printf("%d day of the year %d: month=%d, day=%d\n", yearday, year, month, day);

    year = 2024;
    yearday = 367;
    month_day(year, yearday, &month, &day);
    printf("%d day of the year %d: month=%d, day=%d\n", yearday, year, month, day);

    year = 2023;
    yearday = 60;
    month_day(year, yearday, &month, &day);
    printf("%d day of the year %d: month=%d, day=%d\n", yearday, year, month, day);

    year = 2024;
    yearday = 60;
    month_day(year, yearday, &month, &day);
    printf("%d day of the year %d: month=%d, day=%d\n", yearday, year, month, day);

    return 0;
}

int day_of_year(int year, int month, int day) {
    int i, leap;

    if (12 < month || month <= 0) {
        printf("error: invlaid month\n");
        return 0;
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (daytab[leap][month] < day || day <= 0) {
        printf("error: invalid day\n");
        return 0;
    }

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if ((leap && yearday > 366) || (!leap && yearday > 365) || yearday <= 0) {
        printf("error: invalid year day\n");
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

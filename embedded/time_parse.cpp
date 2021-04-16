//
//
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

time_t TIME2time(const char *str)
{
    struct tm tbuf {};

    const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    // 'Apr 16 2021'
    int month = -1; 
    for (int i = 0; i != sizeof(months) / sizeof(*months); ++i) {
        if (strncmp(months[i], str, 3) == 0) {
            month = i;
            break;
        }
    }
    if (month == -1)
        return time_t{};
    char* rest;
    int day = strtol(str + 3, &rest, 10);
    int year = strtol(rest, NULL, 10);

    tbuf.tm_mon = month;
    tbuf.tm_mday = day;
    tbuf.tm_year = year - 1900;

    return mktime(&tbuf);
}

int main()
{
    const char compiled[] = __DATE__;

    // 'Apr 16 2021'
    printf("Compiled on: %s\n", compiled);
    printf("----------------\n");

    time_t t = TIME2time(compiled);
    printf("Parsed: %s", ctime(&t));
    printf("----------------\n");

    return 0;
}
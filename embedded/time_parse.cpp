//
//
//

#include <stdio.h>
#include <time.h>

int main()
{
    const char compiled[] = __DATE__;

    printf("Compiled on: %s\n", compiled);
    printf("----------------\n");

    return 0;
}
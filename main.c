#include <stdio.h>
#include <limits.h>

int main() {
    int x1 = INT_MAX;
    int x2 = INT_MAX; 
   // printf("Initial value of x: %d\n", x);

    if ( x1 + x2 <= INT_MAX)
        printf("%d bitcoin allocated\n", x1);
    else
        printf("Error, bitcoin not allocated");

    return 0;
}

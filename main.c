#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>

int overFlowDemo(){
    int64_t x1 = INT64_MAX;
    int64_t x2 = INT64_MAX; 
    int64_t wallet1 = 0;
    int64_t wallet2 = 0;
   // printf("Initial value of x: %d\n", x);
    int64_t UTXO = 50;
    int64_t final_value = UTXO - (x1 + x2);
    if (final_value >= 0)
    {
        printf("bitcoin allocated to wallet 1: %"PRId64"\n", x1);
        printf("bitcoin allocated to wallet 2: %"PRId64"\n", x2);
        printf("bitcoin originally in UTXO: %"PRId64"\n", UTXO);
        printf("bitcoin in UTXO: %"PRId64"\n", final_value);
        wallet1 = wallet1 + x1;
        wallet2 = wallet2 + x2;
    }
    else
        printf("%d Error, bitcoin not allocated", final_value);

    return 0;
}

int main() {
    int user_input;
    while(1)
    {
        printf("1: Overflow demo\n2: Fix Demo\n3: Exit\n");
        scanf("%d", &user_input);
        if (user_input == 1)
        {
            printf("Overflow demo\n");
            overFlowDemo();
        }
        else if (user_input == 2)
        {
            printf("Fix demo\n");
        }
        else if (user_input == 3)
        {
            printf("Exiting\n");
            break;
        }
        else
        {
            printf("Invalid input\n");
        }
    }
   
}

#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Wallet {
    int64_t Coin;
    int64_t Cent;
    char ID[26];
};

struct Transaction {
    struct Wallet sender;
    struct Wallet receiver;
    int64_t amount;
    char ID[26];
};

struct Block {
    struct Transaction transactions[3];
    char ID[26];
    int blockNumber;
    struct Block*  next;
    struct Block*  prev;
    char hash[26];
};

struct BlockChain {
    struct Block* first;
    int size;
};

int overFlowDemo(){
    int64_t x1 = INT64_MAX;
    int64_t x2 = INT64_MAX; 
    int64_t wallet1 = 0;
    int64_t wallet2 = 0;
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

char* randomHexInt() 
{ 
    srand(time(0)); 
  
    char hexChar[] 
        = { '0', '1', '2', '3', '4', '5', 
            '6', '7', '8', '9', 'A', 'B', 
            'C', 'D', 'E', 'F' }; 
    char* final_hex = (char*)malloc(25 * sizeof(char));

    for (int i = 0; i < 24; i++) { 
  
        int len = rand() % 24 + 1; 
        for (int j = 0; j < len; j++) { 
            final_hex[j] = hexChar[rand() % 16];
        } 
        //printf("%c", final_hex[i]);
    } 
    final_hex[24] = '\0';
    
    return final_hex;
} 

void generateWallet(){
    struct Wallet wallet1;
    struct Wallet wallet2;
    struct Wallet wallet3;
    wallet1.Coin = 0;
    wallet1.Cent = 0;
    strncpy(wallet1.ID, randomHexInt(), 26);
    wallet2.Coin = 0;
    wallet2.Cent = 0;
    strncpy(wallet2.ID, randomHexInt(), 26);
    wallet3.Coin = 0;
    wallet3.Cent = 50;
    strncpy(wallet3.ID, randomHexInt(), 26);
    printf("Wallet 1: %"PRId64".%"PRId64"\n", wallet1.Coin, wallet1.Cent);
    printf("Wallet 2: %"PRId64".%"PRId64"\n", wallet2.Coin, wallet2.Cent);
    printf("Wallet 3: %"PRId64".%"PRId64"\n", wallet3.Coin, wallet3.Cent);
}

struct BlockChain generateBlockChain(int size){
    clock_t startTime = clock();
    int msec = 0;
    struct BlockChain blockChain;
    struct Block block1;
    blockChain.size = size; //Change to desired blockchain size
    blockChain.first = &block1;
    block1.blockNumber = 0;
    strncpy(block1.ID, randomHexInt(), 26);
    for (int i = 0; i < 3; i++)
    {
        struct Transaction transaction;
        transaction.amount = rand() % 100;
        strncpy(transaction.ID, randomHexInt(), 26);
        strncpy(transaction.sender.ID, randomHexInt(), 26);
        strncpy(transaction.receiver.ID, randomHexInt(), 26);
        block1.transactions[i] = transaction;
    }
    int N = 0;
    struct Block* cur = blockChain.first;
    cur->prev = NULL;
    for (int i = 1; i < blockChain.size; i++)
    {
        struct Block block;
        block.blockNumber = N;
        cur->next = &block;
        strncpy(block.ID, randomHexInt(), 26);
        for (int j = 0; j < 3; j++)
        {
            struct Transaction transaction;
            transaction.amount = rand() % 100;
            strncpy(transaction.ID, randomHexInt(), 26);
            strncpy(transaction.sender.ID, randomHexInt(), 26);
            strncpy(transaction.receiver.ID, randomHexInt(), 26);
            block.transactions[j] = transaction;
        }
        block.prev = cur;
        cur = &block;
    }
    clock_t difference = clock() - startTime;
    msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Block Count %d: Time taken %d seconds %d milliseconds\n", size, msec/1000, msec%1000);
    int64_t realtime = size * 10;
    printf("Block Count %d with average bitcoin validation time(10 mins): Time taken %d days %d hours %d minutes\n", size, realtime/1440, realtime%1440/60, realtime%60);
    return blockChain;
}

int fix(){
    printf("--------------------------------------\n");
    printf("Integer overflow Fix\n");
    printf("--------------------------------------\n");
    int64_t COIN = 100000000; // Smallest unit of currency, 1 BTC = 100 million satoshis
    int64_t MAX_MONEY = 21000000 * COIN; // Max number of bitcoins is 21 million 
    int64_t x1 = INT64_MAX;
    int64_t x2 = INT64_MAX; 
    int64_t arr[] = {x1, x2}; // array of transactions
    int64_t wallet1 = 0;
    int64_t wallet2 = 0;
    int64_t UTXO = 50;
    int64_t final_value = UTXO - (x1 + x2);
    int length = sizeof(arr) / sizeof(arr[0]); // Number of transactions
    int64_t nValueOut = 0;
    for (int i = 0; i < length; i++){
        if (arr[i] < 0){
            printf("Error, transaction output negative\n");
            printf("--------------------------------------\n");
            return 0;
        }
        if (arr[i] > MAX_MONEY){
            printf("Error, transaction %d output too high\n", i+1);
            printf("Transaction %d value: %"PRId64"\n", i+1, arr[i]);
            printf("Maximum transaction value : %"PRId64"\n", MAX_MONEY);
            printf("--------------------------------------\n");
            return 0;
        }
        nValueOut += arr[i];
        if (nValueOut > MAX_MONEY){
            printf("Final total transaction output too high\n");
            printf("Total transaction value: %"PRId64"\n", nValueOut);
            printf("Maximum transaction value : %"PRId64"\n", MAX_MONEY);
            printf("--------------------------------------\n");
            return 0;
        }
    }
    
    // Successfully passed the checks, transactions can be completed
    printf("Transactions approved\n");
    printf("--------------------------------------\n");
    printf("bitcoin allocated to wallet 1: %"PRId64"\n", x1);
    printf("bitcoin allocated to wallet 2: %"PRId64"\n", x2);
    printf("bitcoin originally in UTXO: %"PRId64"\n", UTXO);
    printf("bitcoin in UTXO: %"PRId64"\n", final_value);
    printf("--------------------------------------\n");
    wallet1 = wallet1 + x1;
    wallet2 = wallet2 + x2;
    return 0;
}

int main() {
    int user_input;
    
    while(1)
    {
        printf("1: Overflow demo\n2: Fix Demo\n3: Time to rebuild blockchain\n4: Exit\n");
        scanf("%d", &user_input);
        if (user_input == 1)
        {
            printf("Overflow demo\n");
            overFlowDemo();
        }
        else if (user_input == 2)
        {
            printf("Fix demo\n");
            fix();
        }
        else if (user_input == 3)
        {
            printf("Time to rebuild blockchain\n");
            generateBlockChain(53);
            generateBlockChain(10000);
            generateBlockChain(100000);
            //generateBlockChain(838319); //current bitcoin blockchain size
            int64_t realtime = 838319 * 10;
            printf("Block Count %d with average bitcoin validation time(10 mins): Time taken %d days %d hours %d minutes\n", 838319, realtime/1440, realtime%1440/60, realtime%60);
        }
        else if (user_input == 4)
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

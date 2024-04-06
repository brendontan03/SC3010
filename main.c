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
        printf("%c", final_hex[i]);
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

struct BlockChain generateBlockChain(){
    struct BlockChain blockChain;
    struct Block block1;
    blockChain.size = 50;
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
    return blockChain;
}

int main() {
    int user_input;
    struct BlockChain blockChain = generateBlockChain();
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
            randomHexInt();
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

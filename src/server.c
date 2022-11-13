#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/Std_Types.h"
#include "../include/server.h"
#include "../include/database.h"

typedef struct Card
{
    u16 ExpirationDate;
    u64 PAN;
    u8 *HolderName;
} ST_Card;

extern ST_Card Card;
u32 Global_u32ClientId = CLIENT_NOT_FOUND;
u32 Global_u32TransactionAmount = 0;

u8 SERVER_u8ValidateAccount(void)
{
    u8 Local_u8Valid = INVALID;

    for (u32 i = 0; i < sizeof(PAN); i++)
    {
        if (Card.PAN == PAN[i] && !strcmp(strupr(Card.HolderName), HolderName[i]) && State[i] == ACTIVE)
        {
            Local_u8Valid = VALID;
            Global_u32ClientId = i;
            break;
        }
    }
    return Local_u8Valid;
}
u8 SERVER_u8ValidateBalance(u32 Copy_u32TransactionAmount)
{
    u8 Local_u8Valid = INVALID;

    if (Balance[Global_u32ClientId] >= Copy_u32TransactionAmount)
    {
        Local_u8Valid = VALID;
        Global_u32TransactionAmount = Copy_u32TransactionAmount;
    }

    return Local_u8Valid;
}

void SERVER_u8UpdateAccountBalance(void)
{
    Balance[Global_u32ClientId] -= Global_u32TransactionAmount;
}

void SERVER_VidSaveTransaction(void)
{
    u8 Local_u8TransactionId = 0;

    for (u32 i = 0; i < sizeof(TransactionId); i++)
    {
        if (TransactionId[i] == 0)
        {
            Local_u8TransactionId = i;
            break;
        }
    }

    TransactionId[Local_u8TransactionId] = Local_u8TransactionId + 1;
    TransactionAmount[Local_u8TransactionId] = Global_u32TransactionAmount;
    TransactionDate[Local_u8TransactionId] = time(NULL);
    TransactionPAN[Local_u8TransactionId] = Card.PAN;
    TransactionState[Local_u8TransactionId] = VALID;

    printf("\n----------------------------------------------------------------");
    printf("Transaction is done successfully\n");
    printf("Transaction ID: %u\n", TransactionId[Local_u8TransactionId]);
    printf("Transaction Amount: %u\n", TransactionAmount[Local_u8TransactionId]);
    printf("Transaction Date: %s", ctime(&TransactionDate[Local_u8TransactionId]));
    printf("Transaction PAN: %llu\n", TransactionPAN[Local_u8TransactionId]);
}
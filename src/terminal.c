#include <stdio.h>
#include <time.h>
#include "../include/Std_Types.h"
#include "../include/terminal.h"

typedef struct Card
{
    u16 ExpirationDate;
    u64 PAN;
    u8 *HolderName;
} ST_Card;

extern ST_Card Card;

u8 TERMINAL_u8ValidateCardExpDate()
{
    u8 Local_u8Valid = INVALID, Local_u8Mon, Local_u8Year;
    u16 Local_u16CurrentDate;

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    Local_u8Year = (((timeinfo->tm_year + 1900) / 1) % 10) + ((((timeinfo->tm_year + 1900) / 10) % 10) * 10);
    Local_u8Mon = (timeinfo->tm_mon + 1);

    Local_u16CurrentDate = (Local_u8Mon * 100) + Local_u8Year;

    if (Local_u16CurrentDate < Card.ExpirationDate)
    {
        Local_u8Valid = VALID;
    }
    return Local_u8Valid;
}

u32 TERMINAL_u8ValidateTransactionAmount(void)
{
    u8 Local_u8Valid = INVALID;
    u32 Local_u32TransactionAmount;

    printf("Enter transaction amount: ");
    scanf(" %u", &Local_u32TransactionAmount);

    if (Local_u32TransactionAmount <= MAXIMUM_TRASNACTION_AMOUNT)
    {
        Local_u8Valid = VALID;
        return Local_u32TransactionAmount;
    }
    return Local_u8Valid;
}
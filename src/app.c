#include <stdio.h>
#include "../include/Std_Types.h"
#include "../include/app.h"
#include "../include/card.h"
#include "../include/terminal.h"
#include "../include/server.h"

int main(int argc, char **argv)
{
    u32 Local_u32TransactionAmount;
    CARD_VidGetCardHolderName();
    CARD_VidGetCardExpDate();
    CARD_VidGetCardPAN();

    if (!TERMINAL_u8ValidateCardExpDate())
    {
        printf("Transcation Declined\nReason: Expired Card");
        return CARD_EXPIRED;
    }

    else if (!(Local_u32TransactionAmount = TERMINAL_u8ValidateTransactionAmount()))
    {
        printf("Transcation Declined\nReason: Amount Exceeding Limit");
        return AMOUNT_EXCEEDED;
    }

    else if (!SERVER_u8ValidateAccount())
    {
        printf("Transcation Declined\nReason: Invalid Account, Please contact your bank");
        return INVALID_ACCOUNT;
    }

    else if (!SERVER_u8ValidateBalance(Local_u32TransactionAmount))
    {
        printf("Transcation Declined\nReason: Insufficient Balance");
        return INSUFFICIENT_BALANCE;
    }

    SERVER_u8UpdateAccountBalance();
    SERVER_VidSaveTransaction();

    return 0;
}
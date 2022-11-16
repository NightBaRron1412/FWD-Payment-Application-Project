#include <stdio.h>
#include "../include/Std_Types.h"
#include "../card/card.h"
#include "../terminal/terminal.h"
#include "../server/server.h"
#include "app.h"

/* A structure that contains card data */
extern ST_cardData_t cardData;
/* A structure that contains terminal data */
extern ST_terminalData_t terminalData;
/* A structure that contains accounts data */
extern ST_transaction_t transactionDB;

/* A variable to store state code returned from server */
uint8_t serverState;

void appStart(void)
{
    /* Get the card data from the user */
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    /* Get transaction date from system OS */
    getTransactionDate(&terminalData);

    /* Check if the card is expired */
    if (isCardExpired(&cardData, &terminalData))
    {
        printf("Declined, Expired card\n");
        return;
    }

    /* Get transaction amount form user */
    getTransactionAmount(&terminalData);

    /* Check if the transaction amount is is below allowed limit */
    if (isBelowMaxAmount(&terminalData))
    {
        printf("Declined, Amount Exceeding Limit\n");
        return;
    }

    /* Get transaction state from server */
    serverState = receiveTransactionData(&transactionDB);

    /* Check if the account in invalid */
    if (serverState == FRAUD_CARD)
    {
        printf("Declined, Invalid account\n");
        return;
    }

    /* Check if the account has enough balance */
    else if (serverState == DECLINED_INSUFFICIENT_FUND)
    {
        printf("Declined, Insufficient funds\n");
        return;
    }

    /* Check if the transaction is approved */
    else if (serverState == APPROVED)
    {
        printf("Approved\n");
        return;
    }
}
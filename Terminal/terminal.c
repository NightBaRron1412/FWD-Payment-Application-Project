#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/Std_Types.h"
#include "../Card/card.h"
#include "terminal.h"

/* A structure that contains the terminal data */
ST_terminalData_t terminalData;

/* A structure that contains the card data (defined in card.h)*/
extern ST_cardData_t cardData;

/* A function that gets the transaction amount from the user */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t dateError = WRONG_DATE; /* date error flag */

    /* Get the current date from system time */
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(termData->transactionDate, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    /* Check if the date is valid */
    if ((termData->transactionDate != NULL) && (strspn(termData->transactionDate, "0123456789/") == 10))
    {
        if ((termData->transactionDate[2] == '/') && (termData->transactionDate[5] == '/'))
        {
            dateError = TERMINAL_OK;
        }
    }
    return dateError;
}

/* A function that checks if the card is expired */
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    EN_terminalError_t cardDateError = EXPIRED_CARD; /* card date error flag */

    /* Converting the date format to MM/YY */
    uint8_t card_month[3];
    uint8_t card_year[3];
    uint8_t term_month[3];
    uint8_t term_year[3];

    card_month[0] = cardData->cardExpirationDate[0];
    card_month[1] = cardData->cardExpirationDate[1];
    card_month[2] = '\0';

    card_year[0] = cardData->cardExpirationDate[3];
    card_year[1] = cardData->cardExpirationDate[4];
    card_year[2] = '\0';

    term_month[0] = termData->transactionDate[3];
    term_month[1] = termData->transactionDate[4];
    term_month[2] = '\0';

    term_year[0] = termData->transactionDate[8];
    term_year[1] = termData->transactionDate[9];
    term_year[2] = '\0';

    /* Check if the card is expired */
    if (atoi(card_year) > atoi(term_year))
    {
        cardDateError = TERMINAL_OK;
    }
    else if (atoi(card_year) == atoi(term_year))
    {
        if (atoi(card_month) >= atoi(term_month))
        {
            cardDateError = TERMINAL_OK;
        }
    }

    return cardDateError;
}

/* A function that gets the transaction amount from the user */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t amountError = INVALID_AMOUNT; /* amount error flag */

    /* Setting the transaction max amount to default value */
    setMaxAmount(&terminalData, DEFAULT_MAX_TRANSACTION_AMOUNT);

    /* Get the transaction amount from the user */
    printf("Enter the amount of the transaction: ");
    scanf("%f", &termData->transAmount);
    fflush(stdin);

    /* Check if the amount is valid */
    if (termData->transAmount > 0)
    {
        amountError = TERMINAL_OK;
    }

    return amountError;
}

/* A function that checks if the transaction amount is below the maximum allowed amount */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    EN_terminalError_t amountError = EXCEED_MAX_AMOUNT; /* amount error flag */

    /* Check if the transaction amount is below the maximum allowed amount */
    if (termData->transAmount <= termData->maxTransAmount)
    {
        amountError = TERMINAL_OK;
    }

    return amountError;
}

/* A function that sets the maximum amount allowed for the transaction */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    EN_terminalError_t maxAmountError = INVALID_MAX_AMOUNT; /* maximum amount error flag */
    if (maxAmount > 0)
    {
        termData->maxTransAmount = maxAmount;
        maxAmountError = TERMINAL_OK;
    }
}

/* Testing (Debugging) functions */
#ifdef DEBUG

void getTransactionDateTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: getTransactionDate\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: Date acquired from system\n");
    printf("Expected Output: 0\n");
    printf("Actual Output: %d\n", getTransactionDate(&terminalData));
}

void isCardExpiredTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: isCardExpired\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: Card Expiration Date: 11/27, Transaction Date: 11/22\n");
    printf("Expected Output: 0\n");
    getCardExpiryDate(&cardData);
    getTransactionDate(&terminalData);
    printf("Actual Output: %d\n", isCardExpired(&cardData, &terminalData));
    printf("\nTest Case 2: \n");
    printf("Input Data: Card Expiration Date: 11/20, Transaction Date: 11/22\n");
    printf("Expected Output: 2\n");
    getCardExpiryDate(&cardData);
    getTransactionDate(&terminalData);
    printf("Actual Output: %d\n", isCardExpired(&cardData, &terminalData));
    printf("\nTest Case 3: \n");
    printf("Input Data: Card Expiration Date: 01/21, Transaction Date: 11/22\n");
    printf("Expected Output: 2\n");
    getCardExpiryDate(&cardData);
    getTransactionDate(&terminalData);
    printf("Actual Output: %d\n", isCardExpired(&cardData, &terminalData));
}

void getTransactionAmountTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: getTransactionAmount\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 100\n");
    printf("Expected Output: 0\n");
    printf("Actual Output: %d\n", getTransactionAmount(&terminalData));
    printf("\nTest Case 2: \n");
    printf("Input Data: -100\n");
    printf("Expected Output: 4\n");
    printf("Actual Output: %d\n", getTransactionAmount(&terminalData));
    printf("\nTest Case 3: \n");
    printf("Input Data: 0\n");
    printf("Expected Output: 4\n");
    printf("Actual Output: %d\n", getTransactionAmount(&terminalData));
}

void isBelowMaxAmountTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: isBelowMaxAmount\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 10000\n");
    printf("Expected Output: 0\n");
    setMaxAmount(&terminalData, 20000.0);
    getTransactionAmount(&terminalData);
    printf("Actual Output: %d\n", isBelowMaxAmount(&terminalData));
    printf("\nTest Case 2: \n");
    printf("Input Data: 25000\n");
    printf("Expected Output: 5\n");
    setMaxAmount(&terminalData, 20000.0);
    getTransactionAmount(&terminalData);
    printf("Actual Output: %d\n", isBelowMaxAmount(&terminalData));
}

void setMaxAmountTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: setMaxAmount\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 10000\n");
    printf("Expected Output: 0\n");
    printf("Actual Output: %d\n", setMaxAmount(&terminalData, 10000.0));
    printf("\nTest Case 2: \n");
    printf("Input Data: -10000\n");
    printf("Expected Output: 6\n");
    printf("Actual Output: %d\n", setMaxAmount(&terminalData, -10000.0));
}

#endif
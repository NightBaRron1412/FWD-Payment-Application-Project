#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/Std_Types.h"
#include "../include/Bool.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "server.h"
#include "../include/database.h"

/* A global variable to store current transaction sequence number */
uint32_t transactionSequenceNumber = 0;

/* A global variable to store current transaction state */
EN_serverError_t transState;

/* A global variable to store a reference for the current account if found */
ST_accountsDB_t accountRefrence;

/* A structure that contains card data */
extern ST_cardData_t cardData;

/* A structure that contains terminal data */
extern ST_terminalData_t terminalData;

/* A function to receive transaction data and check if it's valid */
EN_transState_t receiveTransactionData(ST_transaction_t *transData)
{

    /* Check if the account exists in the database */
    if (!isValidAccount(&cardData, &accountRefrence))
    {

        /* Check if the account state is blocked */
        if (!isBlockedAccount(&accountRefrence))
        {
            /* Check if the account has enough balance */
            if (!isAmountAvailable(&terminalData, &accountRefrence))
            {
                accountRefrence.balance -= terminalData.transAmount;
                printf("\nAccount balance after transaction: %f\n", accountRefrence.balance);
                transState = APPROVED;
            }
            else
            {
                transState = DECLINED_INSUFFICIENT_FUND;
            }
        }
        else
        {
            transState = DECLINED_STOLEN_CARD;
        }
    }
    else
    {
        transState = FRAUD_CARD;
    }

    /* Save transaction */
    if (saveTransaction(transData) == SAVING_FAILED)
    {
        return INTERNAL_SERVER_ERROR;
    }
    return transState;
}

/* A function to check if the account exists in the database */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t accountError = ACCOUNT_NOT_FOUND; /* account error flag */

    uint8_t found = FALSE; /* account found flag */

    /* Loop on the database to find the account */
    for (uint8_t i = 0; i <= 5; i++)
    {
        /* Check if the account exists */
        if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0)
        {
            found = TRUE; /* account found */
            *accountRefrence = accountsDB[i];
            accountError = SERVER_OK;
            break;
        }
    }

    /* Check if the account is found */
    if (!found)
    {
        accountRefrence = NULL;
    }

    return accountError;
}

/* A function to check if the account is blocked */
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t accountError = BLOCKED_ACCOUNT; /* account error flag */

    /* Check if the account is blocked */
    if (accountRefrence->state == RUNNING)
    {
        accountError = SERVER_OK;
    }

    return accountError;
}

/* A function to check if the account has enough balance */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t balanceError = LOW_BALANCE; /* account error flag */

    /* Check if the account has enough balance */
    if (accountRefrence->balance >= termData->transAmount)
    {
        balanceError = SERVER_OK;
    }

    return balanceError;
}

/* A function to save transaction data */
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    (transData + transactionSequenceNumber)->cardHolderData = cardData;
    (transData + transactionSequenceNumber)->terminalData = terminalData;
    (transData + transactionSequenceNumber)->transState = transState;
    listSavedTransactions();
    transactionSequenceNumber++;
    return SERVER_OK;
}

/* A function to list all saved transactions */
void listSavedTransactions(void)
{
    for (int32_t i = transactionSequenceNumber; i >= 0; i--)
    {
        printf("\n#########################\n");
        printf("Transaction Sequence Number: %d\n", i);
        printf("Transaction Date: %s\n", transactionDB[i].terminalData.transactionDate);
        printf("Transaction Amount: %f\n", transactionDB[i].terminalData.transAmount);
        printf("Transaction State: %d\n", transactionDB[i].transState);
        printf("Terminal Max Amount: %f\n", transactionDB[i].terminalData.maxTransAmount);
        printf("Cardholder Name: %s\n", transactionDB[i].cardHolderData.cardHolderName);
        printf("PAN: %s\n", transactionDB[i].cardHolderData.primaryAccountNumber);
        printf("Card Expiration Date: %s\n", transactionDB[i].cardHolderData.cardExpirationDate);
        printf("#########################\n");
    }
}

/* Testing (Debugging) functions */
#ifdef DEBUG

void receiveTransactionDataTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: receiveTransactionData\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: Amir Mohammed Shetaia, 11/27, 5377407293552874, 423.53\n");
    printf("Expected Output: 0\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", receiveTransactionData(transactionDB));
    printf("\nTest Case 2: \n");
    printf("Input Data: Hamed El-Gamed, 01/25, 5358548137750737, 295.17\n");
    printf("Expected Output: 3\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", receiveTransactionData(transactionDB));
    printf("\nTest Case 3: \n");
    printf("Input Data: Medhat Abdo, 08/28, 5807007076043875, 136.34\n");
    printf("Expected Output: 2\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", receiveTransactionData(transactionDB));
    printf("\nTest Case 4: \n");
    printf("Input Data: Eyad Shetaia, 06/26, 8989374615436851, 2999.99\n");
    printf("Expected Output: 1\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", receiveTransactionData(transactionDB));
}

void isValidAccountTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: isValidAccount\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 5368841031024013\n");
    printf("Expected Output: 0\n");
    getCardPAN(&cardData);
    printf("Actual Output: %d\n", isValidAccount(&cardData, &accountRefrence));
    printf("\nTest Case 2: \n");
    printf("Input Data: 536884103738214\n");
    printf("Expected Output: 3\n");
    getCardPAN(&cardData);
    printf("Actual Output: %d\n", isValidAccount(&cardData, &accountRefrence));
}

void isBlockedAccountTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: isBlockedAccount\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 5358620937750737\n");
    printf("Expected Output: 0\n");
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", isBlockedAccount(&accountRefrence));
    printf("\nTest Case 2: \n");
    printf("Input Data: 5368841031024013\n");
    printf("Expected Output: 5\n");
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", isBlockedAccount(&accountRefrence));
}
void isAmountAvailableTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: isAmountAvailable\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 5377407293552874, 423.53\n");
    printf("Expected Output: 0\n");
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    getTransactionAmount(&terminalData);
    fflush(stdin);
    printf("Actual Output: %d\n", isAmountAvailable(&terminalData, &accountRefrence));
    printf("\nTest Case 2: \n");
    printf("Input Data: 5358620937750737, 7295.33\n");
    printf("Expected Output: 4\n");
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    getTransactionAmount(&terminalData);
    printf("Actual Output: %d\n", isAmountAvailable(&terminalData, &accountRefrence));
}

void saveTransactionTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: saveTransaction\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: Amir Mohammed Shetaia, 11/27, 5377407293552874, 423.53\n");
    printf("Expected Output: 0\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", saveTransaction(transactionDB));
    printf("\nTest Case 2: \n");
    printf("Input Data: Hamed El-Gamed, 01/25, 5358620937750737, 295.17\n");
    printf("Expected Output: 0\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", saveTransaction(transactionDB));
}

void listSavedTransactionsTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: saveTransaction\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: Amir Mohammed Shetaia, 11/27, 5377407293552874, 423.53\n");
    printf("Expected Output: 0\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", saveTransaction(transactionDB));
    printf("\nTest Case 2: \n");
    printf("Input Data: Hamed El-Gamed, 01/25, 5358620937750737, 295.17\n");
    printf("Expected Output: 0\n");
    getCardHolderName(&cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    getTransactionDate(&terminalData);
    setMaxAmount(&terminalData, 10000.0);
    getTransactionAmount(&terminalData);
    isBelowMaxAmount(&terminalData);
    isValidAccount(&cardData, &accountRefrence);
    printf("Actual Output: %d\n", saveTransaction(transactionDB));
}

#endif
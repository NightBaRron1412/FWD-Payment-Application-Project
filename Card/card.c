#include <stdio.h>
#include <string.h>
#include "../include/Std_Types.h"
#include "card.h"

/* A structure that contains card data  */
ST_cardData_t cardData;

/* A function that gets the card holder name from the user */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{

    /* Get the card holder name from the user */
    printf("Enter your card holder name: ");
    gets(cardData->cardHolderName);

    /* Check if the name is valid */
    if ((cardData->cardHolderName != NULL) && strlen(cardData->cardHolderName) >= 20 && strlen(cardData->cardHolderName) <= 24)
    {
        return CARD_OK;
    }
    else
    {
        return WRONG_NAME;
    }
}

/* A function that gets the card expiry date from the user */
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    /* Get the card expiry date from the user */
    printf("Enter your card expiry date (MM/YY): ");
    gets(cardData->cardExpirationDate);

    /* Check if the expiry date is valid */
    if ((cardData->cardExpirationDate != NULL) && strspn(cardData->cardExpirationDate, "012345678/") == 5 && cardData->cardExpirationDate[2] == '/')
    {
        return CARD_OK;
    }
    else
    {
        return WRONG_EXP_DATE;
    }
}

/* A function that gets the card PAN from the user */
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    /* Get the card PAN from the user */
    printf("Enter your card PAN: ");
    gets(cardData->primaryAccountNumber);

    /* Check if the PAN is valid */
    if ((cardData->primaryAccountNumber != NULL) && strlen(cardData->primaryAccountNumber) >= 16 && strlen(cardData->primaryAccountNumber) <= 19)
    {
        return CARD_OK;
    }
    else
    {
        return WRONG_PAN;
    }
}

/* Testing (Debugging) functions */
#ifdef DEBUG
void getCardHolderNameTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: getCardHolderName\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: Amir Mohammed Shetaia\n");
    printf("Expected Output: 0\n");
    printf("Actual Output: %d\n", getCardHolderName(&cardData));
    printf("\nTest Case 2: \n");
    printf("Input Data: Amir\n");
    printf("Expected Output: 1\n");
    printf("Actual Output: %d\n", getCardHolderName(&cardData));
    printf("\nTest Case 3: \n");
    printf("Input Data: Amir Mohammed Bedier Shetaia\n");
    printf("Expected Output: 1\n");
    printf("Actual Output: %d\n", getCardHolderName(&cardData));
}

void getCardExpiryDateTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: getCardExpiryDate\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 12/22\n");
    printf("Expected Output: 0\n");
    printf("Actual Output: %d\n", getCardExpiryDate(&cardData));
    printf("\nTest Case 2: \n");
    printf("Input Data: 12/2\n");
    printf("Expected Output: 2\n");
    printf("Actual Output: %d\n", getCardExpiryDate(&cardData));
    printf("\nTest Case 3: \n");
    printf("Input Data: 12/222\n");
    printf("Expected Output: 2\n");
    printf("Actual Output: %d\n", getCardExpiryDate(&cardData));
}

void getCardPANTest(void)
{
    printf("\nTester Name: Amir Shetaia\n");
    printf("Function Name: getCardPAN\n");
    printf("\nTest Case 1: \n");
    printf("Input Data: 1234567890123456\n");
    printf("Expected Output: 0\n");
    printf("Actual Output: %d\n", getCardPAN(&cardData));
    printf("\nTest Case 2: \n");
    printf("Input Data: 123456789012345\n");
    printf("Expected Output: 3\n");
    printf("Actual Output: %d\n", getCardPAN(&cardData));
    printf("\nTest Case 3: \n");
    printf("Input Data: 1234567890123456789123\n");
    printf("Expected Output: 3\n");
    printf("Actual Output: %d\n", getCardPAN(&cardData));
}
#endif
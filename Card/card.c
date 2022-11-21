#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/Std_Types.h"
#include "../include/Bool.h"
#include "card.h"

/* A structure that contains card data  */
ST_cardData_t cardData;

/* A function that gets the card holder name from the user */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint8_t i = 0;                         /* loop counter */
    EN_cardError_t nameError = WRONG_NAME; /* name error flag */
    uint8_t containsDigit = FALSE;         /* flag to check if the name contains a digit */

    /* Get the card holder name from the user */
    printf("Enter your card holder name: ");
    gets(cardData->cardHolderName);

    /* Check if the name is valid */
    if ((cardData->cardHolderName != NULL) && strlen(cardData->cardHolderName) >= 20 && strlen(cardData->cardHolderName) <= 24)
    {
        /* Check if the name contains any numbers or special symbols */
        while (cardData->cardHolderName[i] != '\0')
        {
            if (isdigit(cardData->cardHolderName[i]) || ispunct(cardData->cardHolderName[i]))
            {
                containsDigit = TRUE;
                break;
            }
            i++;
        }

        if (containsDigit == FALSE)
        {
            nameError = CARD_OK;
        }
    }

    return nameError;
}

/* A function that gets the card expiry date from the user */
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    EN_cardError_t expDateError = WRONG_EXP_DATE; /* expiration date error flag */

    /* Get the card expiry date from the user */
    printf("Enter your card expiry date (MM/YY): ");
    gets(cardData->cardExpirationDate);

    /* Check if the expiry date is valid */
    if ((cardData->cardExpirationDate != NULL) && strspn(cardData->cardExpirationDate, "012345678/") == 5 && cardData->cardExpirationDate[2] == '/')
    {
        /* Check if the expiry month is in range */
        if (cardData->cardExpirationDate[0] == '0' && (cardData->cardExpirationDate[1] >= '1' && cardData->cardExpirationDate[1] <= '9'))
        {
            expDateError = CARD_OK;
        }
        else if (cardData->cardExpirationDate[0] == '1' && (cardData->cardExpirationDate[1] >= '0' && cardData->cardExpirationDate[1] <= '2'))
        {
            expDateError = CARD_OK;
        }
    }

    return expDateError;
}

/* A function that gets the card PAN from the user */
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    EN_cardError_t panError = WRONG_PAN; /* PAN error flag */

    /* Get the card PAN from the user */
    printf("Enter your card PAN: ");
    gets(cardData->primaryAccountNumber);

    /* Check if the PAN is valid */
    if ((cardData->primaryAccountNumber != NULL) && strspn(cardData->primaryAccountNumber, "0123456789") >= 16 && strspn(cardData->primaryAccountNumber, "0123456789") <= 19)
    {
        panError = CARD_OK;
    }

    return panError;
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
    printf("\nTest Case 4: \n");
    printf("Input Data: Amir12 Moh34 Shetaia43\n");
    printf("Expected Output: 1\n");
    printf("Actual Output: %d\n", getCardHolderName(&cardData));
    printf("\nTest Case 5: \n");
    printf("Input Data: 123456789012345678901\n");
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
    printf("\nTest Case 4: \n");
    printf("Input Data: aa/aa\n");
    printf("Expected Output: 2\n");
    printf("Actual Output: %d\n", getCardExpiryDate(&cardData));
    printf("\nTest Case 5: \n");
    printf("Input Data: 22/22\n");
    printf("Expected Output: 2\n");
    printf("Actual Output: %d\n", getCardExpiryDate(&cardData));
    printf("\nTest Case 6: \n");
    printf("Input Data: 00/00\n");
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
    printf("\nTest Case 4: \n");
    printf("Input Data: amiramiramiram\n");
    printf("Expected Output: 3\n");
    printf("Actual Output: %d\n", getCardPAN(&cardData));
    printf("\nTest Case 5: \n");
    printf("Input Data: 1234567890qq12212\n");
    printf("Expected Output: 3\n");
    printf("Actual Output: %d\n", getCardPAN(&cardData));
}
#endif
#include <stdio.h>
#include "../include/Std_Types.h"
#include "../include/card.h"

ST_cardData_t Card;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    static u8 Local_u8HolderName[25];
    printf("Enter you card holder name: ");
    gets(Local_u8HolderName);
    Card.cardHolderName = Local_u8HolderName;
}

void CARD_VidGetCardExpDate(void)
{
    u16 Local_u8ExpirationDate;
    printf("Enter you card expiration date (MMYY): ");
    scanf(" %hu", &Local_u8ExpirationDate);
    Card.cardExpirationDate = Local_u8ExpirationDate;
}

void CARD_VidGetCardPAN(void)
{
    u64 Local_u64PAN;
    printf("Enter you card number: ");
    scanf(" %llu", &Local_u64PAN);
    Card.primaryAccountNumber = Local_u64PAN;
}
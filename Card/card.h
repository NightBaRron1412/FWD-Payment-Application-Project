/** @file card.h
 *
 * @brief A header file that includes functions prototypes and structure for card related ops.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Nov 15 , 2022
 *
 */

#ifndef CARD_H
#define CARD_H

/* Uncomment to compile the testing functions */
// #define DEBUG

/* A structure that contains the card data */
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
} ST_cardData_t;

/* A enum for card related errors */
typedef enum EN_cardError_t
{
    CARD_OK,
    WRONG_NAME,
    WRONG_EXP_DATE,
    WRONG_PAN
} EN_cardError_t;

/* Function prototypes */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

/* Testing (Debugging) functions prototypes */
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

#endif /* CARD_H */
       /*** end of file ***/
/** @file terminal.h
 *
 * @brief A header file that includes definitions functions prototypes for terminal related ops.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Nov 15 , 2022
 *
 */

#ifndef TERMINAL_H
#define TERMINAL_H

/* Uncomment to compile the testing functions */
// #define DEBUG

/* Default max transaction amount */
#define DEFAULT_MAX_TRANSACTION_AMOUNT 20000.0

/* A structure that contains the terminal data */
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
} ST_terminalData_t;

/* An enum that contains the terminal error codes */
typedef enum EN_terminalError_t
{
    TERMINAL_OK,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT
} EN_terminalError_t;

/* Function prototypes */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // TODO: Add this function to the terminal.c file

/* Testing (Debugging) functions */
void getTransactionDateTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);

#endif /* TERMINAL_H */
       /*** end of file ***/
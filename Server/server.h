/** @file server.h
 *
 * @brief A header file that includes functions prototypes and database for server related ops.
 *
 * @author Amir Shetaia
 * @version 2.1
 * @date Nov 21 , 2022
 *
 */

#ifndef SERVER_H
#define SERVER_H

/* Uncomment to compile the testing functions */
//#define DEBUG

/* A structure that contains transaction state */
typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_INSUFFICIENT_FUND,
    DECLINED_STOLEN_CARD,
    FRAUD_CARD,
    INTERNAL_SERVER_ERROR
} EN_transState_t;

/* A structure that contains transaction data */
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
} ST_transaction_t;

/* A structure that contains server states */
typedef enum EN_serverError_t
{
    SERVER_OK,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE,
    BLOCKED_ACCOUNT
} EN_serverError_t;

/* A structure that contains account states */
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
} EN_accountState_t;

/* A structure that contains account data */
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
} ST_accountsDB_t;

/* Function prototypes */
EN_transState_t receiveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
void listSavedTransactions(void);

/* Testing (Debugging) functions prototypes */
void receiveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);

#endif /* SERVER_H */
       /*** end of file ***/
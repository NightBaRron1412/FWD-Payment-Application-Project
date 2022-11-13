/** @file server.h
 *
 * @brief A header file that includes functions prototypes and database for server related ops.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Nov 13 , 2022
 *
 */

#ifndef SERVER_H
#define SERVER_H

#define SUSPENDED 0
#define ACTIVE 1
#define VALID 1
#define INVALID 0
#define CLIENT_NOT_FOUND -1

u8 SERVER_u8ValidateAccount(void);
u8 SERVER_u8ValidateBalance(u32 Copy_u32TransactionAmount);
void SERVER_u8UpdateAccountBalance(void);
void SERVER_VidSaveTransaction(void);

#endif /* SERVER_H */
       /*** end of file ***/
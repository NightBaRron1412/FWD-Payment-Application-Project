/** @file database.h
 *
 * @brief A header file that includes database for server related ops.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Nov 13 , 2022
 *
 */

#ifndef DATABASE_H
#define DATABASE_H

u8 State[] = {ACTIVE, SUSPENDED};
s32 Balance[] = {81753, 7892};
u64 PAN[] = {5222822687265940, 5503291390930796};
const u8 *HolderName[] = {"AMIR SHETAIA", "HAMED EL-GAMED"};

/* Last Transaction Data */
u32 TransactionId[65535];
u32 TransactionAmount[65535];
u64 TransactionDate[65535];
u64 TransactionPAN[65535];
u8 TransactionState[65535];

#endif /* DATABASE_H */
       /*** end of file ***/
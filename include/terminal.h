/** @file terminal.h
 *
 * @brief A header file that includes definitions functions prototypes for terminal related ops.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Nov 13 , 2022
 *
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#define MAXIMUM_TRASNACTION_AMOUNT 20000
#define VALID 1
#define INVALID 0

u8 TERMINAL_u8ValidateCardExpDate(void);
u32 TERMINAL_u8ValidateTransactionAmount(void);

#endif /* TERMINAL_H */
       /*** end of file ***/
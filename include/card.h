/** @file card.h
 *
 * @brief A header file that includes functions prototypes and structure for card related ops.
 *
 * @author Amir Shetaia
 * @version 1.0
 * @date Nov 13 , 2022
 *
 */

#ifndef CARD_H
#define CARD_H

typedef struct Card
{
    u16 ExpirationDate;
    u64 PAN;
    u8 *HolderName;
} ST_Card;

extern ST_Card Card;

void CARD_VidGetCardHolderName(void);
void CARD_VidGetCardExpDate(void);
void CARD_VidGetCardPAN(void);

#endif /* CARD_H */
       /*** end of file ***/
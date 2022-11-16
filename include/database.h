/** @file database.h
 *
 * @brief A header file that includes database for server related ops.
 *
 * @author Amir Shetaia
 * @version 2.0
 * @date Nov 15 , 2022
 *
 */

#ifndef DATABASE_H
#define DATABASE_H

/* Array of structure that contains the accounts informations */
ST_accountsDB_t accountsDB[255] = {{56784.34, RUNNING, "5377407293552874"},
                                   {6434.64, RUNNING, "5358620937750737"},
                                   {27633.16, BLOCKED, "5368841031024013"},
                                   {545.81, RUNNING, "5388474554406064"},
                                   {2000.0, RUNNING, "8989374615436851"},
                                   {100000.0, BLOCKED, "5807007076043875"}};

/* Array of structure that contains the transactions informations */
ST_transaction_t transactionDB[255] = {0};

#endif /* DATABASE_H */
       /*** end of file ***/
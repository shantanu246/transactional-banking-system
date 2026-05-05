#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>
#include "sqlite3.h"

extern sqlite3 *db; // tells other files db exists
bool UpdateIntoDatabase(int accNoDb,int ChoiceDb,int TempAmountDb,int TempTargetAccount);
bool GetWholeJnDetails();
bool RevertLastTransaction();
bool CheckValidAcccountNo(int tempAcc2);
void GetAccJnDetails(int TempAcc66);
bool RemoveTheAccount(int TempACC7);
bool GetAccountDetails(int tempACC5);
bool UpdateDepositeMoney(int TempAcc2, int tempMonay2);
bool GetWithdrawMon(int TempAcc3,int TempMon3);
bool GetMoneyTransfer(int TempSourceAcc4,int TempDestAcc4,int TempAmount4);
void ConnectDB();
void CloseDB();
int GetNewAccountNo();

#endif
//Account NewAccoutAddition(int AccountNo1,string str,AccountType AccType,int TempInitialMoney);

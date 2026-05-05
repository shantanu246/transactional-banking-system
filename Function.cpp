#include <bits/stdc++.h>
#include "Funtions.h"

using namespace std;
bool RevertLastTransaction()
{
	int TempAcc8;
	int TempMon8;
	string type8;
	int TempDestMon8;



	sqlite3_stmt *sha8;
	sqlite3_prepare_v2(db,"SELECT * from TransactionHistory order by id DESC limit 1",-1,&sha8,nullptr);
	if(sqlite3_step(sha8)==SQLITE_ROW)
	{
		TempAcc8=sqlite3_column_int(sha8,1);
		type8=(const char*)sqlite3_column_text(sha8,2);
		TempMon8=sqlite3_column_int(sha8,3);
		TempDestMon8=sqlite3_column_int(sha8,3);

	}

	if(type8=="Created")
	{
		bool resultOf8=RemoveTheAccount(TempAcc8);
		return resultOf8;
	}
	else if(type8=="Deposite") 
	{
		bool resultOf8=GetWithdrawMon(TempAcc8,TempMon8);
		return resultOf8;
	
	}
	else if (type8=="Withdraw")
	{
		bool resultOf8=UpdateDepositeMoney(TempAcc8,TempMon8);
		return resultOf8;
	}
	else if(type8=="Transfer")
	{
		bool resultOf8=GetMoneyTransfer(TempDestMon8,TempAcc8,TempMon8);
		return resultOf8;
	}
}
bool CheckValidAcccountNo(int tempAcc2)
{
	sqlite3_stmt *sha88;
	sqlite3_prepare_v2(db,"SELECT * FROM AccountDetails where accountno= ? ;",-1,&sha88,nullptr);
	sqlite3_bind_int(sha88,1,tempAcc2);
	if(sqlite3_step(sha88)==SQLITE_ROW)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool RemoveTheAccount(int TempACC7)
{
	sqlite3_stmt *Sha7;
	sqlite3_prepare_v2(db,"Delete from ACCOUNTDETAILS where accountno = ?",-1,&Sha7,nullptr);
	sqlite3_bind_int(Sha7,1,TempACC7);
	if(sqlite3_step(Sha7)== SQLITE_DONE)
	{
		cout<<"Delete successfully"<<endl;
		sqlite3_finalize(Sha7);
		return true;
	}
	else
	{
		cout<<"Error in Deleting the Data"<<endl;
		sqlite3_finalize(Sha7);
		return false;
	}
}

void GetAccJnDetails(int TempAcc66)
{
	sqlite3_stmt * sha6;
	cout<<"Entering in GetAccJnDetails"<<endl;
	cout<<"TempAcc66:- "<<TempAcc66<<endl;
	sqlite3_prepare_v2(db,"SELECT * FROM TransactionHistory where accountno = ?",-1,&sha6,nullptr);
	sqlite3_bind_int(sha6,1,TempAcc66);

	while(sqlite3_step(sha6) == SQLITE_ROW)
	{
		int Id=sqlite3_column_int(sha6,0);
		int TempAcc6=sqlite3_column_int(sha6,1);
		string stt=(const char*)sqlite3_column_text(sha6,2);
		int TempAmount6=sqlite3_column_int(sha6,3);
		int TempDestAmount6=sqlite3_column_int(sha6,4);
		string sttt=(const char*)sqlite3_column_text(sha6,5);

		cout<<"/////////////Printing the Table data/////////////"<<endl;
		cout<<"ID :- "<<Id<<endl;
		cout<<"AccountNo is :- "<<TempAcc6<<endl;
		cout<<"Action is:- "<<stt<<endl;
		cout<<"Amount is :- "<<TempAmount6<<endl;
		cout<<"Transfered Account is:-  "<<TempDestAmount6<<endl;
		cout<<"Date:- "<<sttt<<endl;

		cout<<"-------------------------------------------------"<<endl;

	}
}
bool GetWholeJnDetails()
{
	sqlite3_stmt * sha6;

	sqlite3_prepare_v2(db,"SELECT * FROM TransactionHistory LIMIT 10",-1,&sha6,nullptr);
	cout<<"/////////////Printing the Table data/////////////"<<endl;
	while(sqlite3_step(sha6) == SQLITE_ROW)
	{
		int Id=sqlite3_column_int(sha6,0);
		int TempAcc6=sqlite3_column_int(sha6,1);
		string stt=(const char*)sqlite3_column_text(sha6,2);
		int TempAmount6=sqlite3_column_int(sha6,3);
		int TempDestAmount6=sqlite3_column_int(sha6,4);
		string sttt=(const char*)sqlite3_column_text(sha6,5);

		
		cout<<"ID :- "<<Id<<endl;
		cout<<"AccountNo is :- "<<TempAcc6<<endl;
		cout<<"Action is:- "<<stt<<endl;
		cout<<"Amount is :- "<<TempAmount6<<endl;
		cout<<"Transfered Account is:-  "<<TempDestAmount6<<endl;
		cout<<"Date:- "<<sttt<<endl;

		cout<<"-------------------------------------------------"<<endl;

	}


};
bool UpdateIntoDatabase(int accNoDb,int ChoiceDb,int TempAmountDb,int TempTargetAccount)
{
	sqlite3_stmt *shaDb;
	if(ChoiceDb==1)
	{
		cout<<"Updating the Database for the Creating Account"<<endl;
		sqlite3_prepare_v2(db,"INSERT INTO TransactionHistory(accountno,type,amount,target_account) values(?,'Created', ? , 0 )",-1,&shaDb,nullptr);
		sqlite3_bind_int(shaDb,1,accNoDb);
		sqlite3_bind_int(shaDb,2,TempAmountDb);

		if(sqlite3_step(shaDb)==SQLITE_DONE)
		{
			cout<<"Successfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return true;
		}
		else
		{
			cout<<"UNSuccessfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return false;
		}
		

	}

	else if(ChoiceDb == 2)
	{
		cout<<"Updating the Database for the Deposite Account"<<endl;
		sqlite3_prepare_v2(db,"INSERT INTO TransactionHistory(accountno,type,amount,target_account) values(?,'Deposite', ? , 0 )",-1,&shaDb,nullptr);
		sqlite3_bind_int(shaDb,1,accNoDb);
		sqlite3_bind_int(shaDb,2,TempAmountDb);

		if(sqlite3_step(shaDb)==SQLITE_DONE)
		{
			cout<<"Successfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return true;
		}
		else
		{
			cout<<"UNSuccessfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return false;
		}
	}
	else if(ChoiceDb == 3)
	{
		cout<<"Updating the Database for the Withradh Account"<<endl;
		sqlite3_prepare_v2(db,"INSERT INTO TransactionHistory(accountno,type,amount,target_account) values(?,'Withdraw', ? , 0 )",-1,&shaDb,nullptr);
		sqlite3_bind_int(shaDb,1,accNoDb);
		sqlite3_bind_int(shaDb,2,TempAmountDb);

		if(sqlite3_step(shaDb)==SQLITE_DONE)
		{
			cout<<"Successfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return true;
		}
		else
		{
			cout<<"UNSuccessfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return false;
		}
	}

	else if(ChoiceDb == 4)
	{
		cout<<"Updating the Database for the Transfer Account"<<endl;
		sqlite3_prepare_v2(db,"INSERT INTO TransactionHistory(accountno,type,amount,target_account) values(?,'Transfer', ? , ? )",-1,&shaDb,nullptr);
		sqlite3_bind_int(shaDb,1,accNoDb);
		sqlite3_bind_int(shaDb,2,TempAmountDb);
		sqlite3_bind_int(shaDb,3,TempTargetAccount);

		if(sqlite3_step(shaDb)==SQLITE_DONE)
		{
			cout<<"Successfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return true;
		}
		else
		{
			cout<<"UNSuccessfully Updated in the Jn_Database"<<endl;
			sqlite3_finalize(shaDb);
			return false;
		}
	}
}
bool GetAccountDetails(int tempACC5)
{
	cout<<"tempACC5 :- "<<tempACC5<<endl;
	int tempAmount5;
	string TempAccName5;
	int TemmpAccountType5;

	sqlite3_stmt *sha5;
	sqlite3_prepare_v2(db,"SELECT TOTALMONEY,name,accounttype FROM ACCOUNTDETAILS WHERE ACCOUNTNO = ? ",-1,&sha5,nullptr);
	sqlite3_bind_int(sha5,1,tempACC5);
	if(sqlite3_step(sha5)==SQLITE_ROW)
	{
		tempAmount5=sqlite3_column_int(sha5,0);
		TempAccName5=(const char*)sqlite3_column_text(sha5,1);
		TemmpAccountType5=sqlite3_column_int(sha5,2);
		sqlite3_finalize(sha5);
	}else
	{
		cout<<"Fail in Total Amount"<<endl;
		sqlite3_finalize(sha5);
		return false;
	}

	/*sqlite3_stmt *sha51;
	sqlite3_prepare_v2(db,"")*/
	cout<<"\n"<<endl;
	cout<<"#################################################################################"<<endl;
	cout<<"\n"<<endl;
	cout<<"AccountNo is :- "<<tempACC5<<endl;
	cout<<"Account Name is :- "<<TempAccName5<<endl;
	cout<<"Account Type is :- "<<tempAmount5<<endl;
	cout<<"Account Amount is :- "<<TemmpAccountType5<<endl;
	cout<<"\n"<<endl;
	cout<<"#################################################################################"<<endl;
	cout<<"\n"<<endl;
	return true;

	

}
bool UpdateAmmountToDb(int  TempAmmount00,int TempAccount00)
{
	sqlite3_stmt *sha00;

	sqlite3_prepare_v2(db,"update AccountDetails set totalmoney = ? where accountno = ? ;",-1,&sha00,nullptr);
	sqlite3_bind_int(sha00,1,TempAmmount00);
	sqlite3_bind_int(sha00,2,TempAccount00);

	if(sqlite3_step(sha00)==SQLITE_DONE)
	{
		sqlite3_finalize(sha00); // ← add here
		return true;
	}
	else
	{
		sqlite3_finalize(sha00); // ← add here
		return false;
	}

	return false;

}
bool UpdateDepositeMoney(int TempAcc2, int tempMonay2)
{	
	int TempTotalMon;
	sqlite3_stmt *sha2;
	sqlite3_stmt *sha21;
	sqlite3_prepare_v2(db,"SELECT TOTALMONEY FROM AccountDetails WHERE ACCOUNTNO = ?;",-1,&sha2,nullptr);
	sqlite3_bind_int(sha2,1,TempAcc2);
	if(sqlite3_step(sha2)==SQLITE_ROW)
	{
		TempTotalMon=sqlite3_column_int(sha2,0);
	}

	TempTotalMon=TempTotalMon+tempMonay2;

	cout<<"value to be updated is "<<TempTotalMon<<endl;

	//updating the value in database

	sqlite3_prepare_v2(db,"UPDATE AccountDetails SET totalmoney = ? WHERE accountno = ? ;",-1,&sha21,nullptr);
	sqlite3_bind_int(sha21,1,TempTotalMon);
	sqlite3_bind_int(sha21,2,TempAcc2);

	if(sqlite3_step(sha21)!=SQLITE_DONE)
	{
		cout<<"error in Updating in TotalMoney"<<endl;
		return false;
	}
	else
	{
		cout<<"Successfully updated the Money"<<endl;
		return true;
	}

	return true;


}

bool GetMoneyTransfer(int TempSourceAcc4,int TempDestAcc4,int TempAmount4)
{
	//int TotalAmountSource;
	//int TotalAmountDestniation;
	int tempSMoney4=0;
	int tempDMoney4=0;
	sqlite3_stmt *sha4;
	/*sqlite3_prepare_v2(db,"SELECT totalmoney , accountno FROM AccountDetails WHERE accountno= ? or accountno = ? ;",-1,&sha4,nullptr);

	sqlite3_bind_int(sha4,1,TempSourceAcc4);
	sqlite3_bind_int(sha4,2,TempDestAcc4);*/
	cout<<"TempSourceAcc4:-  "<<TempSourceAcc4<<endl;
	cout<<"TempDestAcc4"<<TempDestAcc4<<endl;
	cout<<"TempAmount4"<<TempAmount4<<endl;
	if(sqlite3_prepare_v2(db,"SELECT totalmoney FROM AccountDetails WHERE accountno = ? ",-1,&sha4,nullptr)!=SQLITE_OK)
	{
		cout << "Prepare failed: " << sqlite3_errmsg(db) << endl;
		 sqlite3_finalize(sha4);
	}
	sqlite3_bind_int(sha4,1,TempSourceAcc4);
	if(sqlite3_step(sha4)==SQLITE_ROW)
	{
		tempSMoney4=sqlite3_column_int(sha4,0);
	}

	 sqlite3_finalize(sha4);

	sqlite3_stmt *sha41;
	/*sqlite3_prepare_v2(db,"SELECT totalmoney , accountno FROM AccountDetails WHERE accountno= ? or accountno = ? ;",-1,&sha4,nullptr);

	sqlite3_bind_int(sha4,1,TempSourceAcc4);
	sqlite3_bind_int(sha4,2,TempDestAcc4);*/

	sqlite3_prepare_v2(db,"SELECT totalmoney FROM AccountDetails WHERE accountno = ?",-1,&sha41,nullptr);
	sqlite3_bind_int(sha41,1,TempDestAcc4);
	if(sqlite3_step(sha41)==SQLITE_ROW)
	{
		tempDMoney4=sqlite3_column_int(sha41,0);
	}

	/*while (sqlite3_step(sha4)==SQLITE_ROW)
	{*
		
		int tempAcc4=sqlite3_column_int(sha4,1);*/

		cout<<"tempSMoney4 :- "<<tempSMoney4<<endl;
		cout<<"tempDMoney4 :- "<<tempDMoney4<<endl;

		if(tempSMoney4<TempAmount4)
		{
			cout<<"Insufficient balance"<<endl;
			return false;
		}
		else
		{
			tempSMoney4 = tempSMoney4-TempAmount4;
			
			tempDMoney4=tempDMoney4+TempAmount4;

			if(UpdateAmmountToDb(tempSMoney4,TempSourceAcc4)!= true)//updating source ammount
			{
				cout<<"error in updating";
				return false;
			}


			if(UpdateAmmountToDb(tempDMoney4,TempDestAcc4)!= true)//updating destination ammount
			{
				cout<<"error in updating";
				return false;
			}

			return true;
		}
	
	
}

bool GetWithdrawMon(int TempAcc3,int TempMon3)
{
	int TempToalAmount3;

	sqlite3_stmt *sha3;
	sqlite3_stmt *sha31;

	sqlite3_prepare_v2(db,"select totalmoney from AccountDetails where accountno = ? ;",-1,&sha3,nullptr);
	sqlite3_bind_int(sha3,1,TempAcc3);
	if(sqlite3_step(sha3)==SQLITE_ROW)
	{
		TempToalAmount3=sqlite3_column_int(sha3,0);
	}

	cout<<" Previous TempToalAmount3 from DB :- "<<TempToalAmount3<<endl;

	if(TempToalAmount3<TempMon3)
	{
		cout<<"Not enough balance"<<endl;
		return false;
	}
	else
	{
		TempToalAmount3=TempToalAmount3-TempMon3;
		cout<<" After TempToalAmount3 from DB :- "<<TempToalAmount3<<endl;
		sqlite3_prepare_v2(db,"UPDATE AccountDetails SET totalmoney = ? WHERE accountno = ? ; ",-1,&sha31,nullptr);
		sqlite3_bind_int(sha31,1,TempToalAmount3);
		sqlite3_bind_int(sha31,2,TempAcc3);
		if(sqlite3_step(sha31)!=SQLITE_DONE)
		{
			cout<<"Error in Updating in Database"<<endl;
			return false;	
		}
		else
		{
			cout<<"Updated the Database with money :- "<<TempToalAmount3<<endl;
			return true;
		}
	}
}
void ConnectDB()
{
	 if(sqlite3_open("bank.db", &db))
    {
        cout << "Cannot open DB" << endl;
        exit(1); // exit the program if DB fails
    }
    cout << "DB Connected Successfully!" << endl;
}

void CloseDB()
{
    sqlite3_close(db);
    cout << "DB Closed!" << endl;
}


int GetNewAccountNo()
{
	int TempAcc=1001;
	sqlite3_stmt *sha;

	sqlite3_prepare_v2(
		db,"select max(accountno) from AccountDetails;",-1,&sha,nullptr
	);//it is preparing the query 
	if(sqlite3_step(sha) == SQLITE_ROW)//it is executing and getting the query
	{
	if(sqlite3_column_type(sha,0)!=SQLITE_NULL)//reading the query
	{
		TempAcc=sqlite3_column_int(sha,0)+1;
	}
}

	//sqlite3_column_int(sha,0)
	return TempAcc;
}

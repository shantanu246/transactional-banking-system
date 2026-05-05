#include <bits/stdc++.h>
#include "sqlite3.h"
using namespace std;

sqlite3 *db;

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
enum AccountType
{
	Current , Saving
};
class Account
{
	 private:
	 int Acc_No;
	 string name;
	 AccountType type;
	 int IniAmount;

	 public:
	 Account(int Account_No1,string name1,AccountType type1,int IniAmount1)
	 {
		Acc_No=Account_No1;
		name=name1;
		type=type1;
		IniAmount=IniAmount1;
	 };

	 int getAccountNo()
	 {
		return Acc_No;
	 }
	 string getName()
	 {
		return name;
	 }
	 int getAccountType()
	 {
		return type;
	 }

	 int getTotalAmmount()
	 {
		return IniAmount;
	 }

	 void DisplayValue(ofstream &Outfile)
	 {
		Outfile<<"AccontNo is :- "<<Acc_No<<endl;
		Outfile<<"Name is :- "<<name<<endl;
		Outfile<<"Account Type is :- "<<type<<endl;
		Outfile<<"Initial Amount is :- "<<IniAmount<<endl;
		Outfile<<"/////////////////////////////////////////////////////////////"<<endl;
	 }

}; 

//int Account::Acc_No=1000;

Account NewAccoutAddition(int AccountNo1,string str,AccountType AccType,int TempInitialMoney)
{
	Account NewA(AccountNo1,str,AccType,TempInitialMoney);
	
		cout<<"added successfully"<<endl;
		
	

	return NewA;

}

int main()
{
	//declaration of variables
	int Choice=0;
	int tempAccountNo;
	string str;
	int AccType;
	int TempInitialMoney;
	AccountType Temp;
	vector <Account> vct; 
	ofstream outfile ("History.txt");


	//connecting to DB

	/*sqlite3 *db;
    if(sqlite3_open("bank.db",&db))
    {
        cout<<"Cannot open DB";
        return 1;
    }
    sqlite3_stmt *stmt;*/
	ConnectDB();

	//Account NewAccount;
	
while(Choice !=8){
	cout<<"Welcome To Student Banking System "<<endl;
	cout<<"\n\n\n"<<endl;
	cout<<"Please Select the following Option"<<endl;
	cout<<"1. Create Account"<<endl;
	cout<<"2. Deposit"<<endl;
	cout<<"3. Withdraw"<<endl;
	cout<<"4. Transfer"<<endl;
	cout<<"5. Show Account"<<endl;
	cout<<"6. Transaction History"<<endl;
	cout << "7. Undo" << endl;
	cout << "8. Exit" << endl;
	cin>>Choice;
	cin.ignore();

	if(Choice==1)
	{
		cout<<"Please enter your name"<<endl;
		getline(cin,str);
		cout<<"please enter type of account"<<endl;
		cout<<"press 1 for Current and Press 2 for savings"<<endl;
		cin>>AccType;
		if(AccType==1)
		{
			Temp=Current;

		}else
		{
			Temp=Saving;
		}
		cout<<"please enter Initial money"<<endl;
		cin>>TempInitialMoney;
		
		int tempAccountNo=GetNewAccountNo();
		Account NewAccToAdd=NewAccoutAddition(tempAccountNo,str,Temp,TempInitialMoney);
	
		
		sqlite3_stmt *stmt;
    	sqlite3_prepare_v2(
        db,
        "INSERT INTO AccountDetails (accountno, name, accounttype, totalmoney) VALUES(?,?,?,?)",
        -1,
        &stmt,
        nullptr
    	);

		//BINDING THE DATA
		sqlite3_bind_int(stmt,1,NewAccToAdd.getAccountNo());
		sqlite3_bind_text(stmt, 2, NewAccToAdd.getName().c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt,3,NewAccToAdd.getAccountType());
		sqlite3_bind_int(stmt,4,NewAccToAdd.getTotalAmmount());
		if(sqlite3_step(stmt) == SQLITE_DONE)
        cout << "Record inserted successfully!" << endl;
    else
        cout << "Error: " << sqlite3_errmsg(db) << endl;

    	sqlite3_finalize(stmt);
   	
		vct.push_back(NewAccToAdd);

		cout<<"the size of VCT is "<<vct.size()<<endl;
		

		//outfile<<NewAccToAdd.DisplayValue()<<endl;
		NewAccToAdd.DisplayValue(outfile);
		
		Choice=0;
		//continue;



	}

	else if(Choice==2)
	{
		int tempAcc2;
		int tempMon2;
		cout<<"depositing the money"<<endl;
		cout<<"Enter Your Account No"<<endl;
		cin>>tempAcc2;
		cout<<"Enter Your Amount To Deposit"<<endl;
		cin>>tempMon2;
		
		if(tempMon2<=0)
		{
			cout<<"Please Enter a Valid Amount"<<endl;
		}

		else
		{
			bool Result2=UpdateDepositeMoney(tempAcc2,tempMon2);
			if(Result2==true)
			{
				cout<<"Money Deposited successfully"<<endl;
			}
			else
			{
				cout<<"Error In Deposite"<<endl;
			}
		}

		Choice=0;
		continue;
		
	}
}
	CloseDB();
	return 0;
} 

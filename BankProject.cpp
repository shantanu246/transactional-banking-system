#include <bits/stdc++.h>
#include "sqlite3.h"
#include "Funtions.h"
using namespace std;

sqlite3 *db;
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
	
while(Choice !=9){

	cout<<"Welcome To Student Banking System "<<endl;
	cout<<"\n\n\n"<<endl;
	cout<<"Please Select the following Option"<<endl;
	cout<<"1. Create Account"<<endl;
	cout<<"2. Deposit"<<endl;
	cout<<"3. Withdraw"<<endl;
	cout<<"4. Transfer"<<endl;
	cout<<"5. Show Account"<<endl;
	cout<<"6. Transaction History"<<endl;
	cout << "7. Delete " << endl;
	cout << "8. Undu" << endl;
	cout << "9. Exit" << endl;


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

		bool DbResult=UpdateIntoDatabase(NewAccToAdd.getAccountNo(),Choice,NewAccToAdd.getTotalAmmount(),0);

		if(DbResult==false)
		{
			cout<<"Error in Inserting in JN_Table"<<endl;
		}
		
		Choice=0;
		continue;
		



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
		cin.ignore();
		
		if(tempMon2<=0)
		{
		
			cout<<"Please Enter a Valid Amount"<<endl;
			Choice=0;
			continue;
		}

		else
		{
			if(CheckValidAcccountNo(tempAcc2)==false)
			{
				cout<<"Invalid AccountNo"<<endl;
				Choice=0;
				continue;
			
			}else{
			bool Result2=UpdateDepositeMoney(tempAcc2,tempMon2);
			if(Result2==true)
			{
				cout<<"Money Deposited successfully"<<endl;
				bool DbResult=UpdateIntoDatabase(tempAcc2,Choice,tempMon2,0);
				if(DbResult==false)
				{
					cout<<"Error in updating JN_Table"<<endl;
				}
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

	else if(Choice==3)
	{
		int TempAcc3;
		int TempMon3;
		cout<<"Please Enter the Account No to Withdraw"<<endl;
		cin>>TempAcc3;
		if(CheckValidAcccountNo(TempAcc3)!=true)
		{
			cout<<"Not A valid AccountNo"<<endl;
			Choice==0;
			continue;

		}
		cout<<"Please Enter the Amount to Withdraw"<<endl;
		cin>>TempMon3;
		cin.ignore();
		

		if(TempAcc3==0)
		{
			cout<<"Please Enter the valid Amount"<<endl;
		}
		else
		{
			bool Result3=GetWithdrawMon(TempAcc3,TempMon3);

			if(Result3==false)
			{
				cout<<"Error in Option 3"<<endl;
			}
			else
			{
				bool DbResult=UpdateIntoDatabase(TempAcc3,Choice,TempMon3,0);
				if(DbResult==false)
				{
					cout<<"Error in Updating Db 3"<<endl;
				}
				cout<<"Success in option 3"<<endl;
			}
		}

		Choice=0;
		continue;

	}

	else if(Choice == 4)
	{
		int TempSourceAcc4;
		int TempDestAcc4;
		int TempAmount4;

		cout<<"Please Select the Source Account:"<<endl;
		cin>>TempSourceAcc4;
		if(CheckValidAcccountNo(TempSourceAcc4)!=true)
		{
			cout<<"Not A valid AccountNo"<<endl;
			Choice==0;
			continue;

		}
		cout<<"Please Enter the Destination Account"<<endl;
		cin>>TempDestAcc4;
		if(CheckValidAcccountNo(TempDestAcc4)!=true)
		{
			cout<<"Not A valid AccountNo"<<endl;
			Choice==0;
			continue;

		}
		cout<<"Please Enter the amount to transfer"<<endl;
		cin>>TempAmount4;
		cin.ignore();


		if(TempSourceAcc4==TempDestAcc4)
		{
			cout<<"Can't transfer the Money to same Account"<<endl;
		}else if(TempAmount4<=0){
			cout<<"Entered invalid Amount"<<endl;
		}else{
				bool result4=GetMoneyTransfer(TempSourceAcc4,TempDestAcc4,TempAmount4);

				if(result4==false)
				{
					cout<<"error in transfering the money"<<endl;
				}
				else
				{
					bool DbResult=UpdateIntoDatabase(TempSourceAcc4,Choice,TempAmount4,TempAmount4);
					cout<<"Transfered the Amount Successfully"<<endl;
				}

				Choice=0;
				continue;

		}
		

		


	}

	else if (Choice == 5 )
	{
		int tempACC5;
		cout<<"Please enter the AccountNo "<<endl;
		cin>>tempACC5;
		if(CheckValidAcccountNo(tempACC5)!=true)
		{
			cout<<"Not A valid AccountNo"<<endl;
			Choice==0;
			continue;

		}
		cin.ignore();
		
		bool Result5=GetAccountDetails(tempACC5);
		if(Result5==false)
		{
			cout<<"error in fetching the details"<<endl;
		}else
		{
			cout<<"Result fetched successfully"<<endl;
		}

		Choice=0;
		continue;
	}
	else if (Choice == 6)
	{
		string str="";
		cout<<"You want to Get the whole Transaction History ? "<<endl;
		cin>>str;
		transform(str.begin(),str.end(),str.begin(), ::tolower);

		if(str == "yes" )
		{
			cout<<"Fetching last 10 recotrds "<<endl;
			GetWholeJnDetails();
		} else
		{
			cout<<"Please enter the account No :- "<<endl;
			int TempAcc66;
			cin>>TempAcc66;
			if(CheckValidAcccountNo(TempAcc66)!=true)
		{
			cout<<"Not A valid AccountNo"<<endl;
			Choice==0;
			continue;

		}
			GetAccJnDetails(TempAcc66);
		}
		Choice=0;
		continue;
		
	}

	else if(Choice  == 7 )
	{
		int TempACC7;
		cout<<"Please enter your AccountNo  :- "<<endl;
		cin>>TempACC7;
		if(CheckValidAcccountNo(TempACC7)!=true)
		{
			cout<<"Not A valid AccountNo"<<endl;
			Choice==0;
			continue;

		}
		if(RemoveTheAccount(TempACC7)==false)
		{
			cout<<"Error in updating "<<endl;
		}else
		{
			cout<<"Successfully Updated"<<endl;
		}

		Choice=0;
		continue;
		
	}
	else if (Choice == 8 )
	{
		cout<<"Reverting last Transaction "<<endl;
		bool Result8=RevertLastTransaction();

		if(Result8!=true)
		{
			cout<<"Error in Reverting"<<endl;
		}
		else
		{
			cout<<"Done Successfully"<<endl;
		}
	}


}
	CloseDB();
	return 0;
} 

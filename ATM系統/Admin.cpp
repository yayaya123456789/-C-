#include"Admin.h"
#include"BankDatabase.h"
#include"Screen.h"
#include<iostream>
#include<vector>
using namespace std;
Admin::Admin(int num,Screen &screen , BankDatabase &data )
	: Transaction(num , screen , data)
{
}
void Admin::execute()
{
	Screen & screen = getScreen();
	BankDatabase& bankdatabase = getBankDatabase();
	vector<int> accountnumber = bankdatabase.adminGetAllUsers();
	for (size_t i=0; i < accountnumber.size() ;i++)
	{
		cout << "Balance information:" << endl;
		screen.displayMessage(" - Account number: ");
		screen.displayAccount(accountnumber[i]);
		screen.displayMessage("\n - Available balance: ");
		double availableBalance = bankdatabase.getAvailableBalance(accountnumber[i]);
		screen.displayDollarAmount(availableBalance);
		screen.displayMessage("\n - Total balance:     ");
		double totalBalance = bankdatabase.getTotalBalance(accountnumber[i]);
		screen.displayDollarAmount(totalBalance);
		cout << endl;
	}
	
}
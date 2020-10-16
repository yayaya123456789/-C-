#ifndef ADMIN_H
#define ADMIN_H
#include<vector>
#include"Transaction.h"
class Screen;
class BankDatabase;
class Admin : public Transaction
{
public:
	Admin(int,Screen &, BankDatabase &);
	virtual void execute() ; 

};
#endif // !ADMIN_H

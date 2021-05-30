#ifndef __Account
#define __Account

#include <iostream>
#include <ctime>
#include "Client.h"
using namespace std;

class AccountBase
{
private:
    static int num;

    int ID;
    int type; // 1: 6 months with 10% profit        2: 1 year with 30% profit       3: 3 years with 50% profit
    int IDBank;
    int IDClient;
    long double balance;
    time_t openDate;
    time_t expDate;
    time_t profitDepositTime;
    bool isBlock;
    bool isRegister;

    AccountBase *next;

public:
    AccountBase(int _type, int _IDBank, int _IDClient, long double _balance, bool _isCheck = false);  // isCheck : if this account was request isCheck is false else true
    AccountBase(int ID); //read from file
    AccountBase();

    static int getNum();

    int getID() const;
    int getType() const;
    int getIDBank() const;
    int getIDClient() const;
    long double getBalance() const;
    time_t getOpenDate() const;
    time_t getExpDate() const;
    time_t getProfitTime() const;
    bool getIsBlock() const;
    bool getIsRegister() const;
    AccountBase *getNext() const;

    void setType(int _type);
    void setIDBank(int _IDBank);
    void setIDClient(int _IDClient);
    void setBalance(long double _balance);
    void setOpenDate(time_t _openDate);
    void setIsBlock(bool _isBlock);
    void setNext(AccountBase *_next);
};

class Account
{
private:
    AccountBase *head;
    AccountBase *last;

    void profitTime(Client *client);

public:
    Account(Client *client);
    Account(AccountBase *head, Client *client);

    void add(int _type, int _IDBank, int _IDClient, long double _balance, bool _isCheck = false);
    void add(AccountBase *_account);
    AccountBase *operator[](int _ID);

    ~Account();
};

#endif
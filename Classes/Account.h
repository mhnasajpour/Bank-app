#ifndef __Account
#define __Account

#include <iostream>
#include <ctime>
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

    AccountBase *next;

    void profitTime();

public:
    AccountBase(int _type, int _IDBank, int _IDClient, long double _balance);
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
    AccountBase *getNext() const;

    void setType(int _type);
    void setIDBank(int _IDBank);
    void setIDClient(int _IDClient);
    void setBalance(long double _balance);
    void setIsBlock(bool _isBlock);
    void setNext(AccountBase *_next);
};

class Account
{
private:
    AccountBase *head;
    AccountBase *last;

public:
    Account();
    Account(AccountBase *head);

    void add(int _type, int _IDBank, int _IDClient, long double _balance);
    void add(AccountBase *_account);
    AccountBase *operator[](int _ID);

    ~Account();
};

#endif
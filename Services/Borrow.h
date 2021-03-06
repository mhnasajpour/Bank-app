#ifndef __Borrow
#define __Borrow

#include <iostream>
#include <ctime>
#include "Account.h"
#include "../Users/Client.h"
using namespace std;

class BorrowBase
{
private:
    static int num;

    int ID;
    int IDBank;
    int IDClient;
    int IDAccget;  // get borrow in which account
    int IDAccgive; // decrease money every month from which account
    time_t startTime;
    time_t endTime;
    time_t lastInstallment;
    long double money;
    int numInstallments;
    int isRegister; // isRegister : { 1: request       2: accept       3: reject        4: Expiration date }

    BorrowBase *next;

public:
    BorrowBase(int _IDBank, int _IDClient, int _IDAccget, int _IDAccgive, int _money, int _numInstallments, int _isRegister = 1);
    BorrowBase(int ID);
    BorrowBase();

    static int getNum();

    int getID() const;
    int getIDBank() const;
    int getIDClient() const;
    int getIDAccget() const;
    int getIDAccgive() const;
    time_t getStartTime() const;
    time_t getEndTime() const;
    time_t getLastInstallment() const;
    long double getMoney() const;
    int getNumInstallments() const;
    int getIsRegister() const; // _isRegister : { 1: request       2: accept       3: reject        4: Expiration date  }
    BorrowBase *getNext() const;

    void setIDBank(int _IDBank);
    void setIDClient(int _IDClient);
    void setIDAccget(int _IDAccget);
    void setIDAccgive(int _IDAccgive);
    void setStartTime(time_t _startTime);
    void setLastInstallment(int countMonth);
    void setMoney(long double _money);
    void setNumInstallments(int _numInstallments);
    void setIsRegister(int _isRegister); // _isRegister : { 1: request       2: accept       3: reject      4: Expiration date  }
    void setNext(BorrowBase *_next);
};

class Borrow
{
private:
    BorrowBase *head;
    BorrowBase *last;

public:
    Borrow(Account *account, Client *client);
    Borrow(BorrowBase *head, Account *account, Client *client);

    void add(int _IDBank, int _IDClient, int _IDAccget, int _IDAccgive, int _money, int _numInstallments, int _isRegister = 1);
    void add(BorrowBase *_borrow);
    BorrowBase *operator[](int _ID);
    void checkBorrows(Account *account, Client *client, int index = -1);

    ~Borrow();
};

#endif
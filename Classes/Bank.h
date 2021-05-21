#ifndef __Bank
#define __Bank

#include <iostream>
#include "Date.h"
using namespace std;

class BankBase
{
private:
    static int num;

    int ID;
    string name;
    int branch;
    int *IDAccount;
    int *IDBorrow;
    int *IDManager;
    int *IDRequestBorrow;
    int sizeAcc;
    int sizeBorrow;
    int sizeManager;
    int sizeRequest;
    string username;
    string password;

    BankBase *next;

public:
    BankBase(string _name, int _branch, int *_IDAccount, int *_IDBorrow, int *_IDManager, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeManager, int _sizeRequest, string _username, string _password);
    BankBase(int ID);
    BankBase();

    static int getNum();

    int getID() const;
    string getName() const;
    int getBranch() const;
    int *getIDAccount();
    int *getIDBorrow();
    int *getIDManager();
    int *getIDRequestBorrow();
    const int *getIDAccount() const;
    const int *getIDBorrow() const;
    const int *getIDManager() const;
    const int *getIDRequestBorrow() const;
    int getSizeAcc() const;
    int getSizeBorrow() const;
    int getSizeManager() const;
    int getSizeRequest() const;
    string getUsername() const;
    string getPassword() const;
    BankBase *getNext() const;

    void setName(string _name);
    void setBranch(int _branch);
    void setIDAccount(int *_IDAccount);
    void setIDBorrow(int *_IDBorrow);
    void setIDManager(int *_IDManager);
    void setIDRequestBorrow(int *_IDRequestBorrow);
    void setSizeAcc(int _sizeAcc);
    void setSizeBorrow(int _sizeBorrow);
    void setSizeManager(int _sizeManager);
    void setSizeRequest(int _sizeRequest);
    void setUsername(string _username);
    void setPassword(string _password);
    void setNext(BankBase *_next);
};

class Bank
{
private:
    BankBase *head;
    BankBase *last;

public:
    Bank();
    Bank(BankBase *head);

    void add(string _name, int _branch, int *_IDAccount, int *_IDBorrow, int *_IDManager, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeManager, int _sizeRequest, string _username, string _password);
    void add(BankBase *_bank);
    BankBase *operator[](int _ID);

    ~Bank();
};

#endif
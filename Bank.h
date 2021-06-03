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
    int *IDRequestAccount;
    int *IDRequestBorrow;
    int sizeAcc;
    int sizeBorrow;
    int sizeManager;
    int sizeRequestAccount;
    int sizeRequestBorrow;
    string username;
    string password;

    BankBase *next;

public:
    BankBase(string _name, int _branch, string _username, string _password, int *_IDAccount = nullptr, int *_IDBorrow = nullptr, int *_IDManager = nullptr, int *_IDRequestAccount = nullptr, int *_IDRequestBorrow = nullptr, int _sizeAcc = 0, int _sizeBorrow = 0, int _sizeManager = 0, int _sizeRequestAccount = 0, int _sizeRequestBorrow = 0);
    BankBase(int ID);
    BankBase();

    static int getNum();

    int getID() const;
    string getName() const;
    int getBranch() const;
    int *getIDAccount();
    int *getIDBorrow();
    int *getIDManager();
    int *getIDRequestAccount();
    int *getIDRequestBorrow();
    const int *getIDAccount() const;
    const int *getIDBorrow() const;
    const int *getIDManager() const;
    const int *getIDRequestAccount() const;
    const int *getIDRequestBorrow() const;
    int getSizeAcc() const;
    int getSizeBorrow() const;
    int getSizeManager() const;
    int getSizeRequestAccount() const;
    int getSizeRequestBorrow() const;
    string getUsername() const;
    string getPassword() const;
    BankBase *getNext() const;

    void setName(string _name);
    void setBranch(int _branch);
    void addIDAccount(int _IDAccount);
    void addIDBorrow(int _IDBorrow);
    void addIDManager(int _IDManager);
    void addIDRequestAccount(int _IDRequestAccount);
    void addIDRequestBorrow(int _IDRequestBorrow);
    void removeIDAccount(int _IDAccount);
    void removeIDBorrow(int _IDBorrow);
    void removeIDManager(int _IDManager);
    void removeIDRequestAccount(int _IDRequestAccount);
    void removeIDRequestBorrow(int _IDRequestBorrow);
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

    void add(string _name, int _branch, string _username, string _password, int *_IDAccount = nullptr, int *_IDBorrow = nullptr, int *_IDManager = nullptr, int *_IDRequestAccount = nullptr, int *_IDRequestBorrow = nullptr, int _sizeAcc = 0, int _sizeBorrow = 0, int _sizeManager = 0, int _sizeRequestAccount = 0, int _sizeRequestBorrow = 0);
    void add(BankBase *_bank);
    BankBase *operator[](int _ID);

    ~Bank();
};

void removeNode(int *array, int &size, int num);
void addNode(int *array, int &size, int num);

#endif
#ifndef __Client
#define __Client

#include <iostream>
#include "Date.h"
using namespace std;

class ClientBase
{
private:
    static int num;

    int ID;
    string firstName;
    string lastName;
    string nationalCode;
    Date birthDate;
    int *IDAccount;
    int *IDBorrow;
    int sizeAcc;
    int sizeBorrow;
    long long unsigned balanceAll;

    ClientBase *next;

public:
    ClientBase(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int *_IDAccount, int *_IDBorrow, int _sizeAcc, int _sizeBorrow, long long unsigned _balanceAll);
    ClientBase(int ID);
    ClientBase();

    static int getNum();

    int getID() const;
    string getFirstName() const;
    string getLastName() const;
    string getNationalCode() const;
    Date getBirthDate() const;
    int *getIDAccount();
    int *getIDBorrow();
    const int *getIDAccount() const;
    const int *getIDBorrow() const;
    int getSizeAcc() const;
    int getSizeBorrow() const;
    long long unsigned getBalanceAll() const;
    ClientBase *getNext() const;

    void setFirstName(string _firstName);
    void setLastName(string _lastName);
    void setNationalCode(string _nationalCode);
    void setBirthDate(Date _birthDate);
    void setIDAccount(int *_IDAccount);
    void setIDBorrow(int *_IDBorrow);
    void setSizeAcc(int _sizeAcc);
    void setSizeBorrow(int _sizeBorrow);
    void setBalanceAll(long long unsigned _balanceAll);
    void setNext(ClientBase *_next);
};

class Client
{
private:
    ClientBase *head;
    ClientBase *last;

public:
    Client();
    Client(ClientBase *head);

    void add(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int *_IDAccount, int *_IDBorrow, int _sizeAcc, int _sizeBorrow, long long unsigned _balanceAll);
    void add(ClientBase *_client);
    ClientBase *operator[](int _ID);

    ~Client();
};

#endif
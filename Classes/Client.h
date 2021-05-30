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
    int *IDRequestAccount;
    int *IDRequestBorrow;
    int sizeAcc;
    int sizeBorrow;
    int sizeRequestAccount;
    int sizeRequestBorrow;
    long long unsigned balanceAll;
    string username;
    string password;

    ClientBase *next;

public:
    ClientBase(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int *_IDAccount, int *_IDBorrow, int *_IDRequestAccount, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeRequestAccount, int _sizeRequestBorrow, long long unsigned _balanceAll, string username, string password);
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
    int *getIDRequestAccount();
    int *getIDRequestBorrow();
    const int *getIDAccount() const;
    const int *getIDBorrow() const;
    const int *getIDRequestAccount() const;
    const int *getIDRequestBorrow() const;
    int getSizeAcc() const;
    int getSizeBorrow() const;
    int getSizeRequestAcc() const;
    int getSizeRequestBorrow() const;
    long long unsigned getBalanceAll() const;
    string getUsername() const;
    string getPassword() const;
    ClientBase *getNext() const;

    void setFirstName(string _firstName);
    void setLastName(string _lastName);
    void setNationalCode(string _nationalCode);
    void setBirthDate(Date _birthDate);
    void setIDAccount(int *_IDAccount);
    void setIDBorrow(int *_IDBorrow);
    void setIDRequestAccount(int *_IDRequestAccount);
    void setIDRequestBorrow(int *_IDRequestBorrow);
    void setSizeAcc(int _sizeAcc);
    void setSizeBorrow(int _sizeBorrow);
    void setSizeRequestAcc(int _sizeRequestAcc);
    void setSizeRequestBorrow(int _sizeRequestBorrow);
    void setBalanceAll(long long unsigned _balanceAll);
    void setUsername(string _username);
    void setPassword(string _password);
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

    void add(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int *_IDAccount, int *_IDBorrow, int *_IDRequestAccount, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeRequestAcc, int _sizeRequestBorrow, long long unsigned _balanceAll, string username, string password);
    void add(ClientBase *_client);
    ClientBase *operator[](int _ID);

    ~Client();
};

#endif
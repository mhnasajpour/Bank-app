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
    ClientBase(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, string username, string password, int *_IDAccount = nullptr, int *_IDBorrow = nullptr, int *_IDRequestAccount = nullptr, int *_IDRequestBorrow = nullptr, int _sizeAcc = 0, int _sizeBorrow = 0, int _sizeRequestAccount = 0, int _sizeRequestBorrow = 0, long long unsigned _balanceAll = 0);
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
    void addIDAccount(int _IDAccount);
    void addIDBorrow(int _IDBorrow);
    void addIDRequestAccount(int _IDRequestAccount);
    void addIDRequestBorrow(int _IDRequestBorrow);
    void removeIDAccount(int _IDAccount);
    void removeIDBorrow(int _IDBorrow);
    void removeIDRequestAccount(int _IDRequestAccount);
    void removeIDRequestBorrow(int _IDRequestBorrow);
    void setBalanceAll(long long _balanceAll);
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

    void add(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, string username, string password, int *_IDAccount = nullptr, int *_IDBorrow = nullptr, int *_IDRequestAccount = nullptr, int *_IDRequestBorrow = nullptr, int _sizeAcc = 0, int _sizeBorrow = 0, int _sizeRequestAcc = 0, int _sizeRequestBorrow = 0, long long unsigned _balanceAll = 0);
    void add(ClientBase *_client);
    ClientBase *operator[](int _ID);

    ~Client();
};

#endif
#ifndef __Client
#define __Client

#include <iostream>
#include "Date.h"
using namespace std;

class Client{
private:
    static int num;
    
    string firstName;
    string lastName;
    string nationalCode;
    Date birthDate;
    int *IDAccount;
    int *IDBorrow;
    int sizeAcc;
    int sizeBorrow;
    long long unsigned balanceAll;

public:
    Client(string _firstName = "", string _lastName = "", string _nationalCode = "", int _day = 0, int _month = 0, int _year = 0, int *_IDAccount = nullptr, int *_IDBorrow = nullptr, int _sizeAcc = 0, int _sizeBorrow = 0, long long unsigned _balanceAll = 0);

    static int setNum();
};

#endif
#ifndef __Bank
#define __Bank

#include <iostream>
#include "Date.h"
using namespace std;

class Bank
{
private:
    static int num;

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

public:
    Bank(string _name = "", int _branch = 0, int *_IDAccount = nullptr, int *_IDBorrow = nullptr, int *_IDManager = nullptr, int *_IDRequestBorrow = nullptr, int _sizeAcc = 0, int _sizeBorrow = 0, int _sizeManager = 0, int _sizeRequest = 0, string _username = "", string _password = "");

    static int setNum();
};

#endif
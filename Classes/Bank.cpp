#include "Bank.h"
#include <fstream>

int Bank::num = 0;

Bank::Bank(string _name, int _branch, int *_IDAccount, int *_IDBorrow, int *_IDManager, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeManager, int _sizeRequest, string _username, string _password)
{
    num++;

    name = _name;
    branch = _branch;
    IDAccount = _IDAccount;
    IDBorrow = _IDBorrow;
    IDManager = _IDManager;
    IDRequestBorrow = _IDRequestBorrow;
    sizeAcc = _sizeAcc;
    sizeBorrow = _sizeBorrow;
    sizeManager = _sizeManager;
    sizeRequest = _sizeRequest;
    username = _username;
    password = _password;
}

int Bank::setNum(){
    ifstream file("Bank.txt");
    file >> num;
    return num;
}
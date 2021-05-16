#include "Client.h"
#include <fstream>


int Client::num = 0;

Client::Client(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int *_IDAccount, int *_IDBorrow, int _sizeAcc, int _sizeBorrow, long long unsigned _balanceAll) : birthDate(_day, _month, _year)
{
    num++;
    
    firstName = _firstName;
    lastName = _lastName;
    nationalCode = _nationalCode;
    IDAccount = _IDAccount;
    IDBorrow = _IDBorrow;
    sizeAcc = _sizeAcc;
    sizeBorrow = _sizeBorrow;
    balanceAll = _balanceAll;
}

int Client::setNum(){
    ifstream file("Client.txt");
    file >> num;
    return num;
}
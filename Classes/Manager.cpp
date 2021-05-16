#include "Manager.h"
#include <fstream>


int Manager::num = 0;

Manager::Manager(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int _salary, int _IDBank, string _username, string _password) : birthDate(_day, _month, _year)
{
    num++;

    firstName = _firstName;
    lastName = _lastName;
    nationalCode = _nationalCode;
    salary = _salary;
    IDBank = _IDBank;
    username = _username;
    password = _password;
}

int Manager::setNum(){
    ifstream file("Manager.txt");
    file >> num;
    return num;
}
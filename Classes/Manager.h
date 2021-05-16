#ifndef __Manager
#define __Manager

#include <iostream>
#include "Date.h"
using namespace std;

class Manager{
private:
    static int num;
    
    string firstName;
    string lastName;
    string nationalCode;
    Date birthDate;
    int salary;
    int IDBank;
    string username;
    string password;

public:
    Manager(string _firstName = "", string _lastName = "", string _nationalCode = "", int _day = 0, int _month = 0, int _year = 0, int _salary = 0, int _IDBank = 0, string _username = "", string _password = "");

    static int setNum();
};

#endif
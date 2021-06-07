#ifndef __Manager
#define __Manager

#include <iostream>
#include "../OtherClasses/Date.h"
using namespace std;

class ManagerBase
{
private:
    static int num;

    int ID;
    string firstName;
    string lastName;
    string nationalCode;
    Date birthDate;
    int salary;
    int IDBank;
    string username;
    string password;

    ManagerBase *next;

public:
    ManagerBase(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int _salary, int _IDBank, string _username, string _password);
    ManagerBase(int ID);
    ManagerBase();

    static int getNum();

    int getID() const;
    string getFirstName() const;
    string getLastName() const;
    string getNationalCode() const;
    Date getBirthDate() const;
    int getSalary() const;
    int getIDBank() const;
    string getUsername() const;
    string getPassword() const;
    ManagerBase *getNext() const;

    void setFirstName(string _firstName);
    void setLastName(string _lastName);
    void setNationalCode(string _nationalCode);
    void setBirthDate(Date _birthDate);
    void setSalary(int _salary);
    void setIDBank(int _IDBank);
    void setUsername(string _username);
    void setPassword(string _password);
    void setNext(ManagerBase *_next);
};

class Manager
{
private:
    ManagerBase *head;
    ManagerBase *last;

public:
    Manager();
    Manager(ManagerBase *head);

    void add(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int _salary, int _IDBank, string _username, string _password);
    void add(ManagerBase *_Manager);
    ManagerBase *operator[](int _ID);

    ~Manager();
};

#endif

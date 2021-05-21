#include "Manager.h"
#include <fstream>
#include <limits>

int ManagerBase::num = 0;

ManagerBase::ManagerBase(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int _salary, int _IDBank, string _username, string _password) : birthDate(_day, _month, _year)
{
    ID = num++;

    firstName = _firstName;
    lastName = _lastName;
    nationalCode = _nationalCode;
    salary = _salary;
    IDBank = _IDBank;
    username = _username;
    password = _password;

    next = nullptr;
}

ManagerBase::ManagerBase(int _ID)
{
    num++;

    ifstream file("Manager.txt");
    for (int i = 0; i < (3 * _ID) + 1; ++i)
        file.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(file, firstName);
    getline(file, lastName);
    file >> ID >> nationalCode >> username >> password >> salary >> IDBank;

    int _day, _month, _year;
    file >> _day >> _month >> _year;

    birthDate.setDay(_day);
    birthDate.setMonth(_month);
    birthDate.setYear(_year);

    next = nullptr;
    file.close();
}

ManagerBase::ManagerBase()
{
    ID = num++;

    salary = 0;
    IDBank = 0;
    username = "";
    password = "";

    next = nullptr;
}

int ManagerBase::getNum()
{
    return num;
}

int ManagerBase::getID() const
{
    return ID;
}

string ManagerBase::getFirstName() const
{
    return firstName;
}

string ManagerBase::getLastName() const
{
    return lastName;
}

string ManagerBase::getNationalCode() const
{
    return nationalCode;
}

Date ManagerBase::getBirthDate() const
{
    return birthDate;
}

int ManagerBase::getSalary() const
{
    return salary;
}

int ManagerBase::getIDBank() const
{
    return IDBank;
}

string ManagerBase::getUsername() const
{
    return username;
}

string ManagerBase::getPassword() const
{
    return password;
}

ManagerBase *ManagerBase::getNext() const
{
    return next;
}

void ManagerBase::setFirstName(string _firstName)
{
    firstName = _firstName;
}

void ManagerBase::setLastName(string _lastName)
{
    lastName = _lastName;
}

void ManagerBase::setNationalCode(string _nationalCode)
{
    nationalCode = _nationalCode;
}

void ManagerBase::setBirthDate(Date _birthDate)
{
    birthDate = _birthDate;
}

void ManagerBase::setSalary(int _salary)
{
    salary = _salary;
}

void ManagerBase::setIDBank(int _IDBank)
{
    IDBank = _IDBank;
}

void ManagerBase::setUsername(string _username)
{
    username = _username;
}

void ManagerBase::setPassword(string _password)
{
    password = _password;
}

void ManagerBase::setNext(ManagerBase *_next)
{
    next = _next;
}

Manager::Manager()
{
    head = nullptr;
    last = nullptr;

    ifstream file("Manager.txt");
    int count;
    file >> count;
    file.close();

    int num = 0;
    while (count--)
    {
        ManagerBase *temp = new ManagerBase(num++);

        if (head == nullptr)
        {
            last = temp;
            head = last;
            continue;
        }

        last->setNext(temp);
        last = last->getNext();
    }

    file.close();
}

Manager::Manager(ManagerBase *_head)
{
    head = _head;

    last = _head;
    while (last->getNext() != nullptr)
        last = last->getNext();
}

void Manager::add(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int _salary, int _IDBank, string _username, string _password)
{
    ManagerBase *node = new ManagerBase(_firstName, _lastName, _nationalCode, _day, _month, _year, _salary, _IDBank, _username, _password);

    if (head == nullptr)
    {
        last = node;
        head = last;
        return;
    }

    last->setNext(node);
    last = last->getNext();
}

void Manager::add(ManagerBase *_manager)
{
    if (head == nullptr)
    {
        last = _manager;
        head = last;
        return;
    }

    last->setNext(_manager);
    last = last->getNext();
}

ManagerBase *Manager::operator[](int _ID)
{
    ManagerBase *current = head;

    while (current != nullptr)
    {
        if (current->getID() == _ID)
            return current;

        current = current->getNext();
    }

    return nullptr;
}

Manager::~Manager()
{
    ofstream file("Manager.txt");
    file << ManagerBase::getNum() << endl;

    ManagerBase *current = head;
    for (int i = 0; i < ManagerBase::getNum(); i++)
    {
        file << current->getFirstName() << '\n'
             << current->getLastName() << endl;
        file << current->getID() << ' ' << current->getNationalCode() << ' ' << current->getUsername() << ' ' << current->getPassword() << ' ' << current->getSalary() << ' ';
        file << current->getIDBank() << ' ' << current->getBirthDate().getDay() << ' ' << current->getBirthDate().getMonth() << ' ' << current->getBirthDate().getYear() << endl;

        current = current->getNext();
    }

    file.close();
    delete[] head;
}

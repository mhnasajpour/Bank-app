#include "Client.h"
#include <fstream>
#include <limits>

int ClientBase::num = 0;

ClientBase::ClientBase(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int *_IDAccount, int *_IDBorrow, int _sizeAcc, int _sizeBorrow, long long unsigned _balanceAll) : birthDate(_day, _month, _year)
{
    ID = num++;

    firstName = _firstName;
    lastName = _lastName;
    nationalCode = _nationalCode;
    IDAccount = _IDAccount;
    IDBorrow = _IDBorrow;
    sizeAcc = _sizeAcc;
    sizeBorrow = _sizeBorrow;
    balanceAll = _balanceAll;

    next = nullptr;
}

ClientBase::ClientBase(int _ID)
{
    num++;

    ifstream file("Client.txt");
    for (int i = 0; i < (3 * _ID) + 1; ++i)
        file.ignore(numeric_limits<streamsize>::max(), '\n');

    int _day, _month, _year;

    getline(file, firstName);
    getline(file, lastName);
    file >> ID >> nationalCode >> _day >> _month >> _year >> balanceAll;

    birthDate.setDay(_day);
    birthDate.setMonth(_month);
    birthDate.setYear(_year);

    file >> sizeAcc;
    IDAccount = (int *)malloc(sizeof(int) * sizeAcc);
    for (int i = 0; i < sizeAcc; i++)
        file >> IDAccount[i];

    file >> sizeBorrow;
    IDBorrow = (int *)malloc(sizeof(int) * sizeBorrow);
    for (int i = 0; i < sizeBorrow; i++)
        file >> IDBorrow[i];

    next = nullptr;
    file.close();
}

ClientBase::ClientBase()
{
    ID = num++;

    firstName = "";
    lastName = "";
    nationalCode = "0";
    IDAccount = nullptr;
    IDBorrow = nullptr;
    sizeAcc = 0;
    sizeBorrow = 0;
    balanceAll = 0;

    next = nullptr;
}

int ClientBase::getNum()
{
    return num;
}

int ClientBase::getID() const
{
    return ID;
}

string ClientBase::getFirstName() const
{
    return firstName;
}

string ClientBase::getLastName() const
{
    return lastName;
}

string ClientBase::getNationalCode() const
{
    return nationalCode;
}

Date ClientBase::getBirthDate() const
{
    return birthDate;
}

int *ClientBase::getIDAccount()
{
    return IDAccount;
}

const int *ClientBase::getIDAccount() const
{
    return IDAccount;
}

int *ClientBase::getIDBorrow()
{
    return IDBorrow;
}

const int *ClientBase::getIDBorrow() const
{
    return IDBorrow;
}

int ClientBase::getSizeAcc() const
{
    return sizeAcc;
}

int ClientBase::getSizeBorrow() const
{
    return sizeBorrow;
}

long long unsigned ClientBase::getBalanceAll() const
{
    return balanceAll;
}

ClientBase *ClientBase::getNext() const
{
    return next;
}

void ClientBase::setFirstName(string _firstName)
{
    firstName = _firstName;
}

void ClientBase::setLastName(string _lastName)
{
    lastName = _lastName;
}

void ClientBase::setNationalCode(string _nationalCode)
{
    nationalCode = _nationalCode;
}

void ClientBase::setBirthDate(Date _birthDate)
{
    birthDate = _birthDate;
}

void ClientBase::setIDAccount(int *_IDAccount)
{
    IDAccount = _IDAccount;
}

void ClientBase::setIDBorrow(int *_IDBorrow)
{
    IDBorrow = _IDBorrow;
}

void ClientBase::setSizeAcc(int _sizeAcc)
{
    sizeAcc = _sizeAcc;
}

void ClientBase::setSizeBorrow(int _sizeBorrow)
{
    sizeBorrow = _sizeBorrow;
}

void ClientBase::setBalanceAll(long long unsigned _balanceAll)
{
    balanceAll = _balanceAll;
}

void ClientBase::setNext(ClientBase *_next)
{
    next = _next;
}

Client::Client()
{
    head = nullptr;
    last = nullptr;

    ifstream file("Client.txt");
    int count;
    file >> count;
    file.close();

    int num = 0;
    while (count--)
    {
        ClientBase *temp = new ClientBase(num++);

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

Client::Client(ClientBase *_head)
{
    head = _head;

    last = _head;
    while (last->getNext() != nullptr)
        last = last->getNext();
}

void Client::add(string _firstName, string _lastName, string _nationalCode, int _day, int _month, int _year, int *_IDAccount, int *_IDBorrow, int _sizeAcc, int _sizeBorrow, long long unsigned _balanceAll)
{
    ClientBase *node = new ClientBase(_firstName, _lastName, _nationalCode, _day, _month, _year, _IDAccount, _IDBorrow, _sizeAcc, _sizeBorrow, _balanceAll);

    if (head == nullptr)
    {
        last = node;
        head = last;
        return;
    }

    last->setNext(node);
    last = last->getNext();
}

void Client::add(ClientBase *_client)
{
    if (head == nullptr)
    {
        last = _client;
        head = last;
        return;
    }

    last->setNext(_client);
    last = last->getNext();
}

ClientBase *Client::operator[](int _ID)
{
    ClientBase *current = head;

    while (current != nullptr)
    {
        if (current->getID() == _ID)
            return current;

        current = current->getNext();
    }

    return nullptr;
}

Client::~Client()
{
    ofstream file("Client.txt");
    file << ClientBase::getNum() << endl;

    ClientBase *current = head;
    for (int i = 0; i < ClientBase::getNum(); i++)
    {
        file << current->getFirstName() << '\n'
             << current->getLastName() << endl;
        file << current->getID() << ' ' << current->getNationalCode() << ' ' << current->getBirthDate().getDay() << ' ' << current->getBirthDate().getMonth() << ' ' << current->getBirthDate().getYear() << ' ' << current->getBalanceAll() << ' ';

        file << current->getSizeAcc() << ' ';
        for (int i = 0; i < current->getSizeAcc(); i++)
            file << current->getIDAccount()[i] << ' ';

        file << current->getSizeBorrow() << ' ';
        for (int i = 0; i < current->getSizeBorrow(); i++)
            file << current->getIDBorrow()[i] << ' ';

        file << endl;
        current = current->getNext();
    }

    file.close();
    delete[] head;
}
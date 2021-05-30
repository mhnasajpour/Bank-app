#include "Bank.h"
#include <fstream>
#include <limits>

int BankBase::num = 0;

BankBase::BankBase(string _name, int _branch, int *_IDAccount, int *_IDBorrow, int *_IDManager, int *_IDRequestAccount, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeManager, int _sizeRequestAccount, int _sizeRequestBorrow, string _username, string _password)
{
    ID = num++;

    name = _name;
    branch = _branch;
    IDAccount = _IDAccount;
    IDBorrow = _IDBorrow;
    IDManager = _IDManager;
    IDRequestAccount = _IDRequestAccount;
    IDRequestBorrow = _IDRequestBorrow;
    sizeAcc = _sizeAcc;
    sizeBorrow = _sizeBorrow;
    sizeManager = _sizeManager;
    sizeRequestAccount = _sizeRequestAccount;
    sizeRequestBorrow = _sizeRequestBorrow;
    username = _username;
    password = _password;

    next = nullptr;
}

BankBase::BankBase(int _ID)
{
    num++;

    ifstream file("Bank.txt");
    for (int i = 0; i <= _ID; ++i)
        file.ignore(numeric_limits<streamsize>::max(), '\n');

    file >> ID >> branch >> username >> password;

    file >> sizeAcc;
    IDAccount = (int *)malloc(sizeof(int) * sizeAcc);
    for (int i = 0; i < sizeAcc; i++)
        file >> IDAccount[i];

    file >> sizeBorrow;
    IDBorrow = (int *)malloc(sizeof(int) * sizeBorrow);
    for (int i = 0; i < sizeBorrow; i++)
        file >> IDBorrow[i];

    file >> sizeManager;
    IDManager = (int *)malloc(sizeof(int) * sizeManager);
    for (int i = 0; i < sizeManager; i++)
        file >> IDManager[i];

    file >> sizeRequestAccount;
    IDRequestBorrow = (int *)malloc(sizeof(int) * sizeRequestAccount);
    for (int i = 0; i < sizeRequestAccount; i++)
        file >> IDRequestAccount[i];
    
    file >> sizeRequestBorrow;
    IDRequestBorrow = (int *)malloc(sizeof(int) * sizeRequestBorrow);
    for (int i = 0; i < sizeRequestBorrow; i++)
        file >> IDRequestBorrow[i];

    getline(file, name);

    next = nullptr;
    file.close();
}

BankBase::BankBase()
{
    ID = num++;

    name = "";
    branch = 0;
    IDAccount = nullptr;
    IDBorrow = nullptr;
    IDManager = nullptr;
    IDRequestAccount = nullptr;
    IDRequestBorrow = nullptr;
    sizeAcc = 0;
    sizeBorrow = 0;
    sizeManager = 0;
    sizeRequestAccount = 0;
    sizeRequestBorrow = 0;
    username = "";
    password = "";

    next = nullptr;
}

int BankBase::getNum()
{
    return num;
}

int BankBase::getID() const
{
    return ID;
}

string BankBase::getName() const
{
    return name;
}

int BankBase::getBranch() const
{
    return branch;
}

int *BankBase::getIDAccount()
{
    return IDAccount;
}

int *BankBase::getIDBorrow()
{
    return IDBorrow;
}

int *BankBase::getIDManager()
{
    return IDManager;
}

int *BankBase::getIDRequestAccount()
{
    return IDRequestAccount;
}

int *BankBase::getIDRequestBorrow()
{
    return IDRequestBorrow;
}

const int *BankBase::getIDAccount() const
{
    return IDAccount;
}

const int *BankBase::getIDBorrow() const
{
    return IDBorrow;
}

const int *BankBase::getIDManager() const
{
    return IDManager;
}

const int *BankBase::getIDRequestAccount() const
{
    return IDRequestAccount;
}

const int *BankBase::getIDRequestBorrow() const
{
    return IDRequestBorrow;
}

int BankBase::getSizeAcc() const
{
    return sizeAcc;
}

int BankBase::getSizeBorrow() const
{
    return sizeBorrow;
}

int BankBase::getSizeManager() const
{
    return sizeManager;
}

int BankBase::getSizeRequestAccount() const
{
    return sizeRequestAccount;
}

int BankBase::getSizeRequestBorrow() const
{
    return sizeRequestBorrow;
}

string BankBase::getUsername() const
{
    return username;
}

string BankBase::getPassword() const
{
    return password;
}

BankBase *BankBase::getNext() const
{
    return next;
}

void BankBase::setName(string _name)
{
    name = _name;
}

void BankBase::setBranch(int _branch)
{
    branch = _branch;
}

void BankBase::setIDAccount(int *_IDAccount)
{
    IDAccount = _IDAccount;
}

void BankBase::setIDBorrow(int *_IDBorrow)
{
    IDBorrow = _IDBorrow;
}

void BankBase::setIDManager(int *_IDManager)
{
    IDManager = _IDManager;
}

void BankBase::setIDRequestAccount(int *_IDRequestAccount)
{
    IDRequestAccount = _IDRequestAccount;
}

void BankBase::setIDRequestBorrow(int *_IDRequestBorrow)
{
    IDRequestBorrow = _IDRequestBorrow;
}

void BankBase::setSizeAcc(int _sizeAcc)
{
    sizeAcc = _sizeAcc;
}

void BankBase::setSizeBorrow(int _sizeBorrow)
{
    sizeBorrow = _sizeBorrow;
}

void BankBase::setSizeManager(int _sizeManager)
{
    sizeManager = _sizeManager;
}

void BankBase::setSizeRequestAccount(int _sizeRequestAccount)
{
    sizeRequestAccount = _sizeRequestAccount;
}

void BankBase::setSizeRequestBorrow(int _sizeRequestBorrow)
{
    sizeRequestBorrow = _sizeRequestBorrow;
}

void BankBase::setUsername(string _username)
{
    username = _username;
}

void BankBase::setPassword(string _password)
{
    password = _password;
}

void BankBase::setNext(BankBase *_next)
{
    next = _next;
}

Bank::Bank()
{
    head = nullptr;
    last = nullptr;

    ifstream file("Bank.txt");
    int count;
    file >> count;
    file.close();

    int num = 0;
    while (count--)
    {
        BankBase *temp = new BankBase(num++);

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

Bank::Bank(BankBase *_head)
{
    head = _head;

    last = _head;
    while (last->getNext() != nullptr)
        last = last->getNext();
}

void Bank::add(string _name, int _branch, int *_IDAccount, int *_IDBorrow, int *_IDManager, int *_IDRequestAccount, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeManager, int _sizeRequestAccount, int _sizeRequestBorrow, string _username, string _password)
{
    BankBase *node = new BankBase(_name, _branch, _IDAccount, _IDBorrow, _IDManager, _IDRequestAccount, _IDRequestBorrow, _sizeAcc, _sizeBorrow, _sizeManager, _sizeRequestAccount, _sizeRequestBorrow, _username, _password);

    if (head == nullptr)
    {
        last = node;
        head = last;
        return;
    }

    last->setNext(node);
    last = last->getNext();
}

void Bank::add(BankBase *_bank)
{
    if (head == nullptr)
    {
        last = _bank;
        head = last;
        return;
    }

    last->setNext(_bank);
    last = last->getNext();
}

BankBase *Bank::operator[](int _ID)
{
    BankBase *current = head;

    while (current != nullptr)
    {
        if (current->getID() == _ID)
            return current;

        current = current->getNext();
    }

    return nullptr;
}

Bank::~Bank()
{
    ofstream file("Bank.txt");
    file << BankBase::getNum() << endl;

    BankBase *current = head;
    for (int i = 0; i < BankBase::getNum(); i++)
    {
        file << current->getID() << ' ' << current->getBranch() << ' ' << current->getUsername() << ' ' << current->getPassword() << ' ';

        file << current->getSizeAcc() << ' ';
        for (int i = 0; i < current->getSizeAcc(); i++)
            file << current->getIDAccount()[i] << ' ';

        file << current->getSizeBorrow() << ' ';
        for (int i = 0; i < current->getSizeBorrow(); i++)
            file << current->getIDBorrow()[i] << ' ';

        file << current->getSizeManager() << ' ';
        for (int i = 0; i < current->getSizeManager(); i++)
            file << current->getIDManager()[i] << ' ';

        file << current->getSizeRequestAccount() << ' ';
        for (int i = 0; i < current->getSizeRequestAccount(); i++)
            file << current->getIDRequestAccount()[i] << ' ';
        
        file << current->getSizeRequestBorrow() << ' ';
        for (int i = 0; i < current->getSizeRequestBorrow(); i++)
            file << current->getIDRequestBorrow()[i] << ' ';

        file << current->getName() << endl;
        current = current->getNext();
    }

    file.close();
    delete[] head;
}
#include "Bank.h"
#include <fstream>
#include <limits>
#include <cstdlib>

int BankBase::num = 0;

BankBase::BankBase(string _name, int _branch, string _username, string _password, int *_IDAccount, int *_IDBorrow, int *_IDManager, int *_IDRequestAccount, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeManager, int _sizeRequestAccount, int _sizeRequestBorrow)
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
    IDRequestAccount = (int *)malloc(sizeof(int) * sizeRequestAccount);
    for (int i = 0; i < sizeRequestAccount; i++)
        file >> IDRequestAccount[i];

    file >> sizeRequestBorrow;
    IDRequestBorrow = (int *)malloc(sizeof(int) * sizeRequestBorrow);
    for (int i = 0; i < sizeRequestBorrow; i++)
        file >> IDRequestBorrow[i];

    file.ignore(1);
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

void BankBase::addIDAccount(int _IDAccount)
{
    addNode(IDAccount, sizeAcc, _IDAccount);
}

void BankBase::addIDBorrow(int _IDBorrow)
{
    addNode(IDBorrow, sizeBorrow, _IDBorrow);
}

void BankBase::addIDManager(int _IDManager)
{
    addNode(IDManager, sizeManager, _IDManager);
}

void BankBase::addIDRequestAccount(int _IDRequestAccount)
{
    addNode(IDRequestAccount, sizeRequestAccount, _IDRequestAccount);
}

void BankBase::addIDRequestBorrow(int _IDRequestBorrow)
{
    addNode(IDRequestBorrow, sizeRequestBorrow, _IDRequestBorrow);
}

void BankBase::removeIDAccount(int _IDAccount)
{
    removeNode(IDAccount, sizeAcc, _IDAccount);
}
void BankBase::removeIDBorrow(int _IDBorrow)
{
    removeNode(IDBorrow, sizeBorrow, _IDBorrow);
}
void BankBase::removeIDManager(int _IDManager)
{
    removeNode(IDManager, sizeManager, _IDManager);
}
void BankBase::removeIDRequestAccount(int _IDRequestAccount)
{
    removeNode(IDRequestAccount, sizeRequestAccount, _IDRequestAccount);
}
void BankBase::removeIDRequestBorrow(int _IDRequestBorrow)
{
    removeNode(IDRequestBorrow, sizeRequestBorrow, _IDRequestBorrow);
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
    if (!file)
        count = 0;

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

void Bank::add(string _name, int _branch, string _username, string _password, int *_IDAccount, int *_IDBorrow, int *_IDManager, int *_IDRequestAccount, int *_IDRequestBorrow, int _sizeAcc, int _sizeBorrow, int _sizeManager, int _sizeRequestAccount, int _sizeRequestBorrow)
{
    BankBase *node = new BankBase(_name, _branch, _username, _password, _IDAccount, _IDBorrow, _IDManager, _IDRequestAccount, _IDRequestBorrow, _sizeAcc, _sizeBorrow, _sizeManager, _sizeRequestAccount, _sizeRequestBorrow);

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
}

void removeNode(int *array, int &size, int num)
{
    int i = 0;
    for (; i < size - 1; i++)
        if (num == array[i])
            break;

    for (int j = i; j < size - 1; j++)
        array[j] = array[j + 1];

    size--;
    array = (int *)realloc(array, sizeof(int) * size);
}

void addNode(int *array, int &size, int num)
{
    size++;

    if (array == nullptr)
        array = (int *)malloc(sizeof(int));
    else
        array = (int *)realloc(array, sizeof(int) * (size));

    array[size - 1] = num;
}
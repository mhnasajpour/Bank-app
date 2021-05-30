#include "Account.h"
#include <fstream>
#include <limits>

int AccountBase::num = 0;

AccountBase::AccountBase(int _type, int _IDBank, int _IDClient, long double _balance, bool _isCheck) // isCheck : if this account was request isCheck is false else true
{
    ID = num++;

    type = _type;
    IDBank = _IDBank;
    IDClient = _IDClient;
    balance = _balance;
    isBlock = false;
    isRegister = _isCheck;
    openDate = time(NULL);
    profitDepositTime = time(NULL);

    switch (type)
    {
    case 1:
        expDate = openDate + 15768000;
        break;
    case 2:
        expDate = openDate + 31536000;
        break;
    case 3:
        expDate = openDate + 94608000;
        break;
    default:
        expDate = openDate;
        break;
    }

    next = nullptr;
}

AccountBase::AccountBase(int _ID) //read from file
{
    num++;

    ifstream file("Account.txt");
    for (int i = 0; i <= _ID; ++i)
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    
    file >> ID >> type >> IDBank >> isBlock >> IDClient >> balance >> isRegister >> openDate >> expDate >> profitDepositTime;
    next = nullptr;
    file.close();
}

AccountBase::AccountBase()
{
    ID = num++;

    type = 0;
    IDBank = 0;
    IDClient = 0;
    balance = 0;
    openDate = time(NULL);
    profitDepositTime = time(NULL);
    expDate = openDate;
    isBlock = false;
    isRegister = false;

    next = nullptr;
}

int AccountBase::getNum()
{
    return num;
}

int AccountBase::getID() const
{
    return ID;
}

int AccountBase::getType() const
{
    return type;
}

int AccountBase::getIDBank() const
{
    return IDBank;
}

int AccountBase::getIDClient() const
{
    return IDClient;
}

long double AccountBase::getBalance() const
{
    return balance;
}

time_t AccountBase::getOpenDate() const
{
    return openDate;
}

time_t AccountBase::getExpDate() const
{
    return expDate;
}

time_t AccountBase::getProfitTime() const
{
    return profitDepositTime;
}

bool AccountBase::getIsBlock() const
{
    return isBlock;
}

bool AccountBase::getIsRegister() const
{
    return isRegister;
}

AccountBase *AccountBase::getNext() const
{
    return next;
}

void AccountBase::setType(int _type)
{
    type = _type;

    switch (type)
    {
    case 1:
        expDate = openDate + 15768000;
        break;
    case 2:
        expDate = openDate + 31536000;
        break;
    case 3:
        expDate = openDate + 94608000;
        break;
    default:
        expDate = openDate;
        break;
    }
}

void AccountBase::setIDBank(int _IDBank)
{
    IDBank = _IDBank;
}

void AccountBase::setIDClient(int _IDClient)
{
    IDClient = _IDClient;
}

void AccountBase::setBalance(long double _balance)
{
    balance += _balance;
}

void AccountBase::setOpenDate(time_t _openDate)
{
    openDate = _openDate;
    profitDepositTime = openDate;
    setType(type);
}

void AccountBase::setIsBlock(bool _isBlock)
{
    isBlock = _isBlock;
}

void AccountBase::setNext(AccountBase *_next)
{
    next = _next;
}

Account::Account(Client *client)
{
    head = nullptr;
    last = nullptr;

    ifstream file("Account.txt");
    int count;
    file >> count;
    file.close();

    int num = 0;
    while (count--)
    {
        AccountBase *temp = new AccountBase(num++);

        if (head == nullptr)
        {
            last = temp;
            head = last;
            continue;
        }

        last->setNext(temp);
        last = last->getNext();
    }

    profitTime(client);
    file.close();
}

Account::Account(AccountBase *_head, Client *client)
{
    head = _head;

    last = _head;
    while (last->getNext() != nullptr)
        last = last->getNext();

    profitTime(client);
}

void Account::profitTime(Client *client)
{
    AccountBase *current = head;
    while(current)
    {     
        if(!current->getIsRegister())
            return;

        int count = (time(NULL) - current->getProfitTime()) / 86400;

        switch (current->getType())
        {
        case 1:
            current->setBalance((0.1 / 365) * count * current->getBalance());
            (*client)[current->getIDClient()]->setBalanceAll((0.1 / 365) * count * current->getBalance());
            break;
        case 2:
            current->setBalance((0.3 / 365) * count * current->getBalance());
            (*client)[current->getIDClient()]->setBalanceAll((0.3 / 365) * count * current->getBalance());
            break;
        case 3:
            current->setBalance((0.5 / 365) * count * current->getBalance());
            (*client)[current->getIDClient()]->setBalanceAll((0.5 / 365) * count * current->getBalance());
            break;
        }

        current = current->getNext();
    }
}

void Account::add(int _type, int _IDBank, int _IDClient, long double _balance, bool _isCheck)
{
    AccountBase *node = new AccountBase(_type, _IDBank, _IDClient, _balance, _isCheck);

    if (head == nullptr)
    {
        last = node;
        head = last;
        return;
    }

    last->setNext(node);
    last = last->getNext();
}

void Account::add(AccountBase *_account)
{
    if (head == nullptr)
    {
        last = _account;
        head = last;
        return;
    }

    last->setNext(_account);
    last = last->getNext();
}

AccountBase *Account::operator[](int _ID)
{
    AccountBase *current = head;

    while (current != nullptr)
    {
        if (current->getID() == _ID)
            return current;

        current = current->getNext();
    }

    return nullptr;
}

Account::~Account()
{
    ofstream file("Account.txt");
    file << AccountBase::getNum() << endl;

    AccountBase *current = head;
    for (int i = 0; i < AccountBase::getNum(); i++)
    {
        file << current->getID() << ' ' << current->getType() << ' ' << current->getIDBank() << ' ' << current->getIsBlock() << ' ';
        file << current->getIDClient() << ' ' << current->getBalance() << ' ' << current->getIsRegister() << ' ' << current->getOpenDate() << ' ' << current->getExpDate() << ' ' << current->getProfitTime() << endl;

        current = current->getNext();
    }

    file.close();
    delete[] head;
}
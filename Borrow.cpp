#include "Borrow.h"
#include <fstream>
#include <limits>

int BorrowBase::num = 0;

BorrowBase::BorrowBase(int _IDBank, int _IDClient, int _IDAccget, int _IDAccgive, int _money, int _numInstallments, bool _isCheck)
{
    ID = num++;

    IDBank = _IDBank;
    IDClient = _IDClient;
    IDAccget = _IDAccget;
    IDAccgive = _IDAccgive;
    startTime = time(NULL);
    endTime = startTime + (_numInstallments * 2628000);
    lastInstallment = time(NULL);
    money = _money;
    numInstallments = _numInstallments;
    isRegister = _isCheck;

    next = nullptr;
}

BorrowBase::BorrowBase(int _ID) //read from file
{
    num++;

    ifstream file("Borrow.txt");
    for (int i = 0; i <= _ID; ++i)
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    
    file >> ID >> IDBank >> IDClient >> IDAccget >> IDAccgive >> money >> numInstallments >> startTime >> endTime >> numInstallments >> isRegister;
    next = nullptr;
    file.close();
}

BorrowBase::BorrowBase()
{
    ID = num++;

    IDBank = 0;
    IDClient = 0;
    IDAccget = 0;
    IDAccgive = 0;
    startTime = time(NULL);
    endTime = time(NULL);
    lastInstallment = time(NULL);
    money = 0;
    numInstallments = 0;
    isRegister = false;

    next = nullptr;
}

int BorrowBase::getNum()
{
    return num;
}

int BorrowBase::getID() const
{
    return ID;
}

int BorrowBase::getIDBank() const
{
    return IDBank;
}

int BorrowBase::getIDClient() const
{
    return IDClient;
}

int BorrowBase::getIDAccget() const
{
    return IDAccget;
}

int BorrowBase::getIDAccgive() const
{
    return IDAccgive;
}

time_t BorrowBase::getStartTime() const
{
    return startTime;
}

time_t BorrowBase::getEndTime() const
{
    return endTime;
}

time_t BorrowBase::getLastInstallment() const
{
    return lastInstallment;
}

long double BorrowBase::getMoney() const
{
    return money;
}

int BorrowBase::getNumInstallments() const
{
    return numInstallments;
}

bool BorrowBase::getIsRegister() const
{
    return isRegister;
}

BorrowBase *BorrowBase::getNext() const
{
    return next;
}

void BorrowBase::setIDBank(int _IDBank)
{
    IDBank = _IDBank;
}

void BorrowBase::setIDClient(int _IDClient)
{
    IDClient = _IDClient;
}

void BorrowBase::setIDAccget(int _IDAccget)
{
    IDAccget = _IDAccget;
}

void BorrowBase::setIDAccgive(int _IDAccgive)
{
    IDAccgive = _IDAccgive;
}

void BorrowBase::setStartTime(time_t _startTime)
{
    startTime = _startTime;
    endTime = startTime + (numInstallments * 2628000);
    lastInstallment = _startTime;
}

void BorrowBase::setLastInstallment(int countMonth)
{
    lastInstallment += countMonth * 2628000;
}

void BorrowBase::setMoney(long double _money)
{
    money = _money;
}

void BorrowBase::setNumInstallments(int _numInstallments)
{
    numInstallments = _numInstallments;
    endTime = startTime + (numInstallments * 2628000);
}

void BorrowBase::setIsRegister(bool _isRegister)
{
    isRegister = _isRegister;
    if(isRegister)
    {
        startTime = time(NULL);
        endTime = (numInstallments * 2628000) + time(NULL);
        lastInstallment = time(NULL);
    }
}

void BorrowBase::setNext(BorrowBase *_next)
{
    next = _next;
}

Borrow::Borrow(Account *account, Client *client)
{
    head = nullptr;
    last = nullptr;

    ifstream file("Borrow.txt");
    int count;
    file >> count;
    file.close();
    if(!file)
        count = 0;

    int num = 0;
    while (count--)
    {
        BorrowBase *temp = new BorrowBase(num++);

        if (head == nullptr)
        {
            last = temp;
            head = last;
            continue;
        }

        last->setNext(temp);
        last = last->getNext();
    }

    checkBorrows(account, client);
    file.close();
}

Borrow::Borrow(BorrowBase *_head, Account *account, Client *client)
{
    head = _head;

    last = _head;
    while (last->getNext() != nullptr)
        last = last->getNext();

    checkBorrows(account, client);
}

void Borrow::checkBorrows(Account *account, Client *client)
{
    BorrowBase *current = head;
    while(current)
    {
        if(!current->getIsRegister() || (time(NULL) - current->getLastInstallment() < 2628000))
            return;

        int count = (time(NULL) - current->getLastInstallment()) / 2628000;
        if((*account)[current->getIDAccgive()]->getBalance() < (current->getMoney() / current->getLastInstallment() * count))
        {
            ClientBase *t = (*client)[current->getIDClient()];
            for(int i = 0; i < (*client)[current->getIDClient()]->getSizeAcc(); i++)
                (*account)[t->getIDAccount()[i]]->setIsBlock(true);

            return;
        }

        (*account)[current->getIDAccgive()]->setBalance((current->getMoney() / current->getNumInstallments() * count) * (-1));
        (*client)[current->getIDClient()]->setBalanceAll((current->getMoney() / current->getNumInstallments() * count) * (-1));
        current->setLastInstallment(count);

        current = current->getNext();
    }
}

void Borrow::add(int _IDBank, int _IDClient, int _IDAccget, int _IDAccgive, int _money, int _numInstallments, bool _isCheck)
{
    BorrowBase *node = new BorrowBase(_IDBank, _IDClient, _IDAccget, _IDAccgive, _money, _numInstallments, _isCheck);

    if (head == nullptr)
    {
        last = node;
        head = last;
        return;
    }

    last->setNext(node);
    last = last->getNext();
}

void Borrow::add(BorrowBase *_borrow)
{
    if (head == nullptr)
    {
        last = _borrow;
        head = last;
        return;
    }

    last->setNext(_borrow);
    last = last->getNext();
}

BorrowBase *Borrow::operator[](int _ID)
{
    BorrowBase *current = head;

    while (current != nullptr)
    {
        if (current->getID() == _ID)
            return current;

        current = current->getNext();
    }

    return nullptr;
}

Borrow::~Borrow()
{
    ofstream file("Borrow.txt");
    file << BorrowBase::getNum() << endl;

    BorrowBase *current = head;
    for (int i = 0; i < BorrowBase::getNum(); i++)
    {
        file << current->getID() << ' ' << current->getIDBank() << ' ' << current->getIDClient() << ' ' << current->getIDAccget() << ' ' << current->getIDAccgive() << ' ';
        file << current->getMoney() << ' ' << current->getNumInstallments() << ' ' << current->getStartTime() << ' ' << current->getEndTime() << ' ' << current->getLastInstallment() << ' ' << current->getIsRegister() << endl;

        current = current->getNext();
    }

    file.close();
    delete[] head;
}
#include "Borrow.h"
#include <fstream>
#include <limits>

int BorrowBase::num = 0;

BorrowBase::BorrowBase(int _IDBank, int _IDClient, int _IDAccget, int _IDAccgive, time_t _endTime, int _money, int _numInstallments)
{
    ID = num++;

    IDBank = _IDBank;
    IDClient = _IDClient;
    IDAccget = _IDAccget;
    IDAccgive = _IDAccgive;
    startTime = time(NULL);
    endTime = _endTime;
    money = _money;
    numInstallments = _numInstallments;

    next = nullptr;
}

BorrowBase::BorrowBase(int _ID) //read from file
{
    num++;

    ifstream file("Borrow.txt");
    for (int i = 0; i <= _ID; ++i)
    {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    file >> ID >> IDBank >> IDClient >> IDAccget >> IDAccgive >> money >> numInstallments >> startTime >> endTime;
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
    money = 0;
    numInstallments = 0;

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

long double BorrowBase::getMoney() const
{
    return money;
}

int BorrowBase::getNumInstallments() const
{
    return numInstallments;
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

void BorrowBase::setEndTime(time_t _endTime)
{
    endTime = _endTime;
}

void BorrowBase::setMoney(long double _money)
{
    money = _money;
}

void BorrowBase::setNumInstallments(int _numInstallments)
{
    numInstallments = _numInstallments;
}

void BorrowBase::setNext(BorrowBase *_next)
{
    next = _next;
}

Borrow::Borrow()
{
    head = nullptr;
    last = nullptr;

    ifstream file("Borrow.txt");
    int count;
    file >> count;
    file.close();

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

    file.close();
}

Borrow::Borrow(BorrowBase *_head)
{
    head = _head;

    last = _head;
    while (last->getNext() != nullptr)
        last = last->getNext();
}

void Borrow::add(int _IDBank, int _IDClient, int _IDAccget, int _IDAccgive, time_t _endTime, int _money, int _numInstallments)
{
    BorrowBase *node = new BorrowBase(_IDBank, _IDClient, _IDAccget, _IDAccgive, _endTime, _money, _numInstallments);

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
        file << current->getMoney() << ' ' << current->getNumInstallments() << ' ' << current->getStartTime() << ' ' << current->getEndTime() << endl;

        current = current->getNext();
    }

    file.close();
    delete[] head;
}
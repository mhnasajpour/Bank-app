#include "Bank.cpp"
#include "Manager.cpp"
#include "Client.cpp"
#include "Account.cpp"
#include "Borrow.cpp"
#include "Date.cpp"
#include "Logo.cpp"
#include <thread>
#include <chrono>

Bank bank;
Manager manager;
Client client;
Account account(&client);
Borrow borrow(&account, &client);

void enter();
void login();
void signUp();

void managerPanel(int _ID);
void showProfile(ManagerBase *manager);
void showAccount();
void managementAccounts(int _ID);
void addAccount(int _IDBank, int _IDManager);
void showBorrowsManager(int _ID);
void managementBorrows(int _ID);
void addBorrow(int _ID);

void clientPanel(int _ID);
void showProfile(ClientBase *client);
void showAccount(int _IDClient);
void moveBalance(ClientBase *client);
void request_createAccount(ClientBase *client);
void showBorrowsClient(int _IDClient);
void request_getBorrow(ClientBase *client);

void bankPanel(int _ID);

int main()
{
    logo();
    enter();
    return 0;
}

void enter()
{
    system("clear");
    cout << "\n\n\n\t1 => Login\n\n\t2 => SignUp\n\n\t3 => Exit\n\n\tInput: ";

    int _part;
    do
    {
        cout << '\t';
        cin >> _part;
    } while (_part < 1 || _part > 3);

    switch (_part)
    {
    case 1:
        login();
        break;
    case 2:
        signUp();
        break;
    case 3:
        exit(0);
    }
}

void login()
{
    while (1)
    {
        system("clear");
        cout << "\n\n\n\t1 => Client"
             << "\n\n\t2 => Employees\n\n\t3 => Central Bank\n\n\tInput: ";
        int _part;
        do
        {
            cout << '\t';
            cin >> _part;
        } while (_part < 1 || _part > 3);

        system("clear");
        string _username, _password;
        cout << "\n\n\n\tUsername: ";
        cin >> _username;
        cout << "\n\n\n\tPassword: ";
        cin >> _password;

        switch (_part)
        {
        case 1:
            for (int i = 0; i < ClientBase::getNum(); i++)
                if (client[i]->getUsername() == _username && client[i]->getPassword() == _password)
                    clientPanel(i);

            break;
        case 2:
            for (int i = 0; i < ManagerBase::getNum(); i++)
                if (manager[i]->getUsername() == _username && manager[i]->getPassword() == _password)
                    managerPanel(i);

            break;
        case 3:
            for (int i = 0; i < BankBase::getNum(); i++)
                if (bank[i]->getUsername() == _username && bank[i]->getPassword() == _password)
                    bankPanel(i);

            break;
        }
        cout << "\n\n\n\tThis username is no exist. Maybe password or username is incorrect..." << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
    }
}

void signUp()
{
    while (1)
    {
        bool b = false;
        system("clear");
        string _username, _password;
        cout << "\n\n\n\twelcome to this panel...\n\tYou can input your username and password then sign up:\n\tBank => Manager\n\tManager => Client" << endl;

        cout << "\n\n\n\tUsername: ";
        cin >> _username;

        cout << "\n\n\n\tPassword: ";
        cin >> _password;

        for (int i = 0; i < ManagerBase::getNum(); i++)
            if (manager[i]->getUsername() == _username && manager[i]->getPassword() == _password)
            {
                string _firstName, _lastName, _nationalCode, _username, _password;
                int _day, _month, _year;
                system("clear");
                cout << "\n\n\tThis panel is for client signUp" << endl;

                cout << "\n\n\tFirst name: ";
                cin.ignore(1);
                getline(cin, _firstName);

                cout << "\n\tLast name: ";
                getline(cin, _lastName);

                cout << "\n\tNational code: ";
                cin >> _nationalCode;

                cout << "\n\tbirthDate(\"day month year\"): ";
                cin >> _day >> _month >> _year;

                cout << "\n\n\tUsername: ";
                cin >> _username;

                cout << "\n\tpassword: ";
                cin >> _password;

                client.add(_firstName, _lastName, _nationalCode, _day, _month, _year, _username, _password);

                cout << "\n\tYou signed up successfully..." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));

                int which;
                cout << "\n\n\tIf you want to back menu input (0) else input (1)\n\tInput: ";
                cin >> which;
                if (which == 0)
                    enter();

                else
                {
                    b = true;
                    break;
                }
            }

        for (int i = 0; i < BankBase::getNum(); i++)
            if (bank[i]->getUsername() == _username && bank[i]->getPassword() == _password)
            {
                string _firstName, _lastName, _nationalCode, _username, _password;
                int _day, _month, _year, _salary;
                system("clear");
                cout << "\n\n\tThis panel is for Manager signUp" << endl;

                cout << "\n\n\tFirst name: ";
                cin.ignore(1);
                getline(cin, _firstName);

                cout << "\n\tLast name: ";
                getline(cin, _lastName);

                cout << "\n\tNational code: ";
                cin >> _nationalCode;

                cout << "\n\tbirthDate(\"day month year\"): ";
                cin >> _day >> _month >> _year;

                cout << "\n\tSalary: ";
                cin >> _salary;

                cout << "\n\n\tUsername: ";
                cin >> _username;

                cout << "\n\tpassword: ";
                cin >> _password;

                manager.add(_firstName, _lastName, _nationalCode, _day, _month, _year, _salary, bank[i]->getID(), _username, _password);

                cout << "\n\tYou signed up successfully..." << endl;
                this_thread::sleep_for(chrono::milliseconds(3000));

                int which;
                cout << "\n\n\tIf you want to back menu input (0) else input (1)\n\tInput: ";
                cin >> which;
                if (which == 0)
                    enter();

                else
                {
                    b = true;
                    break;
                }
            }

        if (!b)
        {
            int which;
            cout << "\n\n\n\tYou don't have access to this panel!\n\n\tIf you want to back menu input (0) else input (1)\n\tInput: ";
            cin >> which;
            if (which == 0)
                enter();

            continue;
        }
    }
}

void clientPanel(int _ID)
{
    while (1)
    {
        system("clear");
        cout << "\n\n\t" << client[_ID]->getFirstName() << ' ' << client[_ID]->getLastName();
        cout << "\n\n\t1 => Show profile\n\n\t2 => Show accounts\n\t3 => Move balance\n\t4 => Request create account\n\n\t5 => Show borrows\n\t6 => Request get borrow\n\t7 => Exit\n\n\tINPUT: ";

        int choice;
        do
        {
            cin >> choice;
            if (choice < 1 || choice > 7)
            {
                cout << "\n\n\tYour input is invalid!!!" << endl;
                cout << "\tInput: ";
            }
        } while (choice < 1 || choice > 7);

        switch (choice)
        {
        case 1:
            showProfile(client[_ID]);
            break;
        case 2:
            showAccount(_ID);
            break;
        case 3:
            moveBalance(client[_ID]);
            break;
        case 4:
            request_createAccount(client[_ID]);
            break;
        case 5:
            showBorrowsClient(_ID);
            break;
        case 6:
            request_getBorrow(client[_ID]);
            break;
        default:
            exit(0);
        }
    }
}

void managerPanel(int _ID)
{
    while (1)
    {
        system("clear");
        cout << "\n\n\t" << manager[_ID]->getFirstName() << ' ' << manager[_ID]->getLastName();
        cout << "\n\n\t1 => Show profile\n\n\t2 => Show accounts\n\t3 => Management accounts\n\t4 => Add account\n\n\t5 => Show borrows\n\t6 => Management borrows\n\t7 => Add borrow\n\n\t8 => Exit\n\n\tINPUT: ";

        int choice;
        do
        {
            cin >> choice;
            if (choice < 1 || choice > 8)
            {
                cout << "\n\n\tYour input is invalid!!!" << endl;
                cout << "\tInput: ";
            }
        } while (choice < 1 || choice > 8);

        switch (choice)
        {
        case 1:
            showProfile(manager[_ID]);
            break;
        case 2:
            showAccount();
            break;
        case 3:
            managementAccounts(manager[_ID]->getIDBank());
            break;
        case 4:
            addAccount(manager[_ID]->getIDBank(), _ID);
            break;
        case 5:
            showBorrowsManager(manager[_ID]->getIDBank());
            break;
        case 6:
            managementBorrows(manager[_ID]->getIDBank());
            break;
        case 7:
            addBorrow(manager[_ID]->getIDBank());
            break;
        default:
            exit(0);
        }
    }
}

void bankPanel(int _ID)
{
    system("clear");
    cout << 3;
}

void showProfile(ClientBase *client)
{
    system("clear");
    cout << "\n\n\tFirst name: " << client->getFirstName() << "\n\tLast name: " << client->getLastName() << endl;
    cout << "\n\tNational code: " << client->getNationalCode() << endl;
    cout << "\tBirth date: " << client->getBirthDate().getYear() << '/';
    cout << client->getBirthDate().getMonth() << '/';
    cout << client->getBirthDate().getDay() << endl;
    cout << "\n\tMany Accounts: " << client->getSizeAcc();
    cout << "\n\tMany Borrows: " << client->getSizeBorrow();
    cout << "\n\tMany request for creat Account : " << client->getSizeRequestAcc();
    cout << "\n\tMany request for get Borrow: " << client->getSizeRequestBorrow();
    cout << "\n\n\tAccounts balance: " << client->getBalanceAll();
    cout << "\n\n\tUsername: " << client->getUsername();
    cout << "\n\tPassword: " << client->getPassword() << endl;
    cout << "\n\n\n\tPress any key to continue..." << endl;
    getchar();
    getchar();
}

void showProfile(ManagerBase *manager)
{
    system("clear");
    cout << "\n\n\tFirst name: " << manager->getFirstName() << "\n\tLast name: " << manager->getLastName() << endl;
    cout << "\n\tNational code: " << manager->getNationalCode() << endl;
    cout << "\tBirth date: " << manager->getBirthDate().getYear() << '/';
    cout << manager->getBirthDate().getMonth() << '/';
    cout << manager->getBirthDate().getDay() << endl;
    cout << "\n\tSalary: " << manager->getSalary() << endl;
    cout << "\n\n\tUsername: " << manager->getUsername();
    cout << "\n\tPassword: " << manager->getPassword() << endl;
    cout << "\n\n\n\tPress any key to continue..." << endl;
    getchar();
    getchar();
}

void showAccount(int _IDClient)
{
    system("clear");
    cout << "\n\n\t1 => Get ID account\n\t2 => Show all accounts\n\n\tINPUT: ";

    int choice;
    do
    {
        cin >> choice;
        if (choice < 1 || choice > 2)
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
            cout << "\tInput: ";
        }
    } while (choice < 1 || choice > 2);

    if (choice == 1)
    {
        cout << "\n\n\tID Account: ";
        cin >> choice;

        if (choice < 0 || choice >= AccountBase::getNum())
            cout << "\n\tThis account does not exist!" << endl;

        else if (account[choice]->getIDClient() != _IDClient)
            cout << "\n\tThis account does not belong to you!" << endl;

        else
        {
            cout << "\n\n\t---------------------------------------------------------" << endl;
            switch (account[choice]->getIsRegister())
            {
            case 1:
                cout << "\t\tNot accepted yet\n"
                     << endl;
                break;
            case 2:
                if (account[choice]->getIsBlock())
                    cout << "\t\tIs blocked!!!\n"
                         << endl;
                break;
            case 3:
                cout << "\t\tWas Rejected\n"
                     << endl;
                break;
            }
            cout << "\t\tID: " << account[choice]->getID() << endl;
            cout << "\t\tType: " << account[choice]->getType() << endl;
            cout << "\t\tName bank: " << bank[account[choice]->getIDBank()]->getName() << '(' << bank[account[choice]->getIDBank()]->getBranch() << ')' << endl;
            time_t t = account[choice]->getOpenDate();
            struct tm *i = localtime(&t);
            cout << "\n\t\tOpen date: " << asctime(i);
            t = account[choice]->getExpDate();
            i = localtime(&t);
            cout << "\t\tExp date: " << asctime(i) << endl;
            cout << "\n\t\tBalance: " << account[choice]->getBalance();
            cout << "\n\t---------------------------------------------------------" << endl;
        }
    }

    else if (choice == 2)
    {
        for (int i = 0; i < client[_IDClient]->getSizeAcc(); i++)
        {
            int index = client[_IDClient]->getIDAccount()[i];
            cout << "\n\n\t---------------------------------------------------------" << endl;
            if (account[index]->getIsBlock())
                cout << "\t\tIs blocked!!!\n\n";

            cout << "\t\tID: " << account[index]->getID() << endl;
            cout << "\t\tType: " << account[index]->getType() << endl;
            cout << "\t\tName bank: " << bank[account[index]->getIDBank()]->getName() << '(' << bank[account[index]->getIDBank()]->getBranch() << ')' << endl;

            time_t t = account[index]->getOpenDate();
            struct tm *k = localtime(&t);
            cout << "\n\t\tOpen date: " << asctime(k);

            t = account[index]->getExpDate();
            k = localtime(&t);
            cout << "\t\tExp date: " << asctime(k) << endl;

            cout << "\n\t\tBalance: " << account[index]->getBalance();
            cout << "\n\t---------------------------------------------------------" << endl;
        }
    }
    cout << "\n\n\n\n\tPress any key to continue..." << endl;
    getchar();
    getchar();
}

void showAccount()
{
    system("clear");
    cout << "\n\n\t1 => Get ID account\n\t2 => Show all accounts\n\n\tINPUT: ";

    int choice;
    do
    {
        cin >> choice;
        if (choice < 1 || choice > 2)
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
            cout << "\tInput: ";
        }
    } while (choice < 1 || choice > 2);

    if (choice == 1)
    {
        cout << "\n\n\tID Account: ";
        cin >> choice;

        if (choice < 0 || choice >= AccountBase::getNum())
            cout << "\n\tThis account does not exist!" << endl;

        else
        {
            cout << "\n\n\t---------------------------------------------------------" << endl;
            switch (account[choice]->getIsRegister())
            {
            case 1:
                cout << "\t\tNot accepted yet\n"
                     << endl;
                break;
            case 2:
                if (account[choice]->getIsBlock())
                    cout << "\t\tIs blocked!!!\n"
                         << endl;
                break;
            case 3:
                cout << "\t\tWas Rejected\n"
                     << endl;
                break;
            }
            cout << "\t\tID: " << account[choice]->getID() << endl;
            cout << "\t\tType: " << account[choice]->getType() << endl;
            cout << "\t\tName bank: " << bank[account[choice]->getIDBank()]->getName() << '(' << bank[account[choice]->getIDBank()]->getBranch() << ')' << endl;

            cout << "\n\t\tFirst name: " << client[account[choice]->getIDClient()]->getFirstName() << endl;
            cout << "\t\tLast name: " << client[account[choice]->getIDClient()]->getLastName() << endl;
            cout << "\t\tNational code: " << client[account[choice]->getIDClient()]->getNationalCode() << endl;
            cout << "\t\tBirthDate: " << client[account[choice]->getIDClient()]->getBirthDate().getYear() << '/';
            cout << client[account[choice]->getIDClient()]->getBirthDate().getMonth() << '/';
            cout << client[account[choice]->getIDClient()]->getBirthDate().getDay() << endl;

            time_t t = account[choice]->getOpenDate();
            struct tm *i = localtime(&t);
            cout << "\n\t\tOpen date: " << asctime(i);
            t = account[choice]->getExpDate();
            i = localtime(&t);
            cout << "\t\tExp date: " << asctime(i) << endl;
            cout << "\n\t\tBalance: " << account[choice]->getBalance();
            cout << "\n\t---------------------------------------------------------" << endl;
        }
    }

    if (choice == 2)
    {
        cout << "\n\n\tNational code: ";
        string _nationalCode;
        cin >> _nationalCode;

        int _IDClient = -1;
        for (int i = 0; i < ClientBase::getNum(); i++)
            if (client[i]->getNationalCode() == _nationalCode)
                _IDClient = client[i]->getID();

        if (_IDClient == -1)
            cout << "\n\tThis user does not exist!" << endl;

        else
        {
            for (int i = 0; i < client[_IDClient]->getSizeAcc(); i++)
            {
                int index = client[_IDClient]->getIDAccount()[i];
                cout << "\n\n\t---------------------------------------------------------" << endl;
                if (account[choice]->getIsBlock())
                    cout << "\t\tIs blocked!!!\n\n";

                cout << "\t\tID: " << account[index]->getID() << endl;
                cout << "\t\tType: " << account[index]->getType() << endl;
                cout << "\t\tName bank: " << bank[account[index]->getIDBank()]->getName() << '(' << bank[account[index]->getIDBank()]->getBranch() << ')' << endl;

                cout << "\n\t\tFirst name: " << client[account[index]->getIDClient()]->getFirstName() << endl;
                cout << "\t\tLast name: " << client[account[index]->getIDClient()]->getLastName() << endl;
                cout << "\t\tNational code: " << client[account[index]->getIDClient()]->getNationalCode() << endl;
                cout << "\t\tBirthDate: " << client[account[index]->getIDClient()]->getBirthDate().getYear() << '/';
                cout << client[account[index]->getIDClient()]->getBirthDate().getMonth() << '/';
                cout << client[account[index]->getIDClient()]->getBirthDate().getDay() << endl;

                time_t t = account[index]->getOpenDate();
                struct tm *k = localtime(&t);
                cout << "\n\t\tOpen date: " << asctime(k);

                t = account[index]->getExpDate();
                k = localtime(&t);
                cout << "\t\tExp date: " << asctime(k) << endl;

                cout << "\n\t\tBalance: " << account[index]->getBalance();
                cout << "\n\t---------------------------------------------------------" << endl;
            }
        }
    }
    cout << "\n\n\n\n\tPress any key to continue..." << endl;
    getchar();
    getchar();
}

void request_createAccount(ClientBase *client)
{
    system("clear");
    cout << "\n\n\tInput account information to request it" << endl;
    int _type, _IDBank, _balance;
    cout << "\n\n\tType 1: 6 months with 10% profit\n\tType 2: 1 year with 30% profit\n\tType 3: 3 years with 50% profit\n\tType ?: ";

    do
    {
        cin >> _type;
        if (_type < 1 || _type > 3)
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
            cout << "\tInput: ";
        }
    } while (_type < 1 || _type > 3);

    cout << "\n\n";
    for (int i = 0; i < BankBase::getNum(); i++)
        cout << "\t" << i << " => " << bank[i]->getName() << endl;

    do
    {
        cout << "\tInput: ";
        cin >> _IDBank;
        if (_IDBank < 0 || _IDBank >= BankBase::getNum())
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
        }
    } while (_IDBank < 0 || _IDBank >= BankBase::getNum());

    cout << "\n\n\n\tRequest Balance: ";
    cin >> _balance;

    account.add(_type, _IDBank, client->getID(), _balance);
    client->addIDRequestAccount(AccountBase::getNum() - 1);
    bank[_IDBank]->addIDRequestAccount(AccountBase::getNum() - 1);

    cout << "\n\n\tYour requestAccount ID: " << AccountBase::getNum() - 1 << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
}

void moveBalance(ClientBase *_client)
{
    int _balance, _yourIDAccount, _hisIDAccount;
    while (1)
    {
        system("clear");
        cout << "\n\n\tAmount of money you want to transfer: ";
        cin >> _balance;

        cout << "\n\n";
        for (int i = 0; i < _client->getSizeAcc(); i++)
            cout << "\t" << i << " => " << _client->getIDAccount()[i] << endl;

        cout << "\n";
        do
        {
            cout << "\n\tOrigin IDAccount: ";
            cin >> _yourIDAccount;
            if (_yourIDAccount < 0 || _yourIDAccount >= _client->getSizeAcc() || account[_client->getIDAccount()[_yourIDAccount]]->getIsRegister() != 2)
            {
                cout << "\n\tYour input is invalid!!!" << endl;
            }
            else if (account[_client->getIDAccount()[_yourIDAccount]]->getIsBlock())
            {
                cout << "\n\tThis account is blocked!!!" << endl;
            }
        } while (_yourIDAccount < 0 || _yourIDAccount >= _client->getSizeAcc() || account[_client->getIDAccount()[_yourIDAccount]]->getIsRegister() != 2 || account[_client->getIDAccount()[_yourIDAccount]]->getIsBlock());

        if (account[_client->getIDAccount()[_yourIDAccount]]->getBalance() < _balance)
        {
            cout << "\n\n\tYour Account does not have enough balance!!!" << endl;
            cout << "\n\tIf you want to select account again press 0 else if you want to back menu press 1 ..." << endl;
            int garbage;
            cin >> garbage;
            if (garbage == 0)
                continue;
            else
                return;
        }

        cout << "\n";
        do
        {
            cout << "\n\tDestination IDAccount: ";
            cin >> _hisIDAccount;
            if (_hisIDAccount < 0 || _hisIDAccount >= AccountBase::getNum() || account[_hisIDAccount]->getIsRegister() != 2)
            {
                cout << "\n\tYour input is invalid!!!" << endl;
            }
            else if (account[_hisIDAccount]->getIsBlock())
            {
                cout << "\n\tThis account is blocked!!!" << endl;
            }
        } while (_hisIDAccount < 0 || _hisIDAccount >= AccountBase::getNum() || account[_hisIDAccount]->getIsRegister() != 2 || account[_hisIDAccount]->getIsBlock());
    }

    account[_hisIDAccount]->setBalance(_balance);
    client[account[_hisIDAccount]->getID()]->setBalanceAll(_balance);
    account[_client->getIDAccount()[_yourIDAccount]]->setBalance(-(_balance));
    _client->setBalanceAll(-(_balance));

    cout << "\n\n\n\tYour transfer done successfully" << endl;
    this_thread::sleep_for(chrono::milliseconds(4000));
}

void showBorrowsClient(int _IDClient)
{
    system("clear");
    cout << "\n\n\t1 => Get ID Borrow\n\t2 => Show all Borrows\n\n\tINPUT: ";

    int choice;
    do
    {
        cin >> choice;
        if (choice < 1 || choice > 2)
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
            cout << "\tInput: ";
        }
    } while (choice < 1 || choice > 2);

    if (choice == 1)
    {
        cout << "\n\n\tID Borrow: ";
        cin >> choice;

        if (choice < 0 || choice >= BorrowBase::getNum())
            cout << "\n\tThis Borrow does not exist!" << endl;

        else if (borrow[choice]->getIDClient() != _IDClient)
            cout << "\n\tThis Borrow does not belong to you!" << endl;

        else
        {
            cout << "\n\n\t---------------------------------------------------------" << endl;
            switch (borrow[choice]->getIsRegister())
            {
            case 1:
                cout << "\t\tNot accepted yet\n"
                     << endl;
                break;
            case 2:
                break;
            case 3:
                cout << "\t\tWas Rejected\n"
                     << endl;
                break;
            }
            cout << "\t\tID: " << borrow[choice]->getID() << endl;
            cout << "\t\tName bank: " << bank[borrow[choice]->getIDBank()]->getName() << '(' << bank[borrow[choice]->getIDBank()]->getBranch() << ')' << endl;
            time_t t = borrow[choice]->getStartTime();
            struct tm *i = localtime(&t);
            cout << "\n\t\tStart time: " << asctime(i);
            t = borrow[choice]->getEndTime();
            i = localtime(&t);
            cout << "\t\tEnd time: " << asctime(i) << endl;
            cout << "\n\t\tDecreas from account with ID: " << borrow[choice]->getIDAccgive() << endl;
            cout << "\n\t\tInstallments: " << borrow[choice]->getNumInstallments() << endl;
            cout << "\t\tMoney: " << borrow[choice]->getMoney();
            cout << "\n\t---------------------------------------------------------" << endl;
        }
    }

    if (choice == 2)
    {
        for (int i = 0; i < client[_IDClient]->getSizeBorrow(); i++)
        {
            int index = client[_IDClient]->getIDBorrow()[i];
            cout << "\n\n\t---------------------------------------------------------" << endl;
            cout << "\t\tID: " << borrow[index]->getID() << endl;
            cout << "\t\tName bank: " << bank[borrow[index]->getIDBank()]->getName() << '(' << bank[borrow[index]->getIDBank()]->getBranch() << ')' << endl;
            time_t t = borrow[index]->getStartTime();
            struct tm *j = localtime(&t);
            cout << "\n\t\tStart time: " << asctime(j);
            t = borrow[index]->getEndTime();
            j = localtime(&t);
            cout << "\t\tEnd time: " << asctime(j) << endl;
            cout << "\n\t\tDecreas from account with ID: " << borrow[index]->getIDAccgive() << endl;
            cout << "\n\t\tInstallments: " << borrow[index]->getNumInstallments() << endl;
            cout << "\t\tMoney: " << borrow[index]->getMoney();
            cout << "\n\t---------------------------------------------------------" << endl;
        }
    }
    cout << "\n\n\n\n\tPress any key to continue..." << endl;
    getchar();
    getchar();
}

void request_getBorrow(ClientBase *_client)
{
    system("clear");
    int _IDAccget, _IDAccgive, _money, _numInstallments;
    cout << "\n\n\tInput Borrow information to request it" << endl;

    for (int i = 0; i < _client->getSizeAcc(); i++)
        cout << "\t" << i << " => " << bank[i]->getName() << "    ID: " << account[_client->getIDAccount()[i]]->getID() << endl;

    cout << "\n\n";
    do
    {
        cout << "\tThe account you want to deposit to it: ";
        cin >> _IDAccget;
        if (_IDAccget < 0 || _IDAccget >= _client->getSizeAcc() || account[_client->getIDAccount()[_IDAccget]]->getIsRegister() != 2)
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
        }
    } while (_IDAccget < 0 || _IDAccget >= _client->getSizeAcc() || account[_client->getIDAccount()[_IDAccget]]->getIsRegister() != 2);

    int _IDBank = account[_client->getIDAccount()[_IDAccget]]->getIDBank();
    for (int i = 0; i < _client->getSizeBorrow(); i++)
        if (_IDBank == borrow[_client->getIDBorrow()[i]]->getIDBank())
        {
            cout << "You have already borrowed from this bank..." << endl;
            this_thread::sleep_for(chrono::milliseconds(4000));
        }

    cout << "\n\n";
    do
    {
        cout << "\tThe account you want to pay from: ";
        cin >> _IDAccgive;
        if (_IDAccgive < 0 || _IDAccgive >= _client->getSizeAcc() || account[_client->getIDAccount()[_IDAccgive]]->getIsRegister() != 2)
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
        }
    } while (_IDAccgive < 0 || _IDAccgive >= _client->getSizeAcc() || account[_client->getIDAccount()[_IDAccgive]]->getIsRegister() != 2);

    cout << "\n\n\n\tMoney: ";
    cin >> _money;

    cout << "\n\n\tNumInstallments: ";
    cin >> _numInstallments;

    borrow.add(_IDBank, _client->getID(), _client->getIDAccount()[_IDAccget], _client->getIDAccount()[_IDAccgive], _money, _numInstallments);
    _client->addIDRequestBorrow(BorrowBase::getNum() - 1);
    bank[_IDBank]->addIDRequestBorrow(BorrowBase::getNum() - 1);

    cout << "\n\n\tYour requestBorrow ID: " << BorrowBase::getNum() - 1 << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
}

void addAccount(int _IDBank, int _IDManager)
{
    while (1)
    {
        system("clear");
        for (int i = 0; i < bank[_IDBank]->getSizeRequestAccount(); i++)
        {
            int index = bank[_IDBank]->getIDRequestAccount()[i];
            cout << "\n\n\t---------------------------------------------------------" << endl;

            cout << "\t\tID: " << account[index]->getID() << endl;
            cout << "\t\tType: " << account[index]->getType() << endl;
            cout << "\t\tName bank: " << bank[account[index]->getIDBank()]->getName() << '(' << bank[account[index]->getIDBank()]->getBranch() << ')' << endl;

            cout << "\n\t\tFirst name: " << client[account[index]->getIDClient()]->getFirstName() << endl;
            cout << "\t\tLast name: " << client[account[index]->getIDClient()]->getLastName() << endl;
            cout << "\t\tNational code: " << client[account[index]->getIDClient()]->getNationalCode() << endl;
            cout << "\t\tBirthDate: " << client[account[index]->getIDClient()]->getBirthDate().getYear() << '/';
            cout << client[account[index]->getIDClient()]->getBirthDate().getMonth() << '/';
            cout << client[account[index]->getIDClient()]->getBirthDate().getDay() << endl;

            cout << "\n\t\tBalance: " << account[index]->getBalance();
            cout << "\n\t---------------------------------------------------------" << endl;
        }

        int input;
        cout << "\n\n\tInput ID requested account: ";
        cin >> input;
        if (input < 0 || input >= AccountBase::getNum())
            cout << "\tInvalid input..." << endl;

        else if (account[input]->getIDBank() != manager[_IDManager]->getIDBank())
            cout << "\n\tThis account does not exist!!!" << endl;

        else if (account[input]->getIsRegister() == 1)
        {
            int s;
            cout << "\n\t1 => Accept    2 => Reject" << endl;
            do
            {
                cout << "\n\tINPUT: ";
                cin >> s;
                if (s != 1 && s != 2)
                    cout << "\tInvalid input";
            } while (s != 1 && s != 2);

            if (s == 1)
            {
                account[input]->setIsRegister(2);
                bank[_IDBank]->removeIDRequestAccount(input);
                bank[_IDBank]->addIDAccount(input);
                client[account[input]->getIDClient()]->removeIDRequestAccount(input);
                client[account[input]->getIDClient()]->addIDAccount(input);
                cout << "\n\tYou accepted this account succussfully" << endl;
            }
            else
            {
                account[input]->setIsRegister(3);
                bank[_IDBank]->removeIDRequestAccount(input);
                client[account[input]->getIDClient()]->removeIDRequestAccount(input);
                cout << "\n\tYou rejected this account succussfully" << endl;
            }
        }
        else if (account[input]->getIsRegister() == 2)
            cout << "\n\tThis account is already registered...";

        else if (account[input]->getIsRegister() == 3)
            cout << "\n\tThis account is already rejected...";

        else
            cout << "\n\tThis account is already rejected...";

        cout << "\n\tIf you want to select account again press 0 else if you want to back menu press 1:  ";
        int garbage;
        cin >> garbage;
        if (garbage == 0)
            continue;
        else
            return;
    }
}

void managementAccounts(int _ID)
{
    while (1)
    {
        system("clear");
        cout << "\n\n\t1 => get ID Account\t2 => get national code and show all accounts" << endl;

        cout << "\n";
        int input;
        do
        {
            cout << "\n\tINPUT: ";
            cin >> input;
            if (input != 1 && input != 2)
            {
                cout << "\n\tYour input is invalid!!!" << endl;
            }
        } while (input != 1 && input != 2);

        if (input == 1)
        {
            cout << "\n\n\tID Account: ";
            do
            {
                cout << "\n\tINPUT: ";
                cin >> input;
                if (input < 0 || input >= AccountBase::getNum())
                {
                    cout << "\n\tYour input is invalid!!!" << endl;
                }
            } while (input < 0 || input >= AccountBase::getNum());

            if (account[input]->getIsBlock())
                cout << "\n\n\tThis account is block" << endl;

            else if (account[input]->getIsRegister() != 2)
                cout << "\n\n\tThis account is not exist" << endl;

            else if (account[input]->getIDBank() != _ID)
                cout << "\n\n\tThis account does not belong to this bank" << endl;

            else
            {
                int balance;
                cout << "\n\n\tBalance: ";
                cin >> balance;

                if (account[input]->getBalance() + balance < 0)
                {
                    cout << "\n\n\tYou cant to transfer this money\tAccount balance: " << account[input]->getBalance() << endl;
                    cout << "\n\tIf you want to select account again press 0 else if you want to back menu press 1 ..." << endl;
                    int garbage;
                    cin >> garbage;
                    if (garbage == 0)
                        continue;
                    else
                        return;
                }

                account[input]->setBalance(balance);
                client[account[input]->getIDClient()]->setBalanceAll(balance);
                cout << "\n\n\n\tYour transfer done successfully\n"
                     << endl;
            }
        }

        else
        {
            cout << "\n\n\tNational code: ";
            string _nationalCode;
            cin >> _nationalCode;

            int _IDClient = -1;
            for (int i = 0; i < ClientBase::getNum(); i++)
                if (client[i]->getNationalCode() == _nationalCode)
                    _IDClient = client[i]->getID();

            if (_IDClient == -1)
                cout << "\n\tThis user does not exist!" << endl;

            else
            {
                for (int i = 0; i < client[_IDClient]->getSizeAcc(); i++)
                {
                    int index = client[_IDClient]->getIDAccount()[i];
                    cout << "\n\n\t---------------------------------------------------------" << endl;
                    if (account[index]->getIsBlock())
                        cout << "\t\tIs blocked!!!\n\n";

                    cout << "\t\tID: " << account[index]->getID() << endl;
                    cout << "\t\tType: " << account[index]->getType() << endl;
                    cout << "\t\tName bank: " << bank[account[index]->getIDBank()]->getName() << '(' << bank[account[index]->getIDBank()]->getBranch() << ')' << endl;

                    cout << "\n\t\tFirst name: " << client[account[index]->getIDClient()]->getFirstName() << endl;
                    cout << "\t\tLast name: " << client[account[index]->getIDClient()]->getLastName() << endl;
                    cout << "\t\tNational code: " << client[account[index]->getIDClient()]->getNationalCode() << endl;
                    cout << "\t\tBirthDate: " << client[account[index]->getIDClient()]->getBirthDate().getYear() << '/';
                    cout << client[account[index]->getIDClient()]->getBirthDate().getMonth() << '/';
                    cout << client[account[index]->getIDClient()]->getBirthDate().getDay() << endl;

                    time_t t = account[index]->getOpenDate();
                    struct tm *k = localtime(&t);
                    cout << "\n\t\tOpen date: " << asctime(k);

                    t = account[index]->getExpDate();
                    k = localtime(&t);
                    cout << "\t\tExp date: " << asctime(k) << endl;

                    cout << "\n\t\tBalance: " << account[index]->getBalance();
                    cout << "\n\t---------------------------------------------------------" << endl;
                }

                cout << "\n\n\tID Account: ";
                do
                {
                    cout << "\n\tINPUT: ";
                    cin >> input;
                    if (input < 0 || input >= AccountBase::getNum())
                    {
                        cout << "\n\tYour input is invalid!!!" << endl;
                    }
                } while (input < 0 || input >= AccountBase::getNum());

                if (account[input]->getIsBlock())
                    cout << "\n\n\tThis account is block" << endl;

                else if (account[input]->getIsRegister() != 2)
                    cout << "\n\n\tThis account is not exist" << endl;

                else if (account[input]->getIDBank() != _ID)
                    cout << "\n\n\tThis account does not belong to this bank" << endl;

                else
                {
                    int balance;
                    cout << "\n\n\tBalance: ";
                    cin >> balance;

                    if (account[input]->getBalance() + balance < 0)
                        cout << "\n\n\tYou cant to transfer this money\tAccount balance: " << account[input]->getBalance() << endl;

                    account[input]->setBalance(balance);
                    client[account[input]->getIDClient()]->setBalanceAll(balance);
                    cout << "\n\n\n\tYour transfer done successfully\n"
                         << endl;
                }
            }
        }
        cout << "\n\tIf you want to select account again press 0 else if you want to back menu press 1 ..." << endl;
        int garbage;
        cin >> garbage;
        if (garbage == 0)
            continue;
        else
            return;
    }
}

void showBorrowsManager(int _ID)
{
    system("clear");
    cout << "\n\n\t1 => Get ID Borrow\n\t2 => Show all Borrows\n\n\tINPUT: ";

    int choice;
    do
    {
        cin >> choice;
        if (choice < 1 || choice > 2)
        {
            cout << "\n\n\tYour input is invalid!!!" << endl;
            cout << "\tInput: ";
        }
    } while (choice < 1 || choice > 2);

    if (choice == 1)
    {
        cout << "\n\n\tID Borrow: ";
        cin >> choice;

        if (choice < 0 || choice >= BorrowBase::getNum())
            cout << "\n\tThis Borrow does not exist!" << endl;

        else if (borrow[choice]->getIDBank() != _ID)
            cout << "\n\tThis Borrow does not belong to you!" << endl;

        else
        {
            cout << "\n\n\t---------------------------------------------------------" << endl;
            switch (borrow[choice]->getIsRegister())
            {
            case 1:
                cout << "\t\tNot accepted yet\n"
                     << endl;
                break;
            case 2:
                if ((time(NULL) - borrow[choice]->getLastInstallment()) / 2628000 > 0)
                    cout << "\t\tDelayed\n"
                         << endl;
                break;
            case 3:
                cout << "\t\tWas Rejected\n"
                     << endl;
                break;
            }
            cout << "\t\tID: " << borrow[choice]->getID() << endl;
            cout << "\t\tName bank: " << bank[borrow[choice]->getIDBank()]->getName() << '(' << bank[borrow[choice]->getIDBank()]->getBranch() << ')' << endl;

            cout << "\n\t\tFirst name: " << client[borrow[choice]->getIDClient()]->getFirstName() << endl;
            cout << "\t\tLast name: " << client[borrow[choice]->getIDClient()]->getLastName() << endl;
            cout << "\t\tNational code: " << client[borrow[choice]->getIDClient()]->getNationalCode() << endl;
            cout << "\t\tBirthDate: " << client[borrow[choice]->getIDClient()]->getBirthDate().getYear() << '/';
            cout << client[borrow[choice]->getIDClient()]->getBirthDate().getMonth() << '/';
            cout << client[borrow[choice]->getIDClient()]->getBirthDate().getDay() << endl;

            time_t t = borrow[choice]->getStartTime();
            struct tm *i = localtime(&t);
            cout << "\n\t\tStart time: " << asctime(i);
            t = borrow[choice]->getEndTime();
            i = localtime(&t);
            cout << "\t\tEnd time: " << asctime(i) << endl;
            cout << "\n\t\tDecreas from account with ID: " << borrow[choice]->getIDAccgive() << endl;
            cout << "\n\t\tInstallments: " << borrow[choice]->getNumInstallments() << endl;
            cout << "\t\tMoney: " << borrow[choice]->getMoney();
            cout << "\n\t---------------------------------------------------------" << endl;
        }
    }

    if (choice == 2)
    {
        for (int i = 0; i < bank[_ID]->getSizeBorrow(); i++)
        {
            int index = bank[_ID]->getIDBorrow()[i];
            cout << "\n\n\t---------------------------------------------------------" << endl;
            cout << "\t\tID: " << borrow[index]->getID() << endl;
            cout << "\t\tName bank: " << bank[borrow[index]->getIDBank()]->getName() << '(' << bank[borrow[index]->getIDBank()]->getBranch() << ')' << endl;

            cout << "\n\t\tFirst name: " << client[borrow[choice]->getIDClient()]->getFirstName() << endl;
            cout << "\t\tLast name: " << client[borrow[choice]->getIDClient()]->getLastName() << endl;
            cout << "\t\tNational code: " << client[borrow[choice]->getIDClient()]->getNationalCode() << endl;
            cout << "\t\tBirthDate: " << client[borrow[choice]->getIDClient()]->getBirthDate().getYear() << '/';
            cout << client[borrow[choice]->getIDClient()]->getBirthDate().getMonth() << '/';
            cout << client[borrow[choice]->getIDClient()]->getBirthDate().getDay() << endl;

            time_t t = borrow[index]->getStartTime();
            struct tm *j = localtime(&t);
            cout << "\n\t\tStart time: " << asctime(j);
            t = borrow[index]->getEndTime();
            j = localtime(&t);
            cout << "\t\tEnd time: " << asctime(j) << endl;
            cout << "\n\t\tDecreas from account with ID: " << borrow[index]->getIDAccgive() << endl;
            cout << "\n\t\tInstallments: " << borrow[index]->getNumInstallments() << endl;
            cout << "\t\tMoney: " << borrow[index]->getMoney();
            cout << "\n\t---------------------------------------------------------" << endl;
        }
    }
    cout << "\n\n\n\n\tPress any key to continue..." << endl;
    getchar();
    getchar();
}

void addBorrow(int _ID)
{
    while (1)
    {
        system("clear");
        for (int i = 0; i < bank[_ID]->getSizeRequestBorrow(); i++)
        {
            int index = bank[_ID]->getIDRequestBorrow()[i];

            cout << "\n\n\t---------------------------------------------------------" << endl;
            cout << "\t\tID: " << borrow[index]->getID() << endl;
            cout << "\t\tName bank: " << bank[borrow[index]->getIDBank()]->getName() << '(' << bank[borrow[index]->getIDBank()]->getBranch() << ')' << endl;

            cout << "\n\t\tFirst name: " << client[borrow[index]->getIDClient()]->getFirstName() << endl;
            cout << "\t\tLast name: " << client[borrow[index]->getIDClient()]->getLastName() << endl;
            cout << "\t\tNational code: " << client[borrow[index]->getIDClient()]->getNationalCode() << endl;
            cout << "\t\tBirthDate: " << client[borrow[index]->getIDClient()]->getBirthDate().getYear() << '/';
            cout << client[borrow[index]->getIDClient()]->getBirthDate().getMonth() << '/';
            cout << client[borrow[index]->getIDClient()]->getBirthDate().getDay() << endl;

            time_t t = borrow[index]->getStartTime();
            struct tm *k = localtime(&t);
            cout << "\n\t\tStart time: " << asctime(k);
            t = borrow[index]->getEndTime();
            k = localtime(&t);
            cout << "\t\tEnd time: " << asctime(k) << endl;
            cout << "\n\t\tDecreas from account with ID: " << borrow[index]->getIDAccgive() << endl;
            cout << "\n\t\tInstallments: " << borrow[index]->getNumInstallments() << endl;
            cout << "\t\tMoney: " << borrow[index]->getMoney();
            cout << "\n\t---------------------------------------------------------" << endl;
        }

        int input;
        cout << "\n\n\tInput ID requested Borrow: ";
        cin >> input;
        if (input < 0 || input >= BorrowBase::getNum())
            cout << "\tInvalid input..." << endl;

        else if (borrow[input]->getIDBank() != _ID)
            cout << "\n\tThis borrow does not exist!!!" << endl;

        else if (borrow[input]->getIsRegister() == 1)
        {
            int s;
            cout << "\n\t1 => Accept    2 => Reject" << endl;
            do
            {
                cout << "\n\tINPUT: ";
                cin >> s;
                if (s != 1 && s != 2)
                    cout << "\tInvalid input";
            } while (s != 1 && s != 2);

            if (s == 1)
            {
                borrow[input]->setIsRegister(2);
                bank[_ID]->removeIDRequestBorrow(input);
                bank[_ID]->addIDBorrow(input);
                client[borrow[input]->getIDClient()]->removeIDRequestBorrow(input);
                client[borrow[input]->getIDClient()]->addIDBorrow(input);
                cout << "\n\tYou accepted this borrow succussfully" << endl;
            }
            else
            {
                borrow[input]->setIsRegister(3);
                bank[_ID]->removeIDRequestBorrow(input);
                client[borrow[input]->getIDClient()]->removeIDRequestBorrow(input);
                cout << "\n\tYou rejected this borrow succussfully" << endl;
            }
        }
        else if (borrow[input]->getIsRegister() == 2)
            cout << "\n\tThis borrow is already registered...";

        else if (borrow[input]->getIsRegister() == 3)
            cout << "\n\tThis borrow is already rejected...";

        else
            cout << "\n\tThis borrow is already expired...";

        cout << "\n\tIf you want to select account again press 0 else if you want to back menu press 1:  ";
        int garbage;
        cin >> garbage;
        if (garbage == 0)
            continue;
        else
            return;
    }
}

void managementBorrows(int _ID)
{
    while (1)
    {
        system("clear");
        cout << "\n\n\tID Borrow: ";
        int choice;
        cin >> choice;

        if (choice < 0 || choice >= BorrowBase::getNum())
            cout << "\n\tThis Borrow does not exist!" << endl;

        else if (borrow[choice]->getIDBank() != _ID)
            cout << "\n\tThis Borrow does not belong to you!" << endl;

        else
        {
            cout << "\n\n\t---------------------------------------------------------" << endl;
            switch (borrow[choice]->getIsRegister())
            {
            case 1:
                cout << "\t\tNot accepted yet\n"
                     << endl;
                break;
            case 2:
                if ((time(NULL) - borrow[choice]->getLastInstallment()) / 2628000 > 0)
                    cout << "\t\tDelayed\n"
                         << endl;
                break;
            case 3:
                cout << "\t\tWas Rejected\n"
                     << endl;
                break;
            }
            cout << "\t\tID: " << borrow[choice]->getID() << endl;
            cout << "\t\tName bank: " << bank[borrow[choice]->getIDBank()]->getName() << '(' << bank[borrow[choice]->getIDBank()]->getBranch() << ')' << endl;

            cout << "\n\t\tFirst name: " << client[borrow[choice]->getIDClient()]->getFirstName() << endl;
            cout << "\t\tLast name: " << client[borrow[choice]->getIDClient()]->getLastName() << endl;
            cout << "\t\tNational code: " << client[borrow[choice]->getIDClient()]->getNationalCode() << endl;
            cout << "\t\tBirthDate: " << client[borrow[choice]->getIDClient()]->getBirthDate().getYear() << '/';
            cout << client[borrow[choice]->getIDClient()]->getBirthDate().getMonth() << '/';
            cout << client[borrow[choice]->getIDClient()]->getBirthDate().getDay() << endl;

            time_t t = borrow[choice]->getStartTime();
            struct tm *i = localtime(&t);
            cout << "\n\t\tStart time: " << asctime(i);
            t = borrow[choice]->getEndTime();
            i = localtime(&t);
            cout << "\t\tEnd time: " << asctime(i) << endl;
            cout << "\n\t\tDecreas from account with ID: " << borrow[choice]->getIDAccgive() << endl;
            cout << "\n\t\tInstallments: " << borrow[choice]->getNumInstallments() << endl;
            cout << "\t\tMoney: " << borrow[choice]->getMoney();

            int count = (time(NULL) - borrow[choice]->getLastInstallment()) / 2628000;
            cout << "\n\n\t\tDelay borrow: " << borrow[choice]->getMoney() / borrow[choice]->getNumInstallments() * count;
            cout << "\n\t---------------------------------------------------------" << endl;

            int input;
            cout << "\n\n\t1 => Get Borrow\t2 = > Cancel\n";
            do
            {
                cout << "\tInput: ";
                cin >> input;
                if (input < 1 || input > 2)
                {
                    cout << "\n\tYour input is invalid!!!" << endl;
                }
            } while (input < 1 || input > 2);

            if (input == 1)
            {
                if((time(NULL) - borrow[choice]->getLastInstallment()) / 2628000 == 0)
                    cout << "\n\n\tThis account has already paid its debt!!!" << endl;

                else if ((account[borrow[choice]->getIDAccgive()]->getBalance()) >= (borrow[choice]->getMoney() / borrow[choice]->getNumInstallments() * count))
                {
                    borrow.checkBorrows(&account, &client, choice);
                    cout << "\n\n\tYou received all the loans" << endl;
                }
                
                else
                    cout << "\n\n\tThis account does not have enough balance!!!" << endl;
            }
        }

        cout << "\n\tIf you want to select account again press 0 else if you want to back menu press 1:  ";
        int garbage;
        cin >> garbage;
        if (garbage == 0)
            continue;
        else
            return;
    }
}
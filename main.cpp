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
//void showAccount();

void clientPanel(int _ID);
void showProfile(ClientBase *client);
void showAccount(int _IDClient);
void request_createAccount(ClientBase *client);

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
    cout << "\n\n\n\t1 => Login"
         << "\n\n\t2 => SignUp\n\n\tInput: ";
    int _part;

    do
    {
        cout << '\t';
        cin >> _part;
    } while (_part != 1 && _part != 2);

    _part == 1 ? login() : signUp();
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
    bool b = false;
    system("clear");
    string _username, _password;
    cout << "\n\n\n\twelcome to this panel...\n\tYou can input your username and password then sign up:\n\tBank => Manager\n\tManager => Client" << endl;

    cout << "\n\n\n\tUsername: ";
    cin >> _username;

    cout << "\n\n\n\tPassword: ";
    cin >> _password;

    while (1)
    {
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
            cout << "\n\n\n\tYou don't have access to this panel!\n\n\tIf you want to back menu input (0) else input (1)\n\tInput: " << endl;
            cin >> which;
            if (which == 0)
                enter();

            break;
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

            break;
        case 4:
            request_createAccount(client[_ID]);
            break;
        case 5:

            break;
        case 6:

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

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

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
        
        cout << "\n\n\t---------------------------------------------------------" << endl;
        switch (account[choice]->getIsRegister())
        {
        case 1:
            cout << "\t\tNot accepted yet\n" << endl;
            break;
        case 2:
            break;
        case 3:
            cout << "\t\tWas Rejected\n" << endl;
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
        cout << "\n\n\n\n\tPress any key to continue..." << endl;
        getchar();
        getchar();
    }

    if (choice == 2)
    {
        for (int i = 0; i < client[_IDClient]->getSizeAcc(); i++)
        {
            int index = client[_IDClient]->getIDAccount()[i];
            cout << "\n\n\t---------------------------------------------------------" << endl;
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
        cout << "\n\n\n\n\tPress any key to continue..." << endl;
        getchar();
        getchar();
    }
}

void request_createAccount(ClientBase *client)
{
    system("clear");
    cout << "\n\n\tInput account information to request them" << endl;
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
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
void clientPanel(int _ID);
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
    cout << "\n\n\n\t1 => Login" << "\n\n\t2 => SignUp\n\n\tInput: ";
    int _part;

    do {
        cout << '\t';
        cin >> _part;
    } while(_part != 1 && _part != 2);
    
    _part == 1 ? login() : signUp();
}

void login()
{
    while(1){
        system("clear");
        cout << "\n\n\n\t1 => Client" << "\n\n\t2 => Employees\n\n\t3 => Central Bank\n\n\tInput: ";
        int _part;
        do {
            cout << '\t';
            cin >> _part;
        } while(_part < 1 || _part > 3);

        system("clear");
        string _username, _password;
        cout << "\n\n\n\tUsername: ";
        cin >> _username;
        cout << "\n\n\n\tPassword: ";
        cin >> _password;
        
        switch (_part){
        case 1:
            for(int i = 0; i < ClientBase::getNum(); i++)
                if(client[i]->getUsername() == _username && client[i]->getPassword() == _password)
                    clientPanel(i);

            break;
        case 2:
            for(int i = 0; i < ManagerBase::getNum(); i++)
                if(manager[i]->getUsername() == _username && manager[i]->getPassword() == _password)
                    managerPanel(i);
            
            break;
        case 3:
            for(int i = 0; i < BankBase::getNum(); i++)
                if(bank[i]->getUsername() == _username && bank[i]->getPassword() == _password)
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
        
    while(1)
    {
        for(int i = 0; i < ManagerBase::getNum(); i++)
            if(manager[i]->getUsername() == _username && manager[i]->getPassword() == _password)
            {
                string _firstName, _lastName, _nationalCode, _username, _password;
                int _day, _month, _year;
                system("clear");
                cout << "\n\n\tThis panel is for client signUp" << endl;
                
                cout << "\n\n\tFirst name: ";
                cin >> _firstName;
                
                cout << "\n\tLast name: ";
                cin >> _lastName;
                
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
                if(which == 0)
                    enter();
                    
                else{
                    b = true;
                    break;
                }
            }
    
        for(int i = 0; i < BankBase::getNum(); i++)
            if(bank[i]->getUsername() == _username && bank[i]->getPassword() == _password)
            {
                string _firstName, _lastName, _nationalCode, _username, _password;
                int _day, _month, _year, _salary;
                system("clear");
                cout << "\n\n\tThis panel is for Manager signUp" << endl;
                
                cout << "\n\n\tFirst name: ";
                cin >> _firstName;
                
                cout << "\n\tLast name: ";
                cin >> _lastName;
                
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
                if(which == 0)
                    enter();
                    
                else{
                    b = true;
                    break;
                }
            }

        if(!b){ 
            int which;
            cout << "\n\n\n\tYou don't have access to this panel!\n\n\tIf you want to back menu input (0) else input (1)\n\tInput: " << endl;
            cin >> which;
            if(which == 0)
                enter();
                
            break;
        }
    }
}   

void clientPanel(int _ID){
    cout << 1;
}
void managerPanel(int _ID){
    exit(0);
}
void bankPanel(int _ID){
    cout << 3;
}
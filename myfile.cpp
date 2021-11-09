/* declarations start */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bits/stdc++.h>
bool menu = true, accountLoginStopper = true;
int menuChoice;
void atmMenu();
enum MenuChoice{CreateAccount = 1, LogIn};
struct AutoTellerMachine
{
    void CreateNewAccount(std::string newUsername, std::string newPassword)
    {
        username = newUsername;
        password = newPassword;
    }
    void AccountLogin(std::string loginUsername, std::string loginPassword)
    {
        if (loginUsername == username && loginPassword == password)
        {
            std::cout<<"You have logged in!"<<std::endl;
            menu = false;
            accountLoginStopper = false;
        }
        else
        {
            std::cout<<"Wrong username or password!"<<std::endl;
            accountLoginStopper = false;
        }
    }
    void DepositMoney(double depositAmount);
    void WithdrawMoney(double withdrawalAmount);
    void SetAccountLogin(int setAccountLocation);
    void SetLastMoneyMovement(int accountID, double amount);
    void SetBeginningBalance(int accountID);
    void SetLastOperation(int accountID, char userInput);
    void AccountMenu();
    int GetAccountLogin() const;
    double GetLastMoneyMovement(int accountID) const;
    double GetAccountBalance(int accountID) const;
    double GetBeginningBalance(int accountID) const;
    char GetLastOperation(int accountID) const;
    std::string GetUsername(int accountID) const;

    int loggedInAccountLocation;
    double accountBalance;
    double beginningBalance;
    double lastMoneyMovement;
    char lastOperation;
    std::string username;
    std::string password;
};
AutoTellerMachine users[10];

/* declarations end */

/* init start */
int main(){
    std::string username, password;
    AutoTellerMachine admin;
    
    int i = 0;
    //Login loop
    while (menu)
    {
        atmMenu();
        std::cin>>menuChoice;
        bool addingAccount = true;
        switch (menuChoice)
        {
            case CreateAccount:
                std::cout<<"Creating account: \n";
                std::cout<<"Enter a username: ";
                std::cin>>username;
                std::cout<<"Enter password: ";
                std::cin>>password;
                //admin.CreateNewAccount(username, password);
                while (addingAccount)
                {
                    users[i].username = username;
                    users[i].password = password;
                    i++;
                    addingAccount = false;
                }
                break;
            case LogIn:
                std::cout<<"Login: \n";
                std::cout<<"Enter a username: ";
                std::cin>>username;
                std::cout<<"Enter password: ";
                std::cin>>password;
                //admin.AccountLogin(username, password);
                for (int j = 0; j < 10; j++)
                {
                    users[j].AccountLogin(username, password);
                }
                
                std::cout<<"Loading . . ."<<std::endl;
                break;
            default:
                std::cout<<"Enter a legit command."<<std::endl;
                break;
        }
    }
    
}
/* init end */

/* functions start */
void atmMenu()
{
    std::cout<<"1. Create account\n2. Log in"<<std::endl;
}

/* functions end */
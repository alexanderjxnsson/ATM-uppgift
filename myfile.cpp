/*
    Alexander Jönsson
*/
/* declarations start */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
std::string username, password, accountFile = "accounts.csv";
bool menu = true, accountLoginStopper = false, bAccountMenu = true;
int menuChoice, numberOfAccounts = 0, cusIDtracker = 2;
double AmountDepositMoney = 0, AmountWithdrawMoney = 0;
void atmMenu();
void welcomeMenu();
bool fileOK();
enum MenuChoice{CreateAccount = 1, LogIn, Quit};
struct ATM
{
    
    int loggedInAccountLocation;
    std::string username;
    std::string password;
    double accountBalance;
    double beginningBalance;
    double lastMoneyMovement;
    char lastOperation;                                                     
    void CreateNewAccount(std::string newUsername, std::string newPassword);
    void AccountLogin(std::string loginUsername, std::string loginPassword);
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
    std::string GetUsername(int accountID) const; //--

}tadmin;
std::vector<ATM> vUsersList;
std::fstream fout;
std::fstream fin;
/* declarations end */

int main(){
    /* init start */
    fileOK();
    
    while (menu)
    {
        welcomeMenu();
        atmMenu();
        std::cin>>menuChoice;
        switch (menuChoice)
        {
            case CreateAccount:
                std::cout<<"\nCreating: \n";
                std::cout<<"Enter a username: ";
                std::cin>>username;
                std::cout<<"Enter password: ";
                std::cin>>password;
                tadmin.CreateNewAccount(username, password);
                break;
            case LogIn:
                std::cout<<"\nLogin: \n";
                std::cout<<"Enter a username: ";
                std::cin>>username;
                std::cout<<"Enter password: ";
                std::cin>>password;
                tadmin.AccountLogin(username, password);
                if (tadmin.loggedInAccountLocation >= 0)
                {
                    //If LoggedInAccountLocation is getting an index number from 0 and up we access AccountMenu
                    tadmin.AccountMenu();
                }
                break;
            case Quit:
                std::cout<<"\nQuitting. . ."<<std::endl;
                menu = false;
                break;
            default:
                std::cout<<"\nEnter a legit command, please!"<<std::endl;
                break;
        }

    }
    /* init end */
}

/* functions start */
void welcomeMenu()
{   
    std::cout<<"################################\n";
    std::cout<<"#   Welcome to Movants ATM!    #\n";
    std::cout<<"################################\n";
}

bool fileOK()
{
    fout.open(accountFile, std::ios::out | std::ios::app);
    if (fout.is_open() == true)
    {
        std::cout<<"The file is ok!\n";
        system("pause");
        system("cls");
        return true;
        
    }
    else
    {
        std::cout<<"The file is not OK!\n";
        system("pause");
        return false;
    }
    
}

void atmMenu()
{   
    
    std::cout<<"\n1. Create account\n2. Log in\n3. Quit"<<std::endl;
}

void ATM::CreateNewAccount(std::string newUsername, std::string newPassword)
{
    tadmin.username = newUsername;
    tadmin.password = newPassword;
    tadmin.accountBalance = 0;
    tadmin.beginningBalance = 0;
    tadmin.lastMoneyMovement = 0;
    tadmin.loggedInAccountLocation = cusIDtracker;
    cusIDtracker++;
    std::cout<<"\nThank you, your account has been created!\n";
    fout << tadmin.loggedInAccountLocation << ","
         << tadmin.username << ","
         << tadmin.password << ","
         << tadmin.accountBalance << ","
         << tadmin.beginningBalance << ","
         << tadmin.lastMoneyMovement << "\n";
    vUsersList.push_back(tadmin);
    fout.close();
    system("pause");
    system("cls");
    
}

void ATM::AccountLogin(std::string loginUsername, std::string loginPassword)
{
    for (int i = 0; i < vUsersList.size(); i++)
    {
        
        if ((loginUsername == vUsersList[i].username)
        && (loginPassword == vUsersList[i].password))
        {
            //If username and password is correct we print out the logged in user and activate the account menu bool
            accountLoginStopper = true;
            std::cout<<"\n"<<vUsersList[i].username<<" have logged in!"<<std::endl;
            bAccountMenu = true;
            //Sending index number to SetAccountLogin to keep track of who is logged in
            SetAccountLogin(i);
            system("pause");
            system("cls");
            break;
        }
    }

    if (!accountLoginStopper)
    {
        //If the login information isn't correct the bool is false and we print out an error message
        std::cout<<"\nLogin failed, please try again!"<<std::endl;
        tadmin.loggedInAccountLocation = -1;
        system("pause");
        system("cls");
    }
}

void ATM::AccountMenu()
{
    welcomeMenu();
    enum LoggiedInchoice{eDepositMoney = 1, eWithdrawMoney, eRequestBalance, eLogut};
    while (bAccountMenu)
    {
        std::cout<<"\n1. Deposit money\n2. Withdraw money\n3. Request Balance\n4. Logut\n";
        std::cin>>menuChoice;
        switch (menuChoice)
        {
        case eDepositMoney:
            std::cout<<"\nEnter the amount you want to depoisit: ";
            std::cin>>AmountDepositMoney;
            if (AmountDepositMoney > 0)
            {
                DepositMoney(AmountDepositMoney);
            }
            else
            {
                std::cout<<"\nPlease enter a value over 0!\n";
            }
            break;
        case eWithdrawMoney:
            std::cout<<"\nEnter the amount you want to withdraw: ";
            std::cin>>AmountWithdrawMoney;
            if (AmountWithdrawMoney > 0)
            {
                WithdrawMoney(AmountWithdrawMoney);
            }
            else
            {
                std::cout<<"\nPlease enter a value over 0!\n";
            }
            break;
        case eRequestBalance:
            std::cout<<"\nBeggining balance:\t\t"<<GetBeginningBalance(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            if (vUsersList[tadmin.loggedInAccountLocation].lastOperation == 'w')
            {
                std::cout<<"Withdraw amount:\t\t"<<GetLastMoneyMovement(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            }
            else if (vUsersList[tadmin.loggedInAccountLocation].lastOperation == 'd')
            {
                std::cout<<"Deposit amount:\t\t\t"<<GetLastMoneyMovement(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            }
            std::cout<<"Current balance:\t\t"<<GetAccountBalance(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            break;
        case eLogut:
            std::cout<<"\nYou have logged out!\n";
            tadmin.loggedInAccountLocation = -1;
            bAccountMenu = false;
            //atmMenu();
            break;
        default:
            std::cout<<"\nEnter a valid number, please!";
            break;
        }
    }
}

void ATM::SetAccountLogin(int setAccountLocation)
{
    tadmin.loggedInAccountLocation = setAccountLocation;
}

void ATM::SetLastOperation(int accountID, char userInput)
{
    vUsersList[accountID].lastOperation = userInput;
}

void ATM::SetBeginningBalance(int accountID)
{
    vUsersList[accountID].beginningBalance = vUsersList[accountID].accountBalance;
}

void ATM::SetLastMoneyMovement(int accountID, double amount)
{
    vUsersList[accountID].lastMoneyMovement = amount;
}

int ATM::GetAccountLogin() const
{
    return tadmin.loggedInAccountLocation;
}

double ATM::GetAccountBalance(int accountID) const
{
    return vUsersList[accountID].accountBalance;
}

double ATM::GetBeginningBalance(int accountID) const
{
    return vUsersList[accountID].beginningBalance;
}

double ATM::GetLastMoneyMovement(int accountID) const
{
    return vUsersList[accountID].lastMoneyMovement;
}

void ATM::DepositMoney(double depositAmount)
{
    SetLastOperation(tadmin.loggedInAccountLocation, 'd');
    SetBeginningBalance(tadmin.loggedInAccountLocation);
    vUsersList[tadmin.loggedInAccountLocation].accountBalance += depositAmount;
    SetLastMoneyMovement(tadmin.loggedInAccountLocation, depositAmount);
}

void ATM::WithdrawMoney(double withdrawalAmount)
{
    if (withdrawalAmount < vUsersList[tadmin.loggedInAccountLocation].accountBalance)
    {
        SetLastOperation(tadmin.loggedInAccountLocation, 'w');
        SetBeginningBalance(tadmin.loggedInAccountLocation);
        vUsersList[tadmin.loggedInAccountLocation].accountBalance -= withdrawalAmount;
        SetLastMoneyMovement(tadmin.loggedInAccountLocation, withdrawalAmount);
    }
    else
    {
        std::cout<<"\nNot enough money!"<<std::endl;
    }
    
}
/* functions end */
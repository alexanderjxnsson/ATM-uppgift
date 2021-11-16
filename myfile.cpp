/*
    Alexander Jönsson
*/

/* declarations start */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
std::string username, password;
bool menu = true, accountLoginStopper = false, bAccountMenu = true;
int menuChoice, numberOfAccounts = 0, whosLoggedIn = 0;
double AmountDepositMoney = 0, AmountWithdrawMoney = 0;
void atmMenu();
void welcomeMenu();
enum MenuChoice{CreateAccount = 1, LogIn, Quit};
struct ATM
{
    std::vector<ATM> tUsersList;
    std::string username;
    std::string password;
    int loggedInAccountLocation;
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
/* declarations end */

int main(){
    /* init start */
    welcomeMenu();
    while (menu)
    {
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

void atmMenu()
{   
    std::cout<<"\n1. Create account\n2. Log in\n3. Quit"<<std::endl;
}

void ATM::CreateNewAccount(std::string newUsername, std::string newPassword)
{
    ATM tTempUsers;
    tTempUsers.username = newUsername;
    tTempUsers.password = newPassword;
    tTempUsers.accountBalance = 0;
    tTempUsers.beginningBalance = 0;
    tTempUsers.lastMoneyMovement = 0;
    tTempUsers.loggedInAccountLocation = whosLoggedIn;
    tUsersList.push_back(tTempUsers);
    whosLoggedIn++;
    std::cout<<"\nThank you, your account has been created!\n";
    
}

void ATM::AccountLogin(std::string loginUsername, std::string loginPassword)
{
    for (int i = 0; i < tadmin.tUsersList.size(); i++)
    {
        
        if ((loginUsername == tadmin.tUsersList[i].username)
        && (loginPassword == tadmin.tUsersList[i].password))
        {
            //If username and password is correct we print out the logged in user and activate the account menu bool
            accountLoginStopper = true;
            std::cout<<"\n"<<tadmin.tUsersList[i].username<<" have logged in!"<<std::endl;
            bAccountMenu = true;
            //Sending index number to SetAccountLogin to keep track of who is logged in
            SetAccountLogin(i);
            break;
        }
    }

    if (!accountLoginStopper)
    {
        //If the login information isn't correct the bool is false and we print out an error message
        std::cout<<"\nLogin failed, please try again!"<<std::endl;
        tadmin.loggedInAccountLocation = -1;
    }
}

void ATM::AccountMenu()
{
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
            DepositMoney(AmountDepositMoney);
            break;
        case eWithdrawMoney:
            std::cout<<"\nEnter the amount you want to withdraw: ";
            std::cin>>AmountWithdrawMoney;
            WithdrawMoney(AmountWithdrawMoney);
            break;
        case eRequestBalance:
            std::cout<<"\nBeggining balance:\t\t"<<GetBeginningBalance(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            if (tadmin.tUsersList[tadmin.loggedInAccountLocation].lastOperation == 'w')
            {
                std::cout<<"Withdraw amount:\t\t"<<GetLastMoneyMovement(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            }
            else if (tadmin.tUsersList[tadmin.loggedInAccountLocation].lastOperation == 'd')
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
    tadmin.tUsersList[accountID].lastOperation = userInput;
}

void ATM::SetBeginningBalance(int accountID)
{
    tadmin.tUsersList[accountID].beginningBalance = tadmin.tUsersList[accountID].accountBalance;
}

void ATM::SetLastMoneyMovement(int accountID, double amount)
{
    tadmin.tUsersList[accountID].lastMoneyMovement = amount;
}

int ATM::GetAccountLogin() const
{
    return tadmin.loggedInAccountLocation;
}

double ATM::GetAccountBalance(int accountID) const
{
    return tadmin.tUsersList[accountID].accountBalance;
}

double ATM::GetBeginningBalance(int accountID) const
{
    return tadmin.tUsersList[accountID].beginningBalance;
}

double ATM::GetLastMoneyMovement(int accountID) const
{
    return tadmin.tUsersList[accountID].lastMoneyMovement;
}

void ATM::DepositMoney(double depositAmount)
{
    SetLastOperation(tadmin.loggedInAccountLocation, 'd');
    SetBeginningBalance(tadmin.loggedInAccountLocation);
    tadmin.tUsersList[tadmin.loggedInAccountLocation].accountBalance += depositAmount;
    SetLastMoneyMovement(tadmin.loggedInAccountLocation, depositAmount);
}

void ATM::WithdrawMoney(double withdrawalAmount)
{
    if (withdrawalAmount < tadmin.tUsersList[tadmin.loggedInAccountLocation].accountBalance)
    {
        SetLastOperation(tadmin.loggedInAccountLocation, 'w');
        SetBeginningBalance(tadmin.loggedInAccountLocation);
        tadmin.tUsersList[tadmin.loggedInAccountLocation].accountBalance -= withdrawalAmount;
        SetLastMoneyMovement(tadmin.loggedInAccountLocation, withdrawalAmount);
    }
    else
    {
        std::cout<<"\nNot enough money!"<<std::endl;
    }
    
}
/* functions end */
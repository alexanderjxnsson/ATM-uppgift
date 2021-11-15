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
    std::cout<<"Welcome to Movants ATM!\n";
    while (menu)
    {
        atmMenu();
            std::cin>>menuChoice;
        switch (menuChoice)
        {
            case CreateAccount:
                std::cout<<"Creating: \n";
                std::cout<<"Enter a username: ";
                std::cin>>username;
                std::cout<<"Enter password: ";
                std::cin>>password;
                tadmin.CreateNewAccount(username, password);
                break;
            case LogIn:
                std::cout<<"Login: \n";
                std::cout<<"Enter a username: ";
                std::cin>>username;
                std::cout<<"Enter password: ";
                std::cin>>password;
                tadmin.AccountLogin(username, password);
                if (tadmin.loggedInAccountLocation >= 0)
                {
                    tadmin.AccountMenu();
                }
                else
                {
                    std::cout<<"Something went wrong!"<<std::endl;
                }
                break;
            case Quit:
                std::cout<<"Quitting. . ."<<std::endl;
                menu = false;
                break;
            default:
                std::cout<<"Enter a legit command."<<std::endl;
                break;
        }
    }
    /* init end */
}

/* functions start */
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
            accountLoginStopper = true;
            
            std::cout<<std::endl<<tadmin.tUsersList[i].username<<" have logged in!"<<std::endl;
            bAccountMenu = true;
            SetAccountLogin(i);
            
            break;
        }
    }

    if (!accountLoginStopper)
    {
        std::cout<<"\nLogin failed, please try again!"<<std::endl;
    }
}

void ATM::SetAccountLogin(int setAccountLocation)
{
    tadmin.loggedInAccountLocation = setAccountLocation;
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
            std::cout<<"Enter the amount you want to depoisit: ";
            std::cin>>AmountDepositMoney;
            DepositMoney(AmountDepositMoney);
            break;
        case eWithdrawMoney:
            std::cout<<"Enter the amount you want to withdraw: ";
            std::cin>>AmountWithdrawMoney;
            WithdrawMoney(AmountWithdrawMoney);
            break;
        case eRequestBalance:
            std::cout<<"Beggining balance:\t\t"<<GetBeginningBalance(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            if (tadmin.tUsersList[tadmin.loggedInAccountLocation].lastOperation == 'w')
            {
                std::cout<<"Withdraw amount:\t\t\t"<<GetLastMoneyMovement(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            }
            else if (tadmin.tUsersList[tadmin.loggedInAccountLocation].lastOperation == 'd')
            {
                std::cout<<"Deposit amount:\t\t\t"<<GetLastMoneyMovement(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            }
            std::cout<<"Current balance:\t\t"<<GetAccountBalance(tadmin.loggedInAccountLocation)<<"SEK"<<std::endl;
            break;
        case eLogut:
            std::cout<<"You have logged out!\n";
            tadmin.loggedInAccountLocation = -1;
            bAccountMenu = false;
            //atmMenu();
            break;
        default:
            std::cout<<"Enter a valid number, please!";
            break;
        }
    }
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
        std::cout<<"Not enough money!"<<std::endl;
    }
    
}

int ATM::GetAccountLogin() const
{
    return tadmin.loggedInAccountLocation;
}

double ATM::GetAccountBalance(int accountID) const
{
    return tadmin.tUsersList[accountID].accountBalance;
}

void ATM::SetLastMoneyMovement(int accountID, double amount)
{
    tadmin.tUsersList[accountID].lastMoneyMovement = amount;
}

void ATM::SetBeginningBalance(int accountID)
{
    tadmin.tUsersList[accountID].beginningBalance = tadmin.tUsersList[accountID].accountBalance;
}

void ATM::SetLastOperation(int accountID, char userInput)
{
    tadmin.tUsersList[accountID].lastOperation = userInput;
}

double ATM::GetLastMoneyMovement(int accountID) const
{
    return tadmin.tUsersList[accountID].lastMoneyMovement;
}

double ATM::GetBeginningBalance(int accountID) const
{
    return tadmin.tUsersList[accountID].beginningBalance;
}
/* functions end */
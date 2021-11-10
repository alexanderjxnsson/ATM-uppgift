/* declarations start */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
std::string username, password;
bool menu = true, accountLoginStopper = false, addingAccount = true, bAccountMenu = true;
int menuChoice, numberOfAccounts = 0, whosLoggedIn = 0;
double AmountDepositMoney = 0;
void atmMenu();
void loginMenu();
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
    std::string GetUsername(int accountID) const;

}tadmin;
std::vector<ATM> user_list;

/* declarations end */

/* init start */
int main(){
    //Login loop
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
                break;
            case Quit:
                std::cout<<"Qutting. . ."<<std::endl;
                menu = false;
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
    std::cout<<"1. Create account\n2. Log in\n3. Quit"<<std::endl;
}

void ATM::AccountMenu()
{
    enum LoggiedInchoice{eDepositMoney = 1, eWithdrawMoney, eRequestBalance, eLogut};
    while (bAccountMenu = true)
    {
        std::cout<<"\n1. Deposit money\n2. Withdraw money\n3. Request Balance\4. Logut\n";
        std::cin>>menuChoice;
        switch (menuChoice)
        {
        case eDepositMoney:
            std::cout<<"Enter the amount you want to depoisit: ";
            std::cin>>AmountDepositMoney;
            ATM::DepositMoney(AmountDepositMoney);
            break;
        case eWithdrawMoney:
            break;
        case eRequestBalance:
            break;
        case eLogut:
            std::cout<<"You have logged out!\n";
            atmMenu();
            break;
        default:
            std::cout<<"Enter a valid number, please!";
            break;
        }
    }
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
            SetAccountLogin(i);
            std::cout<<loggedInAccountLocation<<std::endl;
            break;
        }
    }
    if (!accountLoginStopper)
    {
        std::cout<<"\nLogin failed!"<<std::endl;
    }
    
}

void ATM::SetAccountLogin(int setAccountLocation)
{
    loggedInAccountLocation = setAccountLocation;
}

int ATM::GetAccountLogin() const
{
    return loggedInAccountLocation;
}

void ATM::DepositMoney(double depositAmount)
{
    
}


/* functions end */
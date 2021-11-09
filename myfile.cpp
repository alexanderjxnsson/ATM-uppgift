#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
struct AutoTellerMachine
{
    //n
};
// to represent each customer who uses the ATM program
//Create new accout
void CreateNewAccount(string newUsername, string newPassword);
//Log in, if/case to compare.
void AccountLogin(string loginUsername, string loginPassword);
//Depost money++
void DepositMoney(double depositAmount);
//Withdraw money--
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
string GetUsername(int accountID) const;

int main(){
    int loggedInAccountLocation;
    double accountBalance;
    double beginningBalance;
    double lastMoneyMovement;
    char lastOperation;
    string username;
    string password;
}
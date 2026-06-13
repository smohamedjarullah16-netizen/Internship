#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    char accountHolderName[50];
    double accountBalance;
    string accountType;

public:
    // New Account Create panna
    void createNewAccount() {
        cout << "\n====================================" << endl;
        cout << "      NEW ACCOUNT REGISTRATION      " << endl;
        cout << "====================================" << endl;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore(); // Buffer clear panna
        
        cout << "Enter Account Holder Name: ";
        cin.getline(accountHolderName, 50);
        
        cout << "Enter Account Type (Savings / Current): ";
        cin >> accountType;
        
        cout << "Enter Initial Deposit Amount: ";
        cin >> accountBalance;
        
        cout << "\nAccount Created Successfully!" << endl;
    }

    // Account details-ah display panna
    void displayAccountDetails() const {
        cout << "\n------------------------------------" << endl;
        cout << "Account No.    : " << accountNumber << endl;
        cout << "Holder Name    : " << accountHolderName << endl;
        cout << "Account Type   : " << accountType << endl;
        cout << "Current Balance: Rs. " << fixed << setprecision(2) << accountBalance << endl;
        cout << "------------------------------------" << endl;
    }

    // Money Deposit panna
    void creditAmount(double amount) {
        accountBalance += amount;
        cout << "\nRs. " << amount << " credited successfully." << endl;
    }

    // Money Withdraw panna
    bool debitAmount(double amount) {
        if (amount > accountBalance) {
            cout << "\nTransaction Failed! Insufficient Balance." << endl;
            return false;
        }
        accountBalance -= amount;
        cout << "\nRs. " << amount << " debited successfully." << endl;
        return true;
    }

    // Getters for File handling operations
    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return accountBalance;
    }
};

// --- FILE HANDLING FUNCTIONS ---

// 1. Save Account to File
void saveAccountToFile() {
    BankAccount ac;
    ofstream outFile

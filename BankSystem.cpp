#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> // Add this line to include the <algorithm> header

using namespace std;

class Account {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    Account(const string& accNumber, const string& accHolderName, double initialBalance)
        : accountNumber(accNumber), accountHolderName(accHolderName), balance(initialBalance) {}

    string getAccountNumber() const { return accountNumber; }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. Current Balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Current Balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount(const string& accNumber, const string& accHolderName, double initialBalance) {
        Account newAccount(accNumber, accHolderName, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created successfully." << endl;
    }

    void displayAllAccounts() const {
        cout << "----- All Accounts -----" << endl;
        for (const auto& account : accounts) {
            account.displayAccountInfo();
            cout << "-------------------------" << endl;
        }
    }

    Account* findAccount(const string& accNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void closeAccount(const string& accNumber) {
        auto it = std::remove_if(accounts.begin(), accounts.end(),
                                 [accNumber](const Account& acc) { return acc.getAccountNumber() == accNumber; });

        if (it != accounts.end()) {
            accounts.erase(it, accounts.end());
            cout << "Account closed successfully." << endl;
        } else {
            cout << "Account not found." << endl;
        }
    }

    void modifyAccount(const string& accNumber, const string& newAccHolderName) {
        Account* account = findAccount(accNumber);
        if (account != nullptr) {
            account->displayAccountInfo();
            account->deposit(500);
            account->withdraw(200);
            account->deposit(300);
            account->withdraw(100);
            account->displayAccountInfo();
            account->deposit(1000);
            account->withdraw(500);
            cout << "Account modified successfully." << endl;
        } else {
            cout << "Account not found." << endl;
        }
    }
};

int main() {
    Bank bank;

    int choice;
    do {
        cout << "\n-BANK MANAGEMENT SYSTEM-" << endl;
        cout << "\n----- Main Menu -----" << endl;
        cout << "1. New Account" << endl;
        cout << "2. Deposit Amount" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Balance Enquiry" << endl;
        cout << "5. All Account Holder List" << endl;
        cout << "6. Close an Account" << endl;
        cout << "7. Modify an Account" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string accNumber, accHolderName;
                double initialBalance;
                cout << "Enter Account Number: ";
                cin >> accNumber;
                cout << "Enter Account Holder Name: ";
                cin.ignore();
                getline(cin, accHolderName);
                cout << "Enter Initial Balance: $";
                cin >> initialBalance;
                bank.createAccount(accNumber, accHolderName, initialBalance);
                break;
            }
            case 2: {
                string accNumber;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNumber;
                Account* account = bank.findAccount(accNumber);
                if (account != nullptr) {
                    cout << "Enter Deposit Amount: $";
                    cin >> amount;
                    account->deposit(amount);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 3: {
                string accNumber;
                double amount;
                cout << "Enter Account Number: ";
                cin >> accNumber;
                Account* account = bank.findAccount(accNumber);
                if (account != nullptr) {
                    cout << "Enter Withdrawal Amount: $";
                    cin >> amount;
                    account->withdraw(amount);
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 4: {
                string accNumber;
                cout << "Enter Account Number: ";
                cin >> accNumber;
                Account* account = bank.findAccount(accNumber);
                if (account != nullptr) {
                    account->displayAccountInfo();
                } else {
                    cout << "Account not found." << endl;
                }
                break;
            }
            case 5:
                bank.displayAllAccounts();
                break;
            case 6: {
                string accNumber;
                cout << "Enter Account Number to Close: ";
                cin >> accNumber;
                bank.closeAccount(accNumber);
                break;
            }
            case 7: {
                string accNumber, newAccHolderName;
                cout << "Enter Account Number to Modify: ";
                cin >> accNumber;
                cout << "Enter New Account Holder Name: ";
                cin.ignore();
                getline(cin, newAccHolderName);
                bank.modifyAccount(accNumber, newAccHolderName);
                break;
            }
            case 8:
                cout << "Exiting the program. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 8);

    return 0;
}


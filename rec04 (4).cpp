/*
  rec04_start.cpp
  20F

 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string name;
    int number = 0;
};

// Task 2
// Define an Account class
class AccountsClass {
    friend  ostream& operator<<(ostream& os, const AccountsClass& account);
public:
    AccountsClass(const string& accountName, int accountNumber) : name(accountName), number(accountNumber) {}
   const string& getName() const {
        return name;
    }
   int getNumber() const {
        return number;
    }
private:
    string name;
    int number;
};


// Task 3
// Define an Account and Transaction classes
class Transactions {
    friend ostream& operator<<(ostream& os, const Transactions& transaction);
public:
    Transactions(const string& transactionType, int transactionAmount) : type(transactionType), amount(transactionAmount) {}
private:
    string type;
    int amount;
};


class AccountsClass2 {
    friend ostream& operator<<(ostream& os, const AccountsClass2& account);
public:
    AccountsClass2(const string& accountName, int accountNumber) : name(accountName), number(accountNumber) {}
    void deposit(int amount) {
        vectorOfTransactions.emplace_back("deposit", amount);
        balance += amount;
    }
    void withdrawal(int amount){
        if (balance - amount < 0) {
            cout << "Failure to withdraw. Insufficient funds in account." << endl;
        } else {
            vectorOfTransactions.emplace_back("withdrawal", amount);
            balance -= amount;
        }
        
    }
    int getNumber() const {
        return number;
    }
private:
    string name;
    int number;
    vector<Transactions> vectorOfTransactions;
    int balance = 0;
};



// Task 4
// Define an Account with a nested public Transaction class

class AccountsClass3 {
    friend ostream& operator<<(ostream& os, const AccountsClass3& account);
public:
    AccountsClass3(const string& accountName, int accountNumber) : 
        name(accountName), number(accountNumber) {}
    void deposit(int amount) {
        vectorOfTransactions.emplace_back("deposit", amount);
        balance += amount;
    }
    void withdrawal(int amount) {
        if (balance - amount < 0) {
            cout << "Failure to withdraw. Insufficient funds in account." << endl;
        }
        else {
            vectorOfTransactions.emplace_back("withdrawal", amount);
            balance -= amount;
        }
    }
    int getNumber() const {
        return number;
    }
    class Transactions {
        friend ostream& operator<<(ostream& os, const AccountsClass3::Transactions& transaction);
    public:
       Transactions(const string& transactionType, int transactionAmount) :
            type(transactionType), amount(transactionAmount) {}
    private:
        string type;
        int amount;
    };
private:
    string name;
    int number;
    vector<Transactions> vectorOfTransactions;
    int balance = 0;
};

// Task 5
// Define an Account with a nested private Transaction class
class AccountsClass4 {
    friend ostream& operator<<(ostream& os, const AccountsClass4& account);
public:
    AccountsClass4(const string& accountName, int accountNumber) :
        name(accountName), number(accountNumber) {}
    void deposit(int amount) {
        vectorOfTransactions.emplace_back("deposit", amount);
        balance += amount;
    }
    void withdrawal(int amount) {
        if (balance - amount < 0) {
            cout << "Failure to withdraw. Insufficient funds in account." << endl;
        }
        else {
            vectorOfTransactions.emplace_back("withdrawal", amount);
            balance -= amount;
        }
    }
    int getNumber() const {
        return number;
    }
private:
    string name;
    int number;
    vector<Transactions> vectorOfTransactions;
    int balance = 0;
    class Transactions {
        friend ostream& operator<<(ostream& os, const AccountsClass4::Transactions& transaction) {
            os << "Transaction Type: " + transaction.type + " Amount: " << transaction.amount << endl;
            return os;
        }
    public:
        Transactions(const string& transactionType, int transactionAmount) :
            type(transactionType), amount(transactionAmount) {}
    private:
        string type;
        int amount;
    };
};

int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream accountsTxt("accounts.txt");
    string name;
    int number;
    vector<Account> vectorOfAccounts;
    while (accountsTxt >> name >> number) {
        Account account;
        account.name = name;
        account.number = number;
        vectorOfAccounts.push_back(account);
    }
    accountsTxt.close();
    for (const Account& i : vectorOfAccounts) {
        cout << "Account Name: " + i.name + ", Account Number:" << i.number << endl;
    }

    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    vectorOfAccounts.clear();
    accountsTxt.open("accounts.txt");
    while (accountsTxt >> name >> number) {
        Account account{ name, number };
        vectorOfAccounts.push_back(account);
    }
    accountsTxt.close();
    for (const Account& i : vectorOfAccounts) {
        cout << "Account Name: " + i.name + ", Account Number:" << i.number << endl;
    }
    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";

    accountsTxt.open("accounts.txt");
    vector<AccountsClass> vectorOfAccountsClass;
    while (accountsTxt >> name >> number) {
        AccountsClass account(name, number);
        vectorOfAccountsClass.push_back(account);
    }
    accountsTxt.close();
    for (size_t index = 0; index < vectorOfAccountsClass.size(); ++index) {
        cout << "Account Name: " + vectorOfAccountsClass[index].getName() + ", Account Number: " << vectorOfAccountsClass[index].getNumber() << endl;
    }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    for (size_t index = 0; index < vectorOfAccountsClass.size(); ++index) {
        cout << vectorOfAccountsClass[index] << endl;
    }
    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for (size_t index = 0; index < vectorOfAccountsClass.size(); ++index) {
        cout << vectorOfAccountsClass[index] << endl;
    }

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    accountsTxt.open("accounts.txt");
    vectorOfAccountsClass.clear();
    while (accountsTxt >> name >> number) {
        vectorOfAccountsClass.push_back(AccountsClass(name, number));
    }
    for (size_t index = 0; index < vectorOfAccountsClass.size(); ++index) {
        cout << vectorOfAccountsClass[index] << endl;
    }
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    accountsTxt.open("accounts.txt");
    vectorOfAccountsClass.clear();
    while (accountsTxt >> name >> number) {
        vectorOfAccountsClass.emplace_back(name, number);
    }
    for (size_t index = 0; index < vectorOfAccountsClass.size(); ++index) {
        cout << vectorOfAccountsClass[index] << endl;
    }
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    ifstream transactionsTxt("transactions.txt");
    string description;
    int amount;
    vector<AccountsClass2> vectorsOfAccounts2;
    while (transactionsTxt >> description) {
        if (description == "Account") {
            transactionsTxt >> name >> number;
            vectorsOfAccounts2.emplace_back(name, number);
        } else {
            transactionsTxt >> number >> amount;
            for (size_t i = 0; i < vectorsOfAccounts2.size(); ++i) {
                if (vectorsOfAccounts2[i].getNumber() == number) {
                    if (description == "Deposit") {
                        vectorsOfAccounts2[i].deposit(amount);
                    } else if (description == "Withdrawal") {
                        vectorsOfAccounts2[i].withdrawal(amount);
                    }
                }

            }

        }
    }
    transactionsTxt.close();
    for (size_t index = 0; index < vectorsOfAccounts2.size(); ++index) {
        cout << vectorsOfAccounts2[index] << endl;
    }
    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    vector<AccountsClass3> vectorsOfAccounts3;
    transactionsTxt.open("transactions.txt");
    while (transactionsTxt >> description) {
        if (description == "Account") {
            transactionsTxt >> name >> number;
            vectorsOfAccounts3.emplace_back(name, number);
        }
        else {
            transactionsTxt >> number >> amount;
            for (size_t i = 0; i < vectorsOfAccounts3.size(); ++i) {
                if (vectorsOfAccounts3[i].getNumber() == number) {
                    if (description == "Deposit") {
                        vectorsOfAccounts3[i].deposit(amount);
                    }
                    else if (description == "Withdrawal") {
                        vectorsOfAccounts3[i].withdrawal(amount);
                    }
                }

            }

        }
    }
    transactionsTxt.close();
    for (size_t index = 0; index < vectorsOfAccounts3.size(); ++index) {
        cout << vectorsOfAccounts3[index] << endl;
    }
    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";
    vector<AccountsClass4> vectorsOfAccounts4;
    transactionsTxt.open("transactions.txt");
    while (transactionsTxt >> description) {
        if (description == "Account") {
            transactionsTxt >> name >> number;
            vectorsOfAccounts4.emplace_back(name, number);
        }
        else {
            transactionsTxt >> number >> amount;
            for (size_t i = 0; i < vectorsOfAccounts4.size(); ++i) {
                if (vectorsOfAccounts4[i].getNumber() == number) {
                    if (description == "Deposit") {
                        vectorsOfAccounts4[i].deposit(amount);
                    }
                    else if (description == "Withdrawal") {
                        vectorsOfAccounts4[i].withdrawal(amount);
                    }
                }

            }

        }
    }
    transactionsTxt.close();
    for (size_t index = 0; index < vectorsOfAccounts4.size(); ++index) {
        cout << vectorsOfAccounts4[index] << endl;
    }

}
 ostream& operator<<(ostream& os, const AccountsClass& account) {
     //os << "Account Name: " << account.getName() << ", Account Number: " << account.getNumber();
     os << "Account Name: " << account.name << ", Account Number: " << account.number;
     return os;
 }

 ostream& operator<<(ostream& os, const AccountsClass2& account) {
     os << "Account Name: " + account.name + ", Account Number: " << account.number << endl;
     os << "Transactions: " << endl;
     for (const Transactions& transaction : account.vectorOfTransactions) {
         os << transaction << endl;
     }
     os << "Balance: " << account.balance << endl;
     return os;
 }
 
 ostream& operator<<(ostream& os, const Transactions& transaction) {
    os << "Transaction Type: " + transaction.type + " Amount: " << transaction.amount << endl;
    return os;
 }

 ostream& operator<<(ostream& os, const AccountsClass3::Transactions& transaction) {
     os << "Transaction Type: " + transaction.type + " Amount: " << transaction.amount << endl;
     return os;
 }



 ostream& operator<<(ostream& os, const AccountsClass3& account) {
     os << "Account Name: " + account.name + ", Account Number: " << account.number << endl;
     os << "Transactions: " << endl;
     for (const AccountsClass3::Transactions& transaction : account.vectorOfTransactions) {
         os << transaction << endl;
     }
     os << "Balance: " << account.balance << endl;
     return os;
 }

 
 ostream& operator<<(ostream& os, const AccountsClass4& account) {
     os << "Account Name: " + account.name + ", Account Number: " << account.number << endl;
     os << "Transactions: " << endl;
     for (size_t i = 0; i < account.vectorOfTransactions.size(); ++i) {
         os << account.vectorOfTransactions[i] << endl;
     }
     os << "Balance: " << account.balance << endl;
     return os;
 }
# Simple Banking System in C++

This is a console-based Banking Management System written in C++. It allows for creating customer accounts, managing transactions (deposit, withdrawal, transfer), and viewing account details.

## Features

- Create customer accounts with name and unique alphanumeric ID.
- Deposit and withdraw funds.
- Transfer funds between accounts.
- View individual account details including transaction history.
- View a list of all customers and their balances.
- Input validation for names and customer IDs.

## Technologies Used

- **Language**: C++
- **Libraries**:
  - `<iostream>` for I/O
  - `<vector>` for dynamic arrays
  - `<string>` for string operations
  - `<iomanip>` for formatted output
  - `<ctime>` for timestamping
  - `<regex>` for input validation
  - `<limits>` for stream handling

## Code Structure

- `Transaction` class: Represents individual transactions.
- `Account` class: Manages deposits, withdrawals, transfers, and stores transaction history.
- `Customer` class: Contains customer info and their linked account.
- `BankSystem` class: Core logic to manage customers and operations.

## Validations

- **Customer Name**: Must start with capital letters (e.g., `John Doe`)
- **Customer ID**: Must be alphanumeric and unique (e.g., `john123`)

## How to Compile

Make sure you have a C++ compiler (e.g., `g++`) installed.

### Compile using g++:

```bash
g++ -o BankSystem main.cpp
```

### ====== BANKING SYSTEM MENU ======
1. Create Customer Account
2. Deposit
3. Withdraw
4. Transfer
5. View Account
6. Exit
7. View All Customers
Enter your choice:

## Screenshot
### Code:
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20105834.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20105908.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20105927.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20110612.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20110629.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20110654.png?raw=true)

### Output:
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20111014.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20111034.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20111052.png?raw=true)
![image](https://github.com/ashishyadav-1510/CodeAlpha_Banking_System/blob/main/Screenshot/Screenshot%202025-07-19%20111100.png?raw=true)

## Video

[Video on YouTube](https://youtu.be/z9kgyzyGVQk)

## Explaination:

Header Files

#include <iostream>       // For input/output operations
#include <vector>         // To use dynamic arrays (e.g., list of transactions/customers)
#include <string>         // For using the string class
#include <iomanip>        // For formatted output (e.g., setw, setprecision)
#include <ctime>          // To get current system time for timestamps
#include <regex>          // For input validation using regular expressions
#include <limits>         // To handle input buffer flushing
using namespace std;
This line allows you to use standard C++ objects like cout, cin, vector, etc., without prefixing them with std::.

Transaction Class

class Transaction {
    string type;          // "Deposit", "Withdrawal", or "Transfer"
    double amount;        // Amount involved in the transaction
    string timestamp;     // Time when the transaction occurred
Constructor

    Transaction(string t, double a) : type(t), amount(a) {
        time_t now = time(0);              // Get current system time
        timestamp = string(ctime(&now));   // Convert time to readable string
        timestamp.pop_back();              // Remove trailing newline character
    }
Display Function

    void display() const {
        cout << left << setw(15) << type
             << " | Amount: " << setw(10) << amount
             << " | Time: " << timestamp << endl;
    }
};
Account Class

class Account {
    int accNumber;                   // Unique account number
    double balance;                  // Current balance
    vector<Transaction> transactions;// List of transactions
Constructor

    Account(int accNum) : accNumber(accNum), balance(0.0) {}
Getters

    int getAccountNumber() const { return accNumber; }
    double getBalance() const { return balance; }
Deposit

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount)); // Log deposit
        cout << "Deposit successful.\n";
    }
Withdraw

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            cout << "Insufficient Funds.\n";
            return false;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
        cout << "Withdrawal successful.\n";
        return true;
    }
Transfer

    bool transfer(Account &receiver, double amount) {
        if (withdraw(amount)) {
            receiver.deposit(amount);
            transactions.push_back(Transaction("Transfer to " + to_string(receiver.getAccountNumber()), amount));
            return true;
        }
        return false;
    }
Show Transactions

    void showTransactions() const {
        cout << "\n--- Transactions for Account " << accNumber << " ---\n";
        for (const auto &t : transactions)
            t.display();
    }
Show Account Details

    void showDetails() const {
        cout << "\nAccount Number: " << accNumber << endl;
        cout << "Balance: ₹" << fixed << setprecision(2) << balance << endl;
        showTransactions();
    }
};
Customer Class

class Customer {
    string name;
    string id;
    int srNo;
    Account account;
Constructor

    Customer(string n, string i, int sr) : name(n), id(i), srNo(sr), account(sr + 1000) {}
Getters

    string getID() const { return id; }
    int getSrNo() const { return srNo; }
    string getName() const { return name; }

    Account& getAccount() { return account; }               // Non-const version
    const Account& getAccount() const { return account; }   // Const version for read-only access
Display Customer Info

    void display() const {
        cout << "\nSr.No: " << srNo
             << " | Customer ID: " << id
             << " | Name: " << name
             << " | Account No: " << account.getAccountNumber() << endl;
    }
};
Validation Functions

bool isValidName(const string &name) {
    regex nameRegex("^([A-Z][a-z]*)( [A-Z][a-z]*)*$"); // Each word starts with uppercase
    return regex_match(name, nameRegex);
}

bool isValidCustomerID(const string &id) {
    regex idRegex("^[a-zA-Z0-9]+$"); // Alphanumeric only
    return regex_match(id, idRegex);
}
BankSystem Class

class BankSystem {
    vector<Customer> customers; // List of all customers
    int serialCounter = 1;      // To assign Sr.No.
Find a Customer by ID
cpp
Copy
Edit
    Customer* findCustomer(const string &id) {
        for (auto &c : customers) {
            if (c.getID() == id)
                return &c;
        }
        return nullptr;
    }
Create Customer

    void createCustomer() {
        string name, id;

        while (true) {
            cout << "\nEnter Customer Name : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Flush input
            getline(cin, name);
            if (isValidName(name)) break;
            cout << "Invalid name format\n(Each word starts with capital)\n";
        }

        while (true) {
            cout << "Enter Customer ID : ";
            getline(cin, id);

            if (!isValidCustomerID(id)) {
                cout << "Invalid ID format\n(Alphanumeric only, unique)\n";
                continue;
            }

            if (findCustomer(id)) {
                cout << "Customer ID already exists. Try different.\n";
                continue;
            }

            break;
        }

        customers.emplace_back(name, id, serialCounter++);
        cout << "Customer Account created successfully.\n";
    }
Deposit Function

    void deposit() {
        string id;
        double amount;
        cout << "\nEnter Customer ID: ";
        cin >> id;
        Customer* c = findCustomer(id);
        if (c) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            c->getAccount().deposit(amount);
        } else {
            cout << "Customer not found.\n";
        }
    }
Withdraw Function

    void withdraw() {
        string id;
        double amount;
        cout << "\nEnter Customer ID: ";
        cin >> id;
        Customer* c = findCustomer(id);
        if (c) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            c->getAccount().withdraw(amount);
        } else {
            cout << "Customer not found.\n";
        }
    }
Transfer Function

    void transfer() {
        string fromID, toID;
        double amount;
        cout << "\nEnter Sender Customer ID: ";
        cin >> fromID;
        cout << "Enter Receiver Customer ID: ";
        cin >> toID;

        Customer* sender = findCustomer(fromID);
        Customer* receiver = findCustomer(toID);

        if (sender && receiver) {
            cout << "Enter transfer amount: ";
            cin >> amount;
            if (sender->getAccount().transfer(receiver->getAccount(), amount))
                cout << "Transfer successful.\n";
        } else {
            cout << "One or both customers not found.\n";
        }
    }
View Account

    void viewAccount() {
        string id;
        cout << "\nEnter Customer ID: ";
        cin >> id;
        Customer* c = findCustomer(id);
        if (c) {
            c->display();
            c->getAccount().showDetails();
        } else {
            cout << "Customer not found.\n";
        }
    }
View All Customers

    void viewAllCustomers() {
        if (customers.empty()) {
            cout << "\nNo customers in the bank.\n";
            return;
        }

        cout << "\n========== CUSTOMER LIST ==========\n";
        cout << left << setw(6) << "SrNo"
             << setw(15) << "Customer ID"
             << setw(25) << "Name"
             << setw(15) << "Account No"
             << setw(10) << "Balance" << endl;
        cout << string(70, '-') << endl;

        for (const auto &c : customers) {
            cout << left << setw(6) << c.getSrNo()
                 << setw(15) << c.getID()
                 << setw(25) << c.getName()
                 << setw(15) << c.getAccount().getAccountNumber()
                 << "$" << fixed << setprecision(2) << c.getAccount().getBalance() << endl;
        }
    }
};
Main Function

int main() {
    BankSystem bank;
    int choice;
    
    while (true) {
        cout << "\n====== BANKING SYSTEM MENU ======\n";
        cout << "1. Create Customer Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. View Account\n6. Exit\n7. View All Customers\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createCustomer(); break;
            case 2: bank.deposit(); break;
            case 3: bank.withdraw(); break;
            case 4: bank.transfer(); break;
            case 5: bank.viewAccount(); break;
            case 6: cout << "Thank you for using the Bank System!\n"; return 0;
            case 7: bank.viewAllCustomers(); break;
            default: cout << "Invalid choice!!\n";
        }
    }
}

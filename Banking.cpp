#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <regex>
#include <limits>

using namespace std;

// ------------------- Transaction Class -------------------
class Transaction {
    string type;
    double amount;
    string timestamp;

public:
    Transaction(string t, double a) : type(t), amount(a) {
        time_t now = time(0);
        timestamp = string(ctime(&now));  
        timestamp.pop_back();             // remove trailing newline
    }

    void display() const {
        cout << left << setw(15) << type
             << " | Amount: " << setw(10) << amount
             << " | Time: " << timestamp << endl;
    }
};

// ------------------- Account Class -------------------
class Account {
    int accNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNum) : accNumber(accNum), balance(0.0) {}

    int getAccountNumber() const { return accNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposit successful.\n";
    }

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

    bool transfer(Account &receiver, double amount) {
        if (withdraw(amount)) {
            receiver.deposit(amount);
            transactions.push_back(Transaction("Transfer to " + to_string(receiver.getAccountNumber()), amount));
            return true;
        }
        return false;
    }

    void showTransactions() const {
        cout << "\n--- Transactions for Account " << accNumber << " ---\n";
        for (const auto &t : transactions)
            t.display();
    }

    void showDetails() const {
        cout << "\nAccount Number: " << accNumber << endl;
        cout << "Balance: ₹" << fixed << setprecision(2) << balance << endl;
        showTransactions();
    }
};

// ------------------- Customer Class -------------------
class Customer {
    string name;
    string id;
    int srNo;
    Account account;

public:
    Customer(string n, string i, int sr) : name(n), id(i), srNo(sr), account(sr + 1000) {}

    string getID() const { return id; }
    int getSrNo() const { return srNo; }
    string getName() const { return name; }

    // Non-const version
    Account& getAccount() { return account; }

    // Const version added to fix error
    const Account& getAccount() const { return account; }

    void display() const {
        cout << "\nSr.No: " << srNo
             << " | Customer ID: " << id
             << " | Name: " << name
             << " | Account No: " << account.getAccountNumber() << endl;
    }
};

// ------------------- Validation Utilities -------------------
bool isValidName(const string &name) {
    regex nameRegex("^([A-Z][a-z]*)( [A-Z][a-z]*)*$");
    return regex_match(name, nameRegex);
}

bool isValidCustomerID(const string &id) {
    regex idRegex("^[a-zA-Z0-9]+$");
    return regex_match(id, idRegex);
}

// ------------------- Banking System Class -------------------
class BankSystem {
    vector<Customer> customers;
    int serialCounter = 1;

    Customer* findCustomer(const string &id) {
        for (auto &c : customers) {
            if (c.getID() == id)
                return &c;
        }
        return nullptr;
    }

public:
    void createCustomer() {
        string name, id;

        // Name validation
        while (true) {
            cout << "\nEnter Customer Name : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover newline
            getline(cin, name);
            if (isValidName(name)) break;
            cout << "Invalid name format\n(Each word starts with capital)\n";
        }

        // ID validation and uniqueness
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

// ------------------- Main Function -------------------
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
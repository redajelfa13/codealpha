#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Customer {
private:
    static int nextCustomerID; 
    int customerID;
    string name;
    string address;
    string phoneNumber;
    string email;

public:
    Customer() : customerID(nextCustomerID++), name(""), address(""), phoneNumber(""), email("") {}

    void addCustomer();
    void listCustomer() const;
    int getCustomerID() const { return customerID; }
    const string& getName() const { return name; }
    const string& getAddress() const { return address; }
    const string& getPhoneNumber() const { return phoneNumber; }
    const string& getEmail() const { return email; }
};

int Customer::nextCustomerID = 1;

void Customer::addCustomer() {
    fstream customerdata("customerdata.txt", ios::out | ios::app);
    if (!customerdata.is_open()) {
        cout << "ERROR OPENING THE FILE !!\n";
        return;
    }

    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, name);
    customerdata << customerID << "\n" << name << "\n";
    cout << "Enter your address: ";
    getline(cin, address);
    customerdata << address << "\n";

    cout << "Enter your phone number: ";
    getline(cin, phoneNumber);
    customerdata << phoneNumber << "\n";

    cout << "Enter your email: ";
    getline(cin, email);
    customerdata << email << "\n";

    cout << "==============================\n"; 
	
    customerdata.close();
    
    cout << "Customer Created :\n \n";
}

void Customer::listCustomer() const {
    cout << "Customer ID: " << customerID << "\nName: " << name
         << "\nAddress: " << address << "\nPhone Number: " << phoneNumber
         << "\nEmail: " << email << endl;
}

class Account {
private:
    static int nextAccountID;  
    int accountNumber;
    int customerID;
    double balance;

public: 	
    Account(int custID) : accountNumber(nextAccountID++), customerID(custID), balance(0.0) {}
    int getAccountNumber() const {
        return accountNumber;
    }

    int getCustomerID() const {
        return customerID;
    }

    double getBalance() const {
        return balance;
    }

    void addAccount();
    void account_detail() const;
    void deposit(double amount);
    void withdraw(double amount);
};

int Account::nextAccountID = 2000;

void Account::addAccount() {
    fstream customerdata("customerdata.txt", ios::in);

    if (!customerdata.is_open()) {
        cout << "ERROR OPENING THE FILE !!\n";
        return;
    }

    int customerIDToSearch;
    cout << "Enter your customer ID: ";
    cin >> customerIDToSearch;

    int fileCustomerID;
    string fileName, fileAddress, filePhoneNumber, fileEmail;
    bool customerFound = false;

    while (customerdata >> fileCustomerID) {
        customerdata.ignore();
        getline(customerdata, fileName);
        getline(customerdata, fileAddress);
        getline(customerdata, filePhoneNumber);
        getline(customerdata, fileEmail);

        if (fileCustomerID == customerIDToSearch) {
            customerFound = true;
            break;
        }
    }

    customerdata.close();

    if (customerFound) {
        fstream accountdata("accountdata.txt", ios::out | ios::app);
        if (!accountdata.is_open()) {
            cout << "ERROR OPENING THE FILE !!\n";
            return;
        }

        balance = 0.0; // Initialize balance
        accountdata << accountNumber << "\n" << customerID << "\n" << balance << "\n";

        accountdata.close();

        cout << "Account Created :\n \n";
    } else {
        cout << "You have to create a customer account first.\n";
    }
}

void Account::account_detail{
    cout << "Account Number: " << accountNumber << "\nCustomer ID: " << customerID
         << "\nBalance: " << balance << endl;
}

void Account::deposit(double amount) {
    balance += amount;
    cout << "Deposit of $" << amount << " successful.\n";
}
void Account::withdraw(double amount) {
    if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
}


class Transaction {
public:
    void depositToAccount(Account& account);
    void withdrawfromaccount(Account& account);
};

void Transaction::depositToAccount(Account& account) {
    double amount;
    cout << "Enter the amount you want to deposit: $";
    cin >> amount;

    account.deposit(amount);
}
void Transaction::withdrawfromaccount(Account& account) {
    double amount;
    cout << "Enter the amount you want to withdraw: $ ";
    cin >> amount;

    account.withdraw(amount);
}
int main() {
    Customer customer;
    customer.addCustomer();
    customer.listCustomer();

    Account account(customer.getCustomerID());
    account.addAccount();
    account.listAccount();

    Transaction transaction;
    transaction.depositToAccount(account);

    account.listAccount(); 

    return 0;
}

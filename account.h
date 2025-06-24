#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Transaction {
    string type;
    double amount;
    string timestamp;

    void display() const;
};

class Account {
protected:
    static int nextAccNumber;
    int accNumber;
    string name;
    string pin;
    double balance;
    vector<Transaction> transactions;

public:
    Account();
    void createAccount();
    bool authenticate(const string &enteredPin) const;
    void deposit(double amount);
    void withdraw(double amount);
    void showAccount() const;
    void showMiniStatement() const;
    void calculateInterest();
    int getAccNumber() const;
    double getBalance() const;
    string getName() const;

    void saveToFile(ofstream &out);
    bool loadFromFile(ifstream &in);
};

#endif
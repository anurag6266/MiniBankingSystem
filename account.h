#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Transaction {
public:
    std::string type;
    double amount;
    std::string timestamp;
    Transaction(std::string t, double a, std::string ts);
    void display() const;
};

class Account {
protected:
    static int nextAccNumber;
    int accNumber;
    std::string name;
    std::string pin;
    double balance;
    std::vector<Transaction> transactions;

public:
    Account();
    void createAccount();
    bool authenticate(const std::string &enteredPin) const;
    void deposit(double amount);
    void withdraw(double amount);
    void showAccount() const;
    void showMiniStatement() const;
    void calculateInterest();
    int getAccNumber() const;
    double getBalance() const;
    std::string getName() const;

    void saveToFile(std::ofstream &out);
    void loadFromFile(std::ifstream &in);
};

#endif
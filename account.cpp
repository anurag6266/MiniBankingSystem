#include "account.h"
#include <ctime>
#include <iomanip>

using namespace std;

int Account::nextAccNumber = 1001;

Transaction::Transaction(string t, double a, string ts)
    : type(t), amount(a), timestamp(ts) {}

void Transaction::display() const {
    cout << setw(10) << type << " | "
         << setw(10) << amount << " | "
         << timestamp << endl;
}

Account::Account() : accNumber(0), balance(0.0) {}

void Account::createAccount() {
    accNumber = nextAccNumber++;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Set a 4-digit PIN: ";
    cin >> pin;
    cout << "Enter Initial Balance: ";
    cin >> balance;
    time_t now = time(0);
    transactions.emplace_back("Init", balance, ctime(&now));
    cout << "Account Created Successfully. Account No: " << accNumber << endl;
}

bool Account::authenticate(const string &enteredPin) const {
    return pin == enteredPin;
}

void Account::deposit(double amount) {
    balance += amount;
    time_t now = time(0);
    transactions.emplace_back("Deposit", amount, ctime(&now));
    cout << "Deposited successfully.";
}

void Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        time_t now = time(0);
        transactions.emplace_back("Withdraw", amount, ctime(&now));
        cout << "Withdrawal successful.";
    } else {
        cout << "Insufficient balance!";
    }
}

void Account::calculateInterest() {
    double interestRate = 0.04; // 4%
    double interest = balance * interestRate;
    balance += interest;
    time_t now = time(0);
    transactions.emplace_back("Interest", interest, ctime(&now));
    cout << "Interest of " << interest << " added to balance.";
}

void Account::showAccount() const {
    cout << "Account No: " << accNumber << " | Name: " << name
         << " | Balance: " << balance << endl;
}

void Account::showMiniStatement() const {
    cout << "Mini Statement for Account No: " << accNumber << endl;
    cout << "---------------------------------------------";
    for (const auto &t : transactions)
        t.display();
}

int Account::getAccNumber() const {
    return accNumber;
}

double Account::getBalance() const {
    return balance;
}

string Account::getName() const {
    return name;
}

void Account::saveToFile(ofstream &out) {
    out << accNumber << " " << name << " " << pin << " " << balance << " " << transactions.size() << "\n";
    for (const auto &t : transactions) {
        out << t.type << " " << t.amount << " " << t.timestamp;
    }
}

void Account::loadFromFile(ifstream &in) {
    int txnCount;
    in >> accNumber >> name >> pin >> balance >> txnCount;
    in.ignore();
    transactions.clear();
    for (int i = 0; i < txnCount; ++i) {
        string type, ts;
        double amount;
        in >> type >> amount;
        getline(in, ts);
        transactions.emplace_back(type, amount, ts);
    }
}
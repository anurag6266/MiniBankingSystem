#include "account.h"
#include <ctime>
#include <iomanip>

using namespace std;

int Account::nextAccNumber = 1001;

void Transaction::display() const {
    cout << setw(10) << type << " | "
         << setw(10) << amount << " | "
         << timestamp << endl;
}

Account::Account() : accNumber(0), balance(0.0) {}

// A helper function to get a formatted timestamp string
string getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[80];
    // Format: YYYY-MM-DD HH:MM:SS
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void Account::createAccount() {
    accNumber = nextAccNumber++;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Set a 4-digit PIN: ";
    cin >> pin;
    cout << "Enter Initial Balance: ";
    cin >> balance;
    transactions.push_back({"Init", balance, getCurrentTimestamp()});
    cout << "Account Created Successfully. Account No: " << accNumber << endl;
}

bool Account::authenticate(const string &enteredPin) const {
    return pin == enteredPin;
}

void Account::deposit(double amount) {
    balance += amount;
    transactions.push_back({"Deposit", amount, getCurrentTimestamp()});
    cout << "Deposited successfully.";
}

void Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        transactions.push_back({"Withdraw", amount, getCurrentTimestamp()});
        cout << "Withdrawal successful.";
    } else {
        cout << "Insufficient balance!";
    }
}

void Account::calculateInterest() {
    double interestRate = 0.04; // 4%
    double interest = balance * interestRate;
    balance += interest;
    transactions.push_back({"Interest", interest, getCurrentTimestamp()});
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
    out << accNumber << "\n" << name << "\n" << pin << " " << balance << " " << transactions.size() << "\n";
    for (const auto &t : transactions) {
        out << t.type << " " << t.amount << " " << t.timestamp << "\n";
    }
}

bool Account::loadFromFile(ifstream &in) {
    int txnCount;
    
    if (!(in >> accNumber)) {
        return false;
    }
    in.ignore(); // Consume the rest of the line after reading account number

    if (!getline(in, name)) {
        return false;
    }

    if (!(in >> pin >> balance >> txnCount)) {
        return false;
    }
    in.ignore(); 
    transactions.clear();
    for (int i = 0; i < txnCount; ++i) {
        string type, timestamp_part1, timestamp_part2;
        double amount;
        if (in >> type >> amount >> timestamp_part1 >> timestamp_part2) {
            transactions.push_back({type, amount, timestamp_part1 + " " + timestamp_part2});
            in.ignore(); // consume rest of line
        } else {
            // In case of parsing error for a transaction
            break; 
        }
    }
    return true;
}
#include "account.h"
#include <vector>
#include <fstream>

using namespace std;

vector<Account> accounts;

void loadAccounts() {
    ifstream in("data.txt");
    if (!in) return;
    while (!in.eof()) {
        Account acc;
        acc.loadFromFile(in);
        if (acc.getAccNumber() != 0)
            accounts.push_back(acc);
    }
    in.close();
}

void saveAccounts() {
    ofstream out("data.txt");
    for (auto &acc : accounts)
        acc.saveToFile(out);
    out.close();
}

int findAccount(int number) {
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccNumber() == number)
            return i;
    }
    return -1;
}

int main() {
    loadAccounts();
    int choice;
    while (true) {
        cout << "\n==== Banking System ====\n";
        cout << "1. Create Account\n2. Login\n3. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            Account acc;
            acc.createAccount();
            accounts.push_back(acc);
        } else if (choice == 2) {
            int num;
            string pin;
            cout << "Enter Account Number: ";
            cin >> num;
            int idx = findAccount(num);
            if (idx != -1) {
                cout << "Enter PIN: ";
                cin >> pin;
                if (accounts[idx].authenticate(pin)) {
                    int option;
                    do {
                        cout << "\n1. Show Balance\n2. Deposit\n3. Withdraw\n4. Mini Statement\n5. Interest\n6. Logout\nChoose: ";
                        cin >> option;
                        if (option == 1) accounts[idx].showAccount();
                        else if (option == 2) {
                            double amt;
                            cout << "Amount to Deposit: ";
                            cin >> amt;
                            accounts[idx].deposit(amt);
                        } else if (option == 3) {
                            double amt;
                            cout << "Amount to Withdraw: ";
                            cin >> amt;
                            accounts[idx].withdraw(amt);
                        } else if (option == 4) accounts[idx].showMiniStatement();
                        else if (option == 5) accounts[idx].calculateInterest();
                    } while (option != 6);
                } else {
                    cout << "Incorrect PIN!\n";
                }
            } else {
                cout << "Account not found!\n";
            }
        } else if (choice == 3) {
            saveAccounts();
            cout << "Data saved. Goodbye!\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
    return 0;
}
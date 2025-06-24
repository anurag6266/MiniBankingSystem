#include "account.h"
#include <vector>
#include <fstream>

using namespace std;

vector<Account> accounts;

void loadAccounts() {
    ifstream in("data.txt");
    if (!in.is_open()) return;

    Account acc;
    while (acc.loadFromFile(in)) {
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

        switch (choice) {
            case 1: {
                Account acc;
                acc.createAccount();
                accounts.push_back(acc);
                break;
            }
            case 2: {
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
                            switch (option) {
                                case 1:
                                    accounts[idx].showAccount();
                                    break;
                                case 2: {
                                    double amt;
                                    cout << "Amount to Deposit: ";
                                    cin >> amt;
                                    accounts[idx].deposit(amt);
                                    break;
                                }
                                case 3: {
                                    double amt;
                                    cout << "Amount to Withdraw: ";
                                    cin >> amt;
                                    accounts[idx].withdraw(amt);
                                    break;
                                }
                                case 4:
                                    accounts[idx].showMiniStatement();
                                    break;
                                case 5:
                                    accounts[idx].calculateInterest();
                                    break;
                                case 6:
                                    cout << "Logging out...\n";
                                    break;
                                default:
                                    cout << "Invalid option.\n";
                                    break;
                            }
                        } while (option != 6);
                    } else {
                        cout << "Incorrect PIN!\n";
                    }
                } else {
                    cout << "Account not found!\n";
                }
                break;
            }
            case 3: {
                saveAccounts();
                cout << "Data saved. Goodbye!\n";
                return 0;
            }
            default: {
                cout << "Invalid option.\n";
                break;
            }
        }
    }
    return 0;
}
/*****
** Author : Greyson Robart
** Program : Hw2
** Date Created : March 3, 2024
** Date Last Modified : March 3, 2024
** Usage : No command line arguments
**
** This program manages a checkbook
****/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Check {
    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    bool operator>(const float& amount) const {
        return CheckAmount > amount;
    }

    friend ostream& operator<<(ostream& os, const Check& check) {
        os << "Check #" << check.CheckNum << ": $" << check.CheckAmount
           << " [" << check.CheckMemo << "]";
        return os;
    }
};

class CheckBook {
private:
    float balance;
    Check* chkPtr;
    float lastDeposit;
    int numOfChecks;
    int checkBookSize;
    void resizeCheckBook() {
        Check* temp = new Check[checkBookSize * 2];
        for (int i = 0; i < checkBookSize; ++i) {
            temp[i] = chkPtr[i];
        }
        delete[] chkPtr;
        chkPtr = temp;
        checkBookSize *= 2;
        cout << "Checkbook size doubled to " << checkBookSize << " checks.\n";
    }

public:
    CheckBook() : balance(0), chkPtr(new Check[4]), lastDeposit(0), numOfChecks(0), checkBookSize(4) {}
    CheckBook(float initialBalance) : balance(initialBalance), chkPtr(new Check[2]), lastDeposit(0), numOfChecks(0), checkBookSize(2) {}
    ~CheckBook() {
        delete[] chkPtr;
    }

    CheckBook(const CheckBook& other) : balance(other.balance), lastDeposit(other.lastDeposit), numOfChecks(other.numOfChecks), checkBookSize(other.checkBookSize) {
        chkPtr = new Check[checkBookSize];
        for (int i = 0; i < checkBookSize; ++i) {
            chkPtr[i] = other.chkPtr[i];
        }
    }

    CheckBook& operator=(const CheckBook& other) {
        if (this != &other) {
            delete[] chkPtr;
            balance = other.balance;
            lastDeposit = other.lastDeposit;
            numOfChecks = other.numOfChecks;
            checkBookSize = other.checkBookSize;
            chkPtr = new Check[checkBookSize];
            for (int i = 0; i < checkBookSize; ++i) {
                chkPtr[i] = other.chkPtr[i];
            }
        }
        return *this;
    }

    void deposit(float amount) {
        balance += amount;
        lastDeposit = amount;
        cout << "deposited $" << amount << ". New balance: $" << balance << ".\n";
    }

    bool writeCheck(float amount) {
        if (amount <= balance) {
            if (numOfChecks == checkBookSize) {
                resizeCheckBook();
            }
            chkPtr[numOfChecks].CheckNum = numOfChecks + 1;
            chkPtr[numOfChecks].CheckAmount = amount;
            string memos[] = {"Groceries", "Utilities", "Rent", "going Out", "Gas"};
            chkPtr[numOfChecks].CheckMemo = memos[rand() % 5];
            balance -= amount;
            numOfChecks++;
            cout << "Check written:" << chkPtr[numOfChecks - 1] << ". New balance: $" << balance << ".\n";
            return true;
        } else {
            cout << "Insufficient funds to write a check for $" << amount << ".\n";
            return false;
        }
    }

    void displayChecks() const {
        cout << "Displaying all checks in reverse :\n";
        for (int i = numOfChecks - 1; i >= 0; --i) {
            cout << chkPtr[i] << endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    cout << "Displaying CheckBook with a high balance...\n";
    CheckBook myCheckBook(1000.0);

    myCheckBook.deposit(500);
    myCheckBook.writeCheck(200);

    while (myCheckBook.writeCheck((rand() % 100 + 1))) {
    }

    myCheckBook.displayChecks();

    return 0;
}

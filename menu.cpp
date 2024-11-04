// Menu.cpp
#include "Menu.h"
#include <iostream>
#include "admin.h"

using namespace std;

void menu1() {
    int option{};
    while (true) {
        cout << "Welcome to Skyline Cyber Café\n";
        cout << "1. Register\n";
        cout << "2. Login as User\n";
        cout << "3. Login as Admin\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore();

        switch (option) {
        case 1:
            registerUser();
            break;
        case 2:
            if (loginUser()) {
                string userID = users.begin()->first;
                startSession(userID);
                usermenu(users[userID]);
            }
            break;
        case 3:
            loginAdmin();
            adminMenu();
            
            break;
        case 4:
            cout << "Thank you for using Skyline Cyber Café!\n";
            return;
        default:
            cout << "Invalid option, please try again.\n";
            break;
        }
    }
}

void usermenu(const alluser& user) {
    cout << "Welcome " << user.name << " to Skyline Cyber Café\n";
    char choice;
    while (true) {
        cout << "\n1. Internet Browsing" << endl;
        cout << "2. Gaming" << endl;
        cout << "3. Print Pages" << endl;
        cout << "4. Scan Pages" << endl;
        cout << "5. Pay Bill" << endl;
        cout << "6. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            cout << "Starting internet browsing session...\n";
            break;
        case 2:
            cout << "Starting gaming session...\n";
            break;
        case 3: {
            int pages;
            cout << "Enter number of pages to print: ";
            cin >> pages;
            double cost = pages * printCostPerPage;
            cout << "Total cost for printing " << pages << " pages: NZD " << cost << endl;
            break;
        }
        case 4: {
            int pages;
            cout << "Enter number of pages to scan: ";
            cin >> pages;
            double cost = pages * scanCostPerPage;
            cout << "Total cost for scanning " << pages << " pages: NZD " << cost << endl;
            break;
        }
        case 5: {
            double totalBill = user.totalPrintCost + user.totalScanCost;
            cout << "Total Print Cost: NZD " << user.totalPrintCost << endl;
            cout << "Total Scan Cost: NZD " << user.totalScanCost << endl;
            cout << "Total Amount Payable: NZD " << totalBill << endl;
            break;
        }
        case 6: { menu1(); }

        default:
            cout << "Invalid option, please try again.\n";
            break;
        }
    }
}


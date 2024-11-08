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

void usermenu( alluser& user) {
    int choice;
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
            cout << "Starting internet browsing session. Type 'exit' to end browsing session.\n";
            startSession(user.userID, "browsing");
            endSession(user.userID, "browsing"); 
            break;
        case 2:
            cout << "Starting gaming session. Type 'exit' to end gaming session.\n";
            startSession(user.userID, "gaming");
            endSession(user.userID, "gaming"); 
            break;
        case 3: {
            int pages;
            cout << "Enter number of pages to print: ";
            cin >> pages;
            user.totalPrintPages += pages;
            break;
        }
        
        case 4: {
            int pages;
            cout << "Enter number of pages to scan: ";
            cin >> pages;
            user.totalScanPages += pages;
            break;
        }
        case 5:
            calculateBill(user.userID);
            break;
        case 6:
            return;
        default:
            cout << "Invalid option, please try again.\n";
            break;
        }
    }
}

void startSession(const string& userID, const string& sessionType) {
    time_t startTime = time(nullptr);

    if (sessionType == "browsing") {
        users[userID].browsingSessions.push_back({ startTime, 0 });
    }
    else if (sessionType == "gaming") {
        users[userID].gamingSessions.push_back({ startTime, 0 });
    }
    cout << sessionType << " session started for user: " << users[userID].name << "\n";
}


void endSession(const string& userID, const string& sessionType) {
    time_t endTime = time(nullptr);
    if (sessionType == "browsing" && !users[userID].browsingSessions.empty()) {
        users[userID].browsingSessions.back().second = endTime;
    }
    else if (sessionType == "gaming" && !users[userID].gamingSessions.empty()) {
        users[userID].gamingSessions.back().second = endTime;
    }
    cout << sessionType << " session ended for user: " << users[userID].name << "\n";
    cout << "Session duration: " << difftime(endTime, users[userID].browsingSessions.back().first) / 60 << " minutes.\n";
}



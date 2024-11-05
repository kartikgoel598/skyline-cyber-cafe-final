#include "menu.h"
#include <iostream>
#include <vector>
#include "user.h" // Assuming this includes functions like registerUser, loginUser, etc.

using namespace std;

void menu1() {
    int option{};
    while (true) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::vector<std::string> titleArt = {
            "$$$$$$\\  $$\\   $$\\ $$\\     $$\\ $$\\       $$$$$$\\ $$\\   $$\\ $$$$$$$$\\                           $$\\                                  $$$$$$\\   $$$$$$\\  $$$$$$$$\\ $$$$$$$$\\ ",
            "$$  __$$\\ $$ | $$  |\\$$\\   $$  |$$ |      \\_$$  _|$$$\\  $$ |$$  _____|                          $$ |                                $$  __$$\\ $$  __$$\\ $$  _____|$$  _____|",
            "$$ /  \\__|$$ |$$  /  \\$$\\ $$  / $$ |        $$ |  $$$$\\ $$ |$$ |             $$$$$$$\\ $$\\   $$\\ $$$$$$$\\   $$$$$$\\   $$$$$$\\        $$ /  \\__|$$ /  $$ |$$ |      $$ |      ",
            "\\$$$$$$\\  $$$$$  /    \\$$$$  /  $$ |        $$ |  $$ $$\\$$ |$$$$$\\          $$  _____|$$ |  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\       $$ |      $$$$$$$$ |$$$$$\\    $$$$$\\    ",
            " \\____$$\\ $$  $$<      \\$$  /   $$ |        $$ |  $$ \\$$$$ |$$  __|         $$ /      $$ |  $$ |$$ |  $$ |$$$$$$$$ |$$ |  \\__|      $$ |      $$  __$$ |$$  __|   $$  __|   ",
            "$$\\   $$ |$$ |\\$$\\      $$ |    $$ |        $$ |  $$ |\\$$$ |$$ |            $$ |      $$ |  $$ |$$ |  $$ |$$   ____|$$ |            $$ |  $$\\ $$ |  $$ |$$ |      $$ |      ",
            "\\$$$$$$  |$$ | \\$$\\     $$ |    $$$$$$$$\\ $$$$$$\\ $$ | \\$$ |$$$$$$$$\\       \\$$$$$$$\\ \\$$$$$$$ |$$$$$$$  |\\$$$$$$$\\ $$ |            \\$$$$$$  |$$ |  $$ |$$ |      $$$$$$$$\\ ",
            " \\______/ \\__|  \\__|    \\__|    \\________|\\______|\\__|  \\__|\\________|       \\_______| \\____$$ |\\_______/  \\_______|\\__|             \\______/ \\__|  \\__|\\__|      \\________|",
            "                                                                                      $$\\   $$ |                                                                             ",
            "                                                                                      \\$$$$$$  |                                                                             ",
            "                                                                                       \\______/                                                                              "
        };

        for (const auto& line : titleArt) {
            std::cout << line << std::endl;
        }

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

void usermenu(alluser& user) {
    const double printCostPerPage = 0.10;
    const double scanCostPerPage = 0.05;

    cout << "Welcome " << user.name << " to Skyline Cyber Café\n";
    int choice;
    bool options = true;

    while (options) {
        cout << "\n1. Internet Browsing" << endl;
        cout << "2. Gaming" << endl;
        cout << "3. Print Pages" << endl;
        cout << "4. Scan Pages" << endl;
        cout << "5. Pay Bill" << endl;
        cout << "6. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

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
            user.totalPrintCost += cost;
            break;
        }
        case 4: {
            int pages;
            cout << "Enter number of pages to scan: ";
            cin >> pages;
            double cost = pages * scanCostPerPage;
            cout << "Total cost for scanning " << pages << " pages: NZD " << cost << endl;
            user.totalScanCost += cost;
            break;
        }
        case 5: {
            double totalBill = user.totalPrintCost + user.totalScanCost;
            cout << "Total Print Cost: NZD " << user.totalPrintCost << endl;
            cout << "Total Scan Cost: NZD " << user.totalScanCost << endl;
            cout << "Total Amount Payable: NZD " << totalBill << endl;
            break;
        }
        case 6:
            cout << "Returning to main menu...\n";
            options = false;
            break;
        default:
            cout << "Invalid option, please try again.\n";
            break;
        }
    }
}

// Admin.cpp
#include "Admin.h"
#include <iostream>
#include <fstream>
#include "menu.h"
#include "user.h"
using namespace std;

bool loginAdmin() {
    string email, password;
    cout << "\nLogin as Admin:\n";
    cout << "Enter admin email: ";
    getline(cin, email);
    cout << "Enter admin password: ";
    getline(cin, password);

    ifstream adminFile("admin.txt");
    if (!adminFile) {
        cout << "Admin credentials file not found.\n";
        return false;
    }

    string storedEmail, storedPassword;
    getline(adminFile, storedEmail);
    getline(adminFile, storedPassword);
    adminFile.close();

    if (email == storedEmail && password == storedPassword) {
        cout << "Admin login successful!\n";
        return true;
    }
    cout << "Invalid admin email or password.\n";
    return false;
}
void viewAllUsers() {
    for (const auto& i : users) {
        cout << "User ID: " << i.second.userID << endl;
        cout << "Name: " << i.second.name << endl;
        cout << "Email: " << i.second.email << endl;
        cout << "-------------------------------\n";
    }
}
void deleteUser() {
    
    string email{};
    cout << "Enter email of the user to be deleted: " << endl;
    getline(cin,email);


    if (users.find(email) == users.end()) {
        cout << "User with the email \"" << email << "\" has not been found" << endl;
        return;
    }

    users.erase(email);
    
    ofstream file("users.txt");
    if (!file){
        cout << "Failed to open the file for writing. Please try again later.\n" << endl;
        return;
    }

    for (const auto& entry : users) {
        const alluser& user = entry.second;
        file << user.name << "\n"
            << user.email << "\n"
            << user.password << "\n"
            << user.userID << "\n"
            << user.joiningDate << "\n";
    }

    file.close();
    cout << "User with email \"" << email << "\" has been deleted from the file.\n";

}
void editUser() {
    string email;
    cout << "Enter the user email to be edited: " << endl;
    getline(cin, email);
    
    auto it = users.find(email);
    if (it == users.end()) {
        cout << "User with the email \"" << email << "\" was not found.\n";
        return;
    }

    alluser& user = it->second;  // Reference to the user object
    int choice;
    cout << "What would you like to edit?\n";
    cout << "1) Name\n2) Email\n3) Password\n4) User ID\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();  // Clear newline after cin

    switch (choice) {
    case 1:
        cout << "Enter new name: ";
        getline(cin, user.name);
        break;
    case 2:
        cout << "Enter new email: ";
        getline(cin, user.email);
        break;
    case 3:
        cout << "Enter new password: ";
        getline(cin, user.password);
        break;
    case 4:
        cout << "Enter new user ID: ";
        getline(cin, user.userID);
        break;
    default:
        cout << "Invalid choice.\n";
        return;
    }

    ofstream file("users.txt");
    if (!file) {
        cout << "Failed to open the file for writing. Please try again later.\n";
        return;
    }

    for (const auto& entry : users) {
        const alluser& updatedUser = entry.second;
        file << updatedUser.name << "\n"
            << updatedUser.email << "\n"
            << updatedUser.password << "\n"
            << updatedUser.userID << "\n"
            << updatedUser.joiningDate << "\n";
    }

    file.close();
    cout << "User information updated successfully.\n";
}

void viewAllBill() {
    // If users are empty, show a message and return
    if (users.empty()) {
        cout << "No users found.\n";
        return;
    }

    // Loop through all users in the 'users' map and display their bill information
    cout << "\n--- View All User Bills ---\n";
    for (const auto& userEntry : users) {
        const alluser& user = userEntry.second;

        // Calculate total bill (printing and scanning)
        double totalBill = user.totalPrintCost + user.totalScanCost;

        // Display user bill information
        cout << "User: " << user.name << " (" << user.email << ")\n";
        cout << "Total Print Cost: NZD " << user.totalPrintCost << endl;
        cout << "Total Scan Cost: NZD " << user.totalScanCost << endl;
        cout << "Total Amount Payable: NZD " << totalBill << endl;
        cout << "-------------------------------\n";
    }
}



void adminMenu() {
    int choice{};
    cout << "ADMIN MENU!!" << endl;
    cout << "1) View all users" << endl;
    cout << "2) Delete a user" << endl;
    cout << "3) Edit a user" << endl;
    cout << "4) View bill of the user" << endl;
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1: 
        viewAllUsers();
        break;
    case 2: 
        deleteUser();
        break;
    case 3:
        editUser();
        break;
    case 4:
        viewAllBill();
        break;
    default:
        cout << "Invalid choice. Please try again.\n";
        break;
    }

}

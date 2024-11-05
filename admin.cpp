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
    else {
        cout << "Opening File: " << endl;
        
        
        cout << "File Opened Sucessfully " << endl; 
    }

    string storedEmail, storedPassword;
    getline(adminFile, storedEmail);
    getline(adminFile, storedPassword);
    adminFile.close();

    if (email == storedEmail && password == storedPassword) {
        cout << "Admin login successful!\n";
        adminMenu();
        return true; // Return true for successful login
    }
    else {
        cout << "Invalid admin email or password.\n";
        return false;
    }
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
    string email;
    cout << "Type the email of the user you want to delete: ";
    getline(cin, email);

    if (users.find(email) == users.end()) {
        cout << "User with the email \"" << email << "\" has not been found.\n";
        return; // Exit if the user is not found
    }

    users.erase(email);
    ofstream file("users.txt");
    if (!file) {
        cout << "File could not load. Please try again.\n";
        return; // Exit if the file cannot be opened
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
    cout << "User with email " << email << " has been deleted from the file.\n";
}

void editUser() {
    string email;
    cout << "Enter the email of the user you want to edit: ";
    getline(cin, email);

    // Check if the user exists
    auto it = users.find(email);
    if (it == users.end()) {
        cout << "User with email \"" << email << "\" not found.\n";
        return;
    }

    // Example structure for editing user information
    alluser& user = it->second;
    cout << "Editing user: " << user.name << endl;
    // Here, you can add prompts to edit user details like name, password, etc.
    // For example:
    cout << "Enter new name (leave blank to keep current): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        user.name = newName;
    }

    // Repeat for other fields you want to edit...
}

void adminMenu() {
    int choice{};
    cout << "ADMIN MENU!!" << endl;
    cout << "1) View all users" << endl;
    cout << "2) Delete a user" << endl;
    cout << "3) Edit a user" << endl;
    cout << "4) Exit\n";

    cin >> choice;
    cin.ignore();
    switch (choice) {
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
        cout << "Exiting admin menu...\n";
        return; // Exit admin menu
    default:
        cout << "Invalid option, please try again.\n";
        break;
    }
}

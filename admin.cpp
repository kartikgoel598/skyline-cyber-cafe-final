// Admin.cpp
#include "Admin.h"
#include <iostream>
#include <fstream>
#include "menu.h"
#include "user.h"
#include <unordered_map>
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
    cout << "type the email of the user which you want to delete: " << endl;
    getline(cin,email);
    if (users.find(email) == users.end()) {
        cout << "user with the email""\ << email << " "\has not been found" << endl;
    }
    users.erase(email);
    ofstream file("users.txt");
    if (!file)
    {
        cout << "file could not load please try again" << endl;
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
    cout << "enter the email of the user you want to edit" << endl;
    getline(cin, email);
    if (users.find(email) == users.end())
    {
        cout << "User with email \"" << email << "\" not found.\n";
        return;
    }
    alluser& user = users[email]; 
    int choice{};
    cout << "\nEditing user: " << user.name << " (" << user.email << ")\n";
    cout << "1) Name" << endl;
    cout << "2) email" << endl;
    cout << "3) password" << endl;
    cout << "4) cancel" << endl;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice) {
    case 1: {
        cout << "enter new name" << endl;
        getline(cin, user.name);
        cout << "name has been succesfully updated" << endl;
           }
    case 2: {
        string newEmail;
        cout << "enter new email :" << endl;
        getline(cin, newEmail);
        if (users.find(newEmail) != users.end() )
        {
            cout << "Email \"" << newEmail << "\" is already in use by another user.\n";
            return;
        }
        users[newEmail] = user; 
        users.erase(email);
        cout << "Email updated successfully.\n";
        break;
    }
    case 3: {
        cout << "enter new password" << endl;
        getline(cin, user.password);
        cout << "password has been successfully updated";
        break;
    }
    case 4: cout << "edit cancelled" << endl;
        return;
    default:
        cout << "invalid choice" << endl;
        return;
    }
    ofstream file("users.txt");
    if (!file)
    {
        cout << "error loading the file";
    }
    for (const auto& entry : users) {
        const alluser& user = entry.second;
        file << user.name << endl
            << user.email << endl
            << user.password << endl
            << user.userID << endl
            << user.joiningDate << endl;
    }
    file.close();
    cout << "User details updated successfully in the file." <<  endl;
   
    
}

void adminMenu() {
    int choice{};
    cout << "ADMIN MENU!!" << endl;
    cout << "1) view all users" << endl;
    cout << "2) delete a user" << endl;
    cout << "3) edit a user" << endl;
    cout << "4) re-cehck the bill of the user" << endl;
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1: viewAllUsers();
        break;
    case 2: deleteUser();
        break;
    case 3: editUser();
        break;
    case 4:
        break;
    default:
        cout << "invalid option" << endl;
        break;
    }

}

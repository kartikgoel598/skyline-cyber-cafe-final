// User.cpp
#include "User.h"
#include <iomanip>
#include <fstream>
#include <string>

unordered_map<string, alluser> users;
double printCostPerPage = 0.20;
double scanCostPerPage = 0.10;
const string filename = "users.txt";
int counter = 0;

string generateUserId() {
     return "user" + to_string(counter++);
}

void loadUsersFromFile() {
    ifstream file(filename);
    if (!file) {
        cout << "No user data file found, starting fresh.\n";
        return;
    }

    string name, email, password,userID;
    time_t joiningDate;

    while (file >> ws && getline(file, name) &&
        getline(file, email) &&
        getline(file, password) &&
        getline(file, userID) &&
        (file >> joiningDate)) {
        alluser user = { name, email, password, userID, joiningDate };
        users[email] = user;
        file.ignore();
    }
    file.close();
}

void saveUserToFile(const alluser& user) {
    ofstream file(filename, ios::app);
    if (file) {
        file << user.name << "\n"
            << user.email << "\n"
            << user.password << "\n"
            << user.userID << "\n"
            << user.joiningDate << "\n";
        file.close();
    }
    else {
        cout << "Error saving user data to file.\n";
    }
}





void registerUser() {
    string name;
    string email;
    string password;
    
    cout << "Enter your name: ";
    getline(cin, name);
    
    while (true) {
        cout << "Enter your email: ";
        getline(cin, email);

        // Basic email validation: contains "@" and "." and within a reasonable length
        if (email.find('@') == string::npos || email.find('.') == string::npos ||
            email.find('@') > email.rfind('.') || email.length() < 5 || email.length() > 50) {
            cout << "Enter a valid email.\n";
        }
        else {
            break;
        }
    }

         

    
    
    

    cout << "Enter your password: ";
    getline(cin, password);
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long.\n";
        return;
    }

    string emailAsUserID = email; // Use email as a unique ID
    if (users.find(emailAsUserID) != users.end()) {
        cout << "User with this email already exists.\n";
        return;
    }

    alluser newUser = { name, email, password, generateUserId(), time(nullptr) };
    users[emailAsUserID] = newUser;
    saveUserToFile(newUser);
    cout << "User registered successfully!\n";
}

bool loginUser() {
    string email, password;
    cout << "\nLogin to your account:\n";
    cout << "Enter user email: ";
    getline(cin, email);
    cout << "Enter user password: ";
    getline(cin, password);
    auto it = users.find(email);
    
    if (it != users.end() && it->second.password == password) {
        cout << "Login successful!\n";
       
        return true;
    }
    cout << "Invalid email or password.\n";
    return false;
}

void startSession(const string& userID) {
    time_t startTime = time(nullptr);
    users[userID].sessions.push_back({ startTime, 0 });
    cout << "Session started for user: " << users[userID].name << "\n";
}

void endSession(const string& userID) {
    time_t endTime = time(nullptr);
    auto& session = users[userID].sessions.back();
    session.second = endTime;

    double duration = difftime(endTime, session.first) / 60;
    cout << "Session ended for user: " << users[userID].name << ", Duration: " << duration << " minutes\n";

    int printPages, scanPages;
    cout << "Enter number of pages printed: ";
    cin >> printPages;
    cout << "Enter number of pages scanned: ";
    cin >> scanPages;

    double printCost = printPages * printCostPerPage;
    double scanCost = scanPages * scanCostPerPage;
    users[userID].totalPrintCost += printCost;
    users[userID].totalScanCost += scanCost;

    cout << fixed << setprecision(2);
    cout << "Total Print Cost: NZD " << printCost << "\n";
    cout << "Total Scan Cost: NZD " << scanCost << "\n";
    cout << "Total Amount Payable: NZD " << (printCost + scanCost) << "\n";
}

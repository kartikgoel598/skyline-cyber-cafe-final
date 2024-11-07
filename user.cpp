// User.cpp
#include "User.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

unordered_map<string, alluser> users;
double printCostPerPage = 0.10;
double scanCostPerPage = 0.05;
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

void isValidEmail(const std::string& email) {
    const std::regex pattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    if (std::regex_match(email, pattern)) {
        std::cout << "Email \"" << email << "\" is valid.\n";
    }
    else {
        std::cout << "Email \"" << email << "\" is invalid. Please press enter to try again.\n";
    }
}
bool isValidPassword(const std::string& password) {
    const std::regex passwordPattern(R"((?=.*[A-Z])(?=.*[a-z])(?=.*\d)(?=.*[!@#$%^&*])[A-Za-z\d!@#$%^&*]{8,})");
    if (std::regex_match(password , passwordPattern))
    {
         std::cout << "Password \"" << password << "\" is valid.\n";
         return true;
    }
    else
    {
        cout << "password must be 8 character long " << endl;
       cout  << "password must have one upeer case letter" << endl;
       cout  << "password must have one lower case letter" << endl;
       cout  << "password must have one digit(1,2,3....)" << endl;
         cout    << "password must have one special letter" << endl;
        return false;
    
    }
}

void registerUser() {
    string name;
    string email;
    string password;
    cout << "Enter your name: ";
    while (true)
    {
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        isValidEmail(email);
        if (users.find(email) != users.end())
        {
            cout << "User with this email: \"" << email << "\" is already registered. Please type a different email.\n";
        }

        else if (!std::regex_match(email, std::regex(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))"))) {
                  continue; 
        }

        else {
            break; 
        }
    }
   
    
    
    while (true)
    {
        cout << "Enter your password: ";
        getline(cin, password);
        if (isValidPassword(password)) {
            break; 
        }
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

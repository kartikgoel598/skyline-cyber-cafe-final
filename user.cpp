// User.cpp
#include "User.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>

unordered_map<string, alluser> users;
const string filename = "users.txt";
int counter{};



const double browsingCostPerMinute = 0.50;
const double gamingCostPerMinute = 0.50;
const double printCostPerPage = 0.30;
const double scanCostPerPage = 0.20;

void calculateBill(const string& userID) {
    if (users.find(userID) == users.end())
    {
        cout << "userID not found" << endl;
        return;
    }
    auto& user = users[userID];
    double totalBrowsingCost = 0.0, totalGamingCost = 0.0;
    double totalPrintingCost = 0.0, totalScanningCost = 0.0;
    double totalCost = 0.0;
        
    for (const auto& session : user.browsingSessions) {
        double duration = difftime(session.second, session.first) / 60; 
        totalBrowsingCost += duration * browsingCostPerMinute;
    }
    for (const auto& session : user.gamingSessions) {
        double duration = difftime(session.second, session.first) / 60; 
        totalGamingCost += duration * gamingCostPerMinute;
    }

    totalPrintingCost = user.totalPrintPages * printCostPerPage;
    totalScanningCost = user.totalScanPages * scanCostPerPage;
    totalCost = totalBrowsingCost + totalGamingCost + totalPrintingCost + totalScanningCost;

    //comment for josh and wilson generating receipt 
    cout << fixed << setprecision(2);
    cout << "\n--- Receipt ---\n";
    cout << "Browsing: " << user.totalBrowsingMinutes << " min x NZD " << browsingCostPerMinute << " = NZD " << totalBrowsingCost << endl;
    cout << "Gaming: " << user.totalGamingMinutes << " min x NZD " << gamingCostPerMinute << " = NZD " << totalGamingCost << endl;
    cout << "Printing: " << user.totalPrintPages << " pages x NZD " << printCostPerPage << " = NZD " << totalPrintingCost << endl;
    cout << "Scanning: " << user.totalScanPages << " pages x NZD " << scanCostPerPage << " = NZD " << totalScanningCost << endl;
    cout << "Total Amount Payable: NZD " << totalCost << endl;

    // Save bill history
    saveBillHistory(userID, totalBrowsingCost, totalGamingCost, totalPrintingCost, totalScanningCost, totalCost);
}

void saveBillHistory(const string& userID, double browsingCost, double gamingCost, double printingCost, double scanningCost, double totalCost) {
    ofstream file("bills.txt", ios::app);
    if (file) {
        file << userID << " " << endl;
        file << "browsing cost is:" << browsingCost << " " << "gaming cost is:" << gamingCost << " " << "printing cost is:" << printingCost << " " << "scanning cost is:" << scanningCost << " "  << "total cost is:" << totalCost << "\n";
        file.close();
    }
    else {
        cout << "Error saving bill history.\n";
    }
}

string generateUserId(const string& email) {
     return "User" + to_string(users.size() + 1);
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
        std::cout << "Email \"" << email << "\" is invalid. Please try again\n";
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
       cout << "password must have one upeer case letter" << endl;
       cout << "password must have one lower case letter" << endl;
       cout << "password must have one digit(1,2,3....)" << endl;
       cout << "password must have one special letter" << endl;
        return false;
    
    }
}

void registerUser() {
    string name;
    string email;
    string password;
    cout << "Enter your name: ";
    getline(cin, name);
    while (true)
    {
        //getline(cin, name);
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
    
    /****/
    string userID = generateUserId(email);

    alluser newUser = { name, email, password, userID, time(nullptr) };
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

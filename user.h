#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
#include <regex>

using namespace std;

struct alluser {
    string name;
    string email;
    string password;
    string userID;
    time_t joiningDate{};
    vector<pair<time_t, time_t>> sessions;
    vector<pair<time_t, time_t>> browsingSessions;
    vector<pair<time_t, time_t>> gamingSessions;
    double totalBrowsingMinutes = 0.0;
    double totalGamingMinutes = 0.0;
    int totalPrintPages = 0;
    int totalScanPages = 0;
    double totalPrintCost = 0.0;
    double totalScanCost = 0.0;
};

unordered_map<string, alluser> users;
const extern double printCostPerPage;
const extern double scanCostPerPage;


void saveBillHistory(const string& userID, double browsingCost, double gamingCost, double printingCost, double scanningCost, double totalCost);
void calculateBill(const string& userID);

string generateUserId(const std::string& email);
void loadUsersFromFile();
void saveUserToFile(const alluser& user);
void isValidEmail(const std::string& email);
bool isValidPassword(const std::string& password);
void registerUser();
bool loginUser();
void startSession(const string& userID);
void endSession(const string& userID);
#endif 

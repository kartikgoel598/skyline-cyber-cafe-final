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
    double totalBrowsingMinutes = 0;
    double totalGamingMinutes = 0;
    double totalPrintPages = 0;
    double totalScanPages = 0;
    double totalPrintCost = 0;
    double totalScanCost = 0;
};

extern unordered_map<string, alluser> users;
extern double printCostPerPage;
extern double scanCostPerPage;



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

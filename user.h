#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

struct Session {
    time_t startTime;
    time_t endTime;
};


struct alluser {
    string name;
    string email;
    string password;
    string userID;
    string joiningDate{};
    vector<pair<time_t, time_t>> sessions;
    double totalPrintCost = 0;
    double totalScanCost = 0;
};

extern unordered_map<string, alluser> users;
extern double printCostPerPage;
extern double scanCostPerPage;

string generateUserId();
void loadUsersFromFile();
void saveUserToFile(const alluser& user);
void registerUser();
bool loginUser();
void startSession(const string& userID);
void endSession(const string& userID);

#endif 

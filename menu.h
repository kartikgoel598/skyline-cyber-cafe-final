#pragma once
#ifndef MENU_H
#define MENU_H

#include "User.h"
#include "Admin.h"

void menu1();
void usermenu(const alluser& user);
void endSession(const string& userID, const string& sessionType);
void startSession(const string& userID, const string& sessionType);

#endif // MENU_H


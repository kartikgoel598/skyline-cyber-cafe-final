#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <regex>


#include "user.h"
#include "menu.h"
#include "admin.h"



int main() {
	loadUsersFromFile();
	menu1();
	return 0;

}
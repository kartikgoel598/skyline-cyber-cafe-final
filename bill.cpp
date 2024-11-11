#include <fstream>
#include <iostream>

void Billdoc(std::string email,double print, double scan,  double internet, double debt) {
    std::ofstream file("bill.txt", std::ios::app); 

    if (file.is_open()) {
        file << "Account: " << email << std::endl;
        file << "Print: $" << print << std::endl; 
        file << "Scan: $" << scan << std::endl;
        
        file << "Internet: $" << internet << std::endl;
        file << std::endl;
        file << "Total Outstanding: $" << debt << std::endl;
        file << "_____________________________________________________" << std::endl; 
        file << std::endl; 
        
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

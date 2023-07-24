#include "./Checker.hpp"
#include "./Parse.hpp"
#include "./Solver.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// __________________________________________________________________
void Checker::readDataInput(const std::string &options,
                  const std::string &constraints) {             
}

// __________________________________________________________________
void Checker::helperFunctionBuildData() {
}

// __________________________________________________________________
void Checker::readDataModel(const std::string &models) {
}

// __________________________________________________________________
void Checker::setModel(std::vector<std::string> param) {
}

// __________________________________________________________________
int Checker::ifCondition1Valid() {
    return 0;
}

// __________________________________________________________________
int Checker::ifCondition2Valid() {
    return 0;
}

// __________________________________________________________________
int Checker::ifCondition3Valid() {
    return 0;
}

// __________________________________________________________________
int Checker::ifOptionValid() {
    //Check option file.
    return 0;
}

// __________________________________________________________________
int Checker::ifConstraintValid() {
    //Check if empty .constraints

    return 0;
}

// __________________________________________________________________
bool Checker::andTheRest(int i) {
    return (file2_[i + 1] == "RAM" || 
            file2_[i + 1] == "Bildschirm" || 
            file2_[i + 1] == "Prozessor" || 
            file2_[i + 1] == "");
}

// __________________________________________________________________
bool Checker::ifModel() {
    if (ifCondition1Valid() == 0 && 
        ifCondition2Valid() == 0 && 
        ifCondition3Valid() == 0) {
        std::cout << "VERIFIED" << std::endl;
        return true;
    } else {
        errorCode_ = 30;
        std::cout << "UNVERIFIED" << std::endl;
        return false;
    }
}

// __________________________________________________________________
bool Checker::ifOptionAndConstraints() {
    if (ifConstraintValid() == 0 &&
    ifOptionValid() == 0) {
        return true;
    } else {
        if (ifOptionValid() != 0) {
            std::cerr << "Not possible .options" << std::endl;
            errorCode_ = ifOptionValid();
        }
        if (ifConstraintValid() != 0) {
            std::cerr << "Not possible .constaints" << std::endl;
            errorCode_ = ifConstraintValid();
        }
        return false;
    }
}



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
    Parse p;
    file1_ = p.ReturnVectorOfWord(options);
    file2_ = p.ReturnVectorOfWord(constraints);               
}

// __________________________________________________________________
void Checker::helperFunctionBuildData() {
    Solver s;
    s.getDataFromOption(file1_);
    s.getDataFromConstraint(file2_);
    constraints_ = s.getConstraint();
    option_ = s.getOption(); 
}

// __________________________________________________________________
void Checker::readDataModel(const std::string &models) {
    helperFunctionBuildData();
    Parse p;
    file3_ = p.ReturnVectorOfWord(models);
    setModel(file3_);
}

// __________________________________________________________________
void Checker::setModel(std::vector<std::string> param) {
    for (int i = 0; i < (int)param.size(); i++) {
        std::string pro = "" ,ram = "", bild = "";
        while ((i < (int)param.size() - 1) && (param[i] != "\n" )) {
            if (param[i] == "Prozessor") {
                pro = param[i+1];
            }
            if (param[i] == "RAM") {
                ram = param[i+1];
            }
            if (param[i] == "Bildschirm") {
                bild = param[i+1];
            }
            i = i + 2;
        }
    model tempModel = {pro, ram, bild};
    models_.push_back(tempModel);
    }
}

// __________________________________________________________________
int Checker::ifCondition1Valid() {
    for (int i = 0; i < (int)models_.size(); i++) {
        if (models_[i].prozessor_ == "" || 
            models_[i].ram_ == "" || 
            models_[i].bildschirm_ == "") {
                std::cerr << "Prozessor: " << models_[i].prozessor_ << 
                             "RAM: " << models_[i].ram_ <<
                             "Bildschirm: " << models_[i].bildschirm_ << std::endl;
                if (models_[i].prozessor_ == "") {
                    std::cerr << "Prozessor is not given" << std::endl;
                }
                if (models_[i].ram_ == "") {
                    std::cerr << "RAM is not given" << std::endl;
                }
                if (models_[i].bildschirm_ == "") {
                    std::cerr << "Bildschirm is not given" << std::endl;
                }
                return 30;
        }
    }
    return 0;
}

// __________________________________________________________________
int Checker::ifCondition2Valid() {
    // check if constraint file empty.
    if ((int)file2_.size() == 1 && file2_[0] == "") {
        return 0;
    }
    for (int i = 0; i < (int)models_.size(); i++) {
        for (int j = 0; j < (int)constraints_.size(); j++) {
            if ((models_[i].prozessor_ == constraints_[j].prozessor_ || constraints_[j].prozessor_ == "") && 
            (models_[i].ram_ == constraints_[j].ram_ || constraints_[j].ram_ == "") && 
            (models_[i].bildschirm_ == constraints_[j].bildschirm_ || constraints_[j].bildschirm_ == "")) {
                std::cerr << "Prozessor: " << models_[i].prozessor_ << 
                             ", RAM: " << models_[i].ram_ <<
                             ", Bildschirm: " << models_[i].bildschirm_ << std::endl;
                std::cerr << "Not compatible with Constraints" << std::endl;
                return 30;
            }
        }
    }
    return 0;
}

// __________________________________________________________________
int Checker::ifCondition3Valid() {
    bool ifFound = false;
    for (int i = 0; i < (int)models_.size(); i++) {
        for (int j = 0; j < (int)option_.prozessor_.size(); j++) {
            if (models_[i].prozessor_ == option_.prozessor_[j]) {
                ifFound = true;
            }
        }
        if (!ifFound) {
            std::cerr << models_[i].prozessor_ << " : is not provided in .options file" << std::endl;
            return 30;
        }
        ifFound = false;
        for (int j = 0; j < (int)option_.ram_.size(); j++) {
            if (models_[i].ram_ == option_.ram_[j]) {
                ifFound = true;
            }
        }
        if (!ifFound) {
            std::cerr << models_[i].ram_ << " : is not provided in .options file" << std::endl;
            return 30;
        }
        ifFound = false;
        for (int j = 0; j < (int)option_.bildschirm_.size(); j++) {
            if (models_[i].bildschirm_ == option_.bildschirm_[j]) {
                ifFound = true;
            }
        }
        if (!ifFound) {
            std::cerr << models_[i].bildschirm_ << " : is not provided in .options file" << std::endl;
            return 30;
        }
        ifFound = false;
    }

    for (int i = 0; i < (int)constraints_.size(); i++) {
        if (constraints_[i].prozessor_ == "") {
            ifFound = true;
        } else {
            for (int j = 0; j < (int)option_.prozessor_.size(); j++) {
                if (constraints_[i].prozessor_ == option_.prozessor_[j]) {
                    ifFound = true;
                }
            }
        }

        if (!ifFound) {
            std::cerr << constraints_[i].prozessor_ << " : is not provided in .options file" << std::endl;
            return 30;
        }
        ifFound = false;

        if (constraints_[i].ram_ == "") {
            ifFound = true;
        } else {
            for (int j = 0; j < (int)option_.ram_.size(); j++) {
                if (constraints_[i].ram_ == option_.ram_[j]) {
                    ifFound = true;
                }
            }
        }

        if (!ifFound) {
            std::cerr << constraints_[i].ram_ << " : is not provided in .options file" << std::endl;
            return 30;
        }
        ifFound = false;
        if (constraints_[i].bildschirm_ == "") {
            ifFound = true;
        } else {
            for (int j = 0; j < (int)option_.bildschirm_.size(); j++) {
                if (constraints_[i].bildschirm_ == option_.bildschirm_[j]) {
                    ifFound = true;
                }
            }
        }
        if (!ifFound) {
            std::cerr << constraints_[i].bildschirm_ << " : is not provided in .options file" << std::endl;
            return 30;
        }
        ifFound = false;

    }
    return 0;
}

// __________________________________________________________________
int Checker::ifOptionValid() {
    //Check option file.
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    //Valid .option must be at least 6 elements.
    //At least 3 value and 3 options.
    if ((int)file1_.size() < 6) {
        return 10;
    }
    for (int i = 0; i < (int)file1_.size() - 1; i++) {
        if ((file1_[i] == "Prozessor") && (file1_[i + 1] != "")) {
            flag1 = true;
        }
        if (file1_[i] == "RAM" && (file1_[i + 1] != "")) {
            flag2 = true;
        }
        if (file1_[i] == "Bildschirm" && (file1_[i + 1] != "")) {
            flag3 = true;
        }
    }
    if (flag1 && flag2 && flag3) {
        return 0;
    }
    return 10;
}

// __________________________________________________________________
int Checker::ifConstraintValid() {
    //Check if empty .constraints
    if (file2_.size() == 1 && file2_[0] == "") {
        return 0;
    }
    //must be at least pair of option and value.
    //so size always must even number.
    if (((int)file2_.size() % 2) != 0) {
        return 20;
    }
    //Check for missing value.
    for (int i = 0; i < (int)file2_.size() - 1; i++) {
        if ((file2_[i] == "Prozessor") && andTheRest(i)) {
            return 20;
        }
        if (file2_[i] == "RAM" && andTheRest(i)) {
            return 20;
        }
        if (file2_[i] == "Bildschirm" && andTheRest(i)) {
            return 20;
        }
    }
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



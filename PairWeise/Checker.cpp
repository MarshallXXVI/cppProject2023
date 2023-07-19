#include "./Checker.hpp"
#include "./Parse.hpp"
#include "./Solver.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// __________________________________________________________________
void Checker::readData(const std::string &options,
                  const std::string &constraints,
                  const std::string &models) 
                  {
    Parse p;
    std::vector<std::string> file1 = p.ReturnVectorOfWord(options);
    std::vector<std::string> file2 = p.ReturnVectorOfWord(constraints);
    std::vector<std::string> file3 = p.ReturnVectorOfWord(models);
    Solver s;
    s.getDataFromOption(file1);
    s.getDataFromConstraint(file2);
    constraints_ = s.getConstraint();
    option_ = s.getOption();
    setModel(file3);
    // for (int i = 0; i < (int)models_.size(); i++) {
    //     std::cout << models_[i].prozessor_;
    // }
    // for (int i = 0; i < (int)constraints_.size(); i++) {
    //     std::cout << constraints_[i].prozessor_;
    // }
    // for (int i = 0; i < (int)file3.size(); i++) {
    //     std::cout << file3[i];
    // }
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
    for (int i = 0; i < (int)models_.size(); i++) {
        for (int j = 0; j < (int)constraints_.size(); j++) {
            if ((models_[i].prozessor_ == constraints_[j].prozessor_ || constraints_[j].prozessor_ == "") && 
            (models_[i].ram_ == constraints_[j].ram_ || constraints_[j].ram_ == "") && 
            (models_[i].bildschirm_ == constraints_[j].bildschirm_ || constraints_[j].bildschirm_ == "")) {
                std::cerr << "Prozessor: " << models_[i].prozessor_ << 
                             "RAM: " << models_[i].ram_ <<
                             "Bildschirm: " << models_[i].bildschirm_ << std::endl;
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
void Checker::Check() {
    if (ifCondition1Valid() == 0 && ifCondition2Valid() == 0 && ifCondition3Valid() == 0) {
        std::cout << "VERIFIED" << std::endl;
    } else {
        std::cout << "UNVERIFIED" << std::endl;
    }

} 

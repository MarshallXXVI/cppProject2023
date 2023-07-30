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
    p.ReadDataFromFile(options, constraints);
    optionFile = p.getOptions();
    constraintFile = p.getConstraints();
    s.constraintsCopy_ = constraintFile;
    s.optionCopy_ = optionFile;
    s.generateTuple();         
}

// __________________________________________________________________
void Checker::readDataModel(const std::string &models) {
    Parse p;
    modelFile = p.vectorTransform(p.ReturnVectorOfWord(models));
    setModel();
}

// __________________________________________________________________
void Checker::setModel() {
  for (int i = 0; i < (int)modelFile.size(); i++) {
    std::vector<Tuple> tempVecTuple;
    int j = 0;
    int k = 1;
    while (j < (int)modelFile[i].size() - 1 && k < (int)modelFile[i].size()) {
      //std::cout << (int)constraintsCopy_[i].size() << std::endl;
      std::string temp1;
      std::string temp2;
      Tuple tempTuple = {modelFile[i][j].c_str(), modelFile[i][k].c_str()};
      //std::cout << "(" << tempTuple.value_.size() << ")" << std::endl;
      tempVecTuple.push_back(tempTuple);
      j = j + 2;
      k = k + 2;
    }
    Model.push_back(tempVecTuple);
  }
}

// __________________________________________________________________
int Checker::ifConditionValid() {
    std::vector<std::string> possibleOption;
    for (int n = 0; n < (int)optionFile.size(); n++) {
        possibleOption.push_back(optionFile[n][0]);
    }
    for (int i = 0; i < (int)Model.size(); i++) {
        if (!ifThisCongifurationValid(Model[i], possibleOption)) {
            for (int j = 0; j < (int)Model[i].size(); j++) {
                std::cout << "(" << Model[i][j].Option_ << "," << Model[i][j].Value_ << ")";
                std::cout << " : this Configuration is invalid" << std::endl;
            }
            std::cout << std::endl;
            return 30;
        }
        if (s.ifMatchConstraints(Model[i])) {
            for (int j = 0; j < (int)Model[i].size(); j++) {
                std::cout << "(" << Model[i][j].Option_ << "," << Model[i][j].Value_ << ")";
                std::cout << " : this Configuration violated .constraints" << std::endl;
            }
            std::cout << std::endl;
            return 30;
        }
    }

    return 0;
}

// __________________________________________________________________
bool Checker::ifThisCongifurationValid(std::vector<Tuple> param, std::vector<std::string> possibleOption) {
    for (int i = 0; i < (int)param.size(); i++) {
        std::string tempOption = param[i].Option_;
        for (int j = 0; j < (int)possibleOption.size(); j++) {
            if (tempOption == possibleOption[j]) {
                for (int k = 1; k < (int)param.size(); k++) {
                    if (param[i].Value_ == optionFile[j][k]) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// __________________________________________________________________
int Checker::ifOptionValid() {
    int count = 0;
    for (int i = 0; i < (int)optionFile.size(); i++) {
        for (int j = 0; j < (int)optionFile[i].size(); j++) {
            count++;
        }
    }
    if (count < 4) {
        return 10;
    }
    //Check option file.
    if ((int)optionFile.size() < 2 && (int)optionFile[0].size() < 2 && (int)optionFile[1].size() < 2) {
        return 10;
    }
    if ((int)optionFile.size() == 2 && optionFile[1].empty()) {
        return 10;
    }
    std::vector<std::string> forbidenValues;
    for (int i = 0; i < (int)optionFile.size(); i++) {
        std::string forbidenValue = optionFile[i][0]; // copy string of Option.
        forbidenValues.push_back(forbidenValue); // push each Option to forbindenValues.
        for (int j = 1; j < (int)optionFile[i].size(); j++) { // iteratate each Value of options.
            for (int k = 0; k < (int)forbidenValues.size(); k++) { // iterate each Option in forbindenValues.
                if (optionFile[i][j] == forbidenValues[k]) { // if any Value of any Option match in forbindenValues.
                    return 10; // return error code.
                }
            }
        }
    }
    return 0;
}

// __________________________________________________________________
int Checker::ifConstraintValid() {
    constraintFile.shrink_to_fit();
    if (constraintFile[0][0] == "") {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < (int)constraintFile.size(); i++) {
        for (int j = 0; j < (int)constraintFile[i].size(); j++) {
            count++;
        }
    }
    if (count % 2 != 0) {
        return 20;
    }
    tupleConstraintsCopy = s.getTupleConstraints();
    for (int i = 0; i < (int)tupleConstraintsCopy.size(); i++) {
        for (int j = 0; j < (int)tupleConstraintsCopy[i].size(); j++) {
            TupleForConstraints tempTuples = tupleConstraintsCopy[i][j];
            if (!ifThisTupleOfConstraintValid(tempTuples)) {
                return 20;
            }
        }
    }
    return 0;
}

// __________________________________________________________________
bool Checker::ifThisTupleOfConstraintValid(TupleForConstraints param) {
    bool flag = false;
    for (int k = 0; k < (int)optionFile.size(); k++) {
        if (param.Option_ == optionFile[k][0]) {
            flag = true;
            for (int l = 1; l < (int)optionFile[k].size(); l++) {
                if (param.value_ == optionFile[k][l] && flag) {
                    return true;
                }
            }
        }
    }
    return false;
}
// __________________________________________________________________
bool Checker::ifModel() {
    if (ifConditionValid() == 0) {
        std::cout << "VERIFIED" << std::endl;
        return true;
    } else {
        errorCode_ = ifConditionValid();
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



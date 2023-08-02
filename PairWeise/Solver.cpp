#include "./Solver.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <random>
#include <filesystem>
#include <algorithm>

// __________________________________________________________________
void Solver::getDataFromOption(std::vector<std::vector<std::string>> param) {
  optionCopy_ = param;
}

void Solver::getDataFromConstraint(std::vector<std::vector<std::string>> param) {
  constraintsCopy_ = param;
}

// __________________________________________________________________
void Solver::generateModells(std::string const &file3) {
  generateTuple();
  std::ofstream MyFile1("temp.models");
  std::vector<Tuple> currentPermutation;
  generatePermutations(tupleOption, currentPermutation, 0, MyFile1);
  MyFile1.close();
  std::ofstream MyFileCopy(file3);
  std::string tempString = readAndTrimTrailingSpaces("temp.models");
  MyFileCopy << tempString;
  MyFileCopy.close();
  std::remove("temp.models");
}


// __________________________________________________________________
void Solver::generatePermutations(const std::vector<std::vector<Tuple>>& data,
                          std::vector<Tuple>& currentPermutation,
                          int categoryIndex,
                          std::ofstream& FILE)
{
    if (categoryIndex == (int)data.size()) {
      std::vector<Tuple> tempConfigBuffer;
      //std::cout << "here" << std::endl;
        // Print the current permutation
        for (size_t i = 0; i < currentPermutation.size(); ++i) {
            //std::cout << currentPermutation[i].Option_ << "," << currentPermutation[i].Value_;
            tempConfigBuffer.push_back(currentPermutation[i]);
            // if (i < currentPermutation.size() - 1) {
            //     //std::cout << ",";
            // }
        }
        //std::cout << std::endl;
        //std::cout << "here" << std::endl;
        //std::cout << thisConfigToString(tempConfigBuffer);
        if (!ifMatchConstraints(tempConfigBuffer)) {
          FILE << thisConfigToString(tempConfigBuffer);
        }
        return;
    }

    for (const auto& item : data[categoryIndex]) {
        currentPermutation.push_back(item);
        generatePermutations(data, currentPermutation, categoryIndex + 1, FILE);
        currentPermutation.pop_back();
    }
}


// __________________________________________________________________
std::string Solver::thisConfigToString(std::vector<Tuple> tempConfig) {
  std::string tempString;
  for (int i = 0; i < (int)tempConfig.size(); i++) {
      if (i == (int)tempConfig.size() - 1) {
          tempString += tempConfig[i].Option_ + "," + tempConfig[i].Value_;
        } else {
          tempString += tempConfig[i].Option_ + "," + tempConfig[i].Value_ + ",";
        }
    }
    tempString += "\n";
    return tempString;
}

// __________________________________________________________________
void Solver::generateTuple() {
  for (int i = 0; i < (int)optionCopy_.size(); i++) {
    std::vector<Tuple> tempVecPair;
    for (int j = 1; j < (int)optionCopy_[i].size(); j++) {
      Tuple tempPair = {optionCopy_[i][0], optionCopy_[i][j]};
      tempVecPair.push_back(tempPair);
    }
    tupleOption.push_back(tempVecPair);
  }

  for (int i = 0; i < (int)constraintsCopy_.size(); i++) {
    std::vector<TupleForConstraints> tempVecTuple;
    int j = 0;
    int k = 1;
    while (j < (int)constraintsCopy_[i].size() - 1 && k < (int)constraintsCopy_[i].size()) {
      //std::cout << (int)constraintsCopy_[i].size() << std::endl;
      std::string temp1;
      std::string temp2;
      TupleForConstraints tempTuple = {constraintsCopy_[i][j].c_str(), constraintsCopy_[i][k].c_str(), false};
      //std::cout << "(" << tempTuple.value_.size() << ")" << std::endl;
      tempVecTuple.push_back(tempTuple);
      j = j + 2;
      k = k + 2;
    }
    tupleConstraints.push_back(tempVecTuple);
  }
  //just for debug.
  // for (int i = 0; i < (int)tupleOption.size(); i++) {
  //   for (int j = 0; j < (int)tupleOption[i].size(); j++) {
  //     std::cout << "(" << tupleOption[i][j].Option_ << "," << tupleOption[i][j].Value_ << ")" << std::endl;
  //   }
  // }

  // for (int i = 0; i < (int)tupleConstraints.size(); i++) {
  //   for (int j = 0; j < (int)tupleConstraints[i].size(); j++) {
  //     std::cout << "<" << tupleConstraints[i][j].Option_ << "," << tupleConstraints[i][j].value_ << ">" << std::endl;
  //   }
  // }
}

// __________________________________________________________________
bool Solver::ifMatchConstraints(std::vector<Tuple> param) {
  if (tupleConstraints.size() == 1 && tupleConstraints[0].empty()) {
    return false;
  }
  resetConstraints();
  for (int l = 0; l < (int)tupleConstraints.size(); l++) {
    for (int k = 0; k < (int)tupleConstraints[l].size(); k++) {
      for (int i = 0; i < (int)param.size(); i++) {
        if (param[i].Option_ == tupleConstraints[l][k].Option_) {
          //std::cout << "checking for :" << tupleConstraints[l][k].Option_  << "," << param[i].Option_ << std::endl;
          //std::cout << "compare value :" << tupleConstraints[l][k].value_  << "," << param[i].Value_ << std::endl;
          if (param[i].Value_ == tupleConstraints[l][k].value_) {
            tupleConstraints[l][k].Match = true;
          }
        }
      }
    }
    std::vector<bool> tempBool;
    for (int k = 0; k <(int)tupleConstraints[l].size(); k ++) {
      //std::cout << tupleConstraints[l][k].Match << std::endl;
      tempBool.push_back(tupleConstraints[l][k].Match);
    }
    int sum = std::accumulate(std::begin(tempBool), std::end(tempBool), 0);
    if (sum == (int)tempBool.size()) {
      //std::cout << "this configuration match the constraints" << std::endl;
      return true;
    }
  }
  return false;
}

// __________________________________________________________________
void Solver::resetConstraints() {
  for (int l = 0; l < (int)tupleConstraints.size(); l++) {
    for (int k = 0; k < (int)tupleConstraints[l].size(); k++) {
      tupleConstraints[l][k].Match = false;
    }
  }
}

// __________________________________________________________________
std::string Solver::readAndTrimTrailingSpaces(std::string const &file) {
    std::ifstream thisFile(file);
    std::string   buffer(std::istreambuf_iterator<char>{thisFile}, {});

    while (!buffer.empty() && std::isspace(buffer.back()))
        buffer.pop_back();

    return buffer;
}

// __________________________________________________________________
void Solver::handleInputFiles(std::string const &file1, std::string const &file2) {
  std::string tempString1 = readAndTrimTrailingSpaces(file1);
  std::ofstream MyFile1(file1);
  MyFile1 << tempString1;
  MyFile1.close();

  std::string tempString2 = readAndTrimTrailingSpaces(file2);
  std::ofstream MyFile2(file2);
  MyFile2 << tempString2;
  MyFile2.close();
}
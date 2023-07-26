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
void Solver::generateModells() {
  std::ofstream MyFile1("a.models");
  int incrementer = 0;
  srand(time(NULL));
  while (incrementer < 1000) {
    std::vector<Tuple> tempConfig;
    // can do smarter way but how ?
    // in forum Solver functional weise.
    for (int i = 0; i < (int)tupleOption.size(); i++) {
      int size = (int)tupleOption[i].size();
      int j;
      j = rand() % size;
      tempConfig.push_back(tupleOption[i][j]);
    }
    if(!ifMatchConstraints(tempConfig)) {
      MyFile1 << thisCofigToString(tempConfig);
      //incrementer++;
    }
    incrementer++;
  }
  MyFile1.close();
}

// __________________________________________________________________
std::string Solver::thisCofigToString(std::vector<Tuple> tempConfig) {
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
    //Problem happen here.
    while (j < (int)constraintsCopy_[i].size() - 1 && k < (int)constraintsCopy_[i].size()) {
      //std::cout << (int)constraintsCopy_[i].size() << std::endl;
      std::string temp1;
      std::string temp2;
      TupleForConstraints tempTuple = {constraintsCopy_[i][j].c_str(), constraintsCopy_[i][k].c_str(), false};
      std::cout << "(" << tempTuple.value_.size() << ")" << std::endl;
      tempVecTuple.push_back(tempTuple);
      j = j + 2;
      k = k + 2;
    }
    tupleConstraints.push_back(tempVecTuple);
  }
  // just for debug.
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
  for (int l = 0; l < (int)tupleConstraints.size(); l++) {
    for (int k = 0; k < (int)tupleConstraints[l].size(); k++) {
      for (int i = 0; i < (int)param.size(); i++) {
        if (param[i].Option_ == tupleConstraints[l][k].Option_) {
          std::cout << "checking for :" << tupleConstraints[l][k].Option_  << "," << param[i].Option_ << std::endl;
          std::cout << "compare value :" << tupleConstraints[l][k].value_  << "," << param[i].Value_ << std::endl;
          if (param[i].Value_ == tupleConstraints[l][k].value_) {
            tupleConstraints[l][k].Match = true;
          }
        }
      }
    }
    std::vector<bool> tempBool;
    for (int k = 0; k <(int)tupleConstraints[l].size(); k ++) {
      std::cout << tupleConstraints[l][k].Match << std::endl;
      tempBool.push_back(tupleConstraints[l][k].Match);
    }
    int sum = std::accumulate(std::begin(tempBool), std::end(tempBool), 0);
    if (sum == (int)tempBool.size()) {
      std::cout << "this configuration match the constraints" << std::endl;
      return true;
    }
  }
  return false;
}

// __________________________________________________________________
std::string Solver::readAndTrimTrailingSpaces(std::string const & file)
{
    std::ifstream thisFile(file);
    std::string   buffer(std::istreambuf_iterator<char>{thisFile}, {});

    while (!buffer.empty() && std::isspace(buffer.back()))
        buffer.pop_back();

    return buffer;
}
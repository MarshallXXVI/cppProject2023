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
  std::vector<Tuple> tempConfig;
  for (int i = 0; i < (int)tupleOption.size(); i++) {
    int size = (int)tupleOption[i].size();
    int j;
    srand(time(NULL));
    j = rand() % size;
    tempConfig.push_back(tupleOption[i][j]);
  }
  std::cout << ifMatchConstraints(tempConfig);
  for (int i = 0; i < (int)tempConfig.size(); i++) {
    if (i == (int)tempConfig.size() - 1) {
      std::cout << tempConfig[i].Option_ << "," << tempConfig[i].Value_;
    } else {
      std::cout << tempConfig[i].Option_ << "," << tempConfig[i].Value_ << ",";
    }
  }
  std::cout << std::endl;
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
    for (int j = 0; j < (int)constraintsCopy_[i].size() - 1; j++) {
      std::string temp1 = constraintsCopy_[i][j];
      // problem is here.
      std::string temp2 = constraintsCopy_[i][j+1];
      std::cout << temp2 << ">" <<std::endl;
      TupleForConstraints tempTuple = {temp1, temp2};
      tempVecTuple.push_back(tempTuple);
      if (j < (int)constraintsCopy_[i].size() - 1) {
        j++;
      }
    }
    tupleConstraints.push_back(tempVecTuple);
  }

  for (int i = 0; i < (int)tupleOption.size(); i++) {
    for (int j = 0; j < (int)tupleOption[i].size(); j++) {
      std::cout << "(" << tupleOption[i][j].Option_ << "," << tupleOption[i][j].Value_ << ")" << std::endl;
    }
  }

  for (int i = 0; i < (int)tupleConstraints.size(); i++) {
    for (int j = 0; j < (int)tupleConstraints[i].size(); j++) {
      std::cout << "<" << tupleConstraints[i][j].Option_ << "," << tupleConstraints[i][j].Value_ << ">" << std::endl;
    }
  }
}

// __________________________________________________________________
bool Solver::ifMatchConstraints(std::vector<Tuple> param) {
  //std::cout << tupleConstraints.size() << std::endl;
  for (int l = 0; l < (int)tupleConstraints.size(); l++) {
    for (int k = 0; k < (int)tupleConstraints[l].size(); k++) {
      for (int i = 0; i < (int)param.size(); i++) {
        if (param[i].Option_ == tupleConstraints[l][k].Option_) {
          std::cout << "checking for :" << tupleConstraints[l][k].Option_  << "," << param[i].Option_ << std::endl;
          std::cout << "compare value :" << tupleConstraints[l][k].Value_  << "," << param[i].Value_ << std::endl;
          if (param[i].Value_ == tupleConstraints[l][k].Value_) {
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
    std::all_of(tempBool.begin(), tempBool.end(), [](bool v) { return v; });
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
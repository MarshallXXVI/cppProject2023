#ifndef CHECKER_H_
#define CHECKER_H_

#include "./Solver.hpp"
#include "./Parse.hpp"
#include <string>
#include <utility>
#include <vector>

class Checker {

public:
  // read data from file.
  void readDataInput(const std::string &options,
                     const std::string &constraints);
  // reading data after model is generated.
  void readDataModel(const std::string &models);
  // this function calls all checker methods are valid.
  // ifModel() == 0; returns error code 30.
  bool ifModel();
  // if a.option is invalid; returns error code 10.
  // if a.constraints is invalid; returns error code 20.
  bool ifOptionAndConstraints();
  // error code returned at end of runtime.
  int errorCode_;

private:
  // utilize solver-method as a helper function
  Solver s;
  // utilize parser-method as a helper function
  Parse p;
  // class properties.
  std::vector<std::vector<std::string>> optionFile;
  std::vector<std::vector<std::string>> constraintFile;
  std::vector<std::vector<std::string>> modelFile;
  std::vector<std::vector<TupleForConstraints>> tupleConstraintsCopy;
  std::vector<std::vector<Tuple>> Model;
  // setter of model field.
  void setModel();
  // check whether each configuration in model is valid.
  // in every configuration each option has to be unique.
  // in every configuration each option should not violate constraints.
  // in every configuration each option has a value.
  // in every configuration all options are included.
  int ifConditionValid();
  // check if .option is valid (at least 2 options & values provided)
  int ifOptionValid();
  // constraints only contain combinations of options and values from
  // .options file
  int ifConstraintValid();
  // helper function;
  int ifThisTupleOfConstraintValid(TupleForConstraints param);
  bool ifThisCongifurationValid(std::vector<Tuple> param);
};
#endif // CHECKER_H_
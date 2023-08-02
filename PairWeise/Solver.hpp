#ifndef SOLVER_H_
#define SOLVER_H_

#include <string>
#include <utility>
#include <vector>

struct Tuple {
  std::string Option_;
  std::string Value_;
};

struct TupleForConstraints {
  std::string Option_;
  std::string value_;
  bool Match = false;
};

class Solver {
  // class properties.
  std::vector<std::vector<Tuple>> tupleOption;
  std::vector<std::vector<TupleForConstraints>> tupleConstraints;

public:
  // Set- and getters
  std::vector<std::vector<std::string>> optionCopy_;
  std::vector<std::vector<std::string>> constraintsCopy_;
  std::vector<std::vector<TupleForConstraints>> getTupleConstraints() {
    return tupleConstraints;
  }
  // Copy the parameter input into the field.
  void getDataFromOption(std::vector<std::vector<std::string>> param);
  // Copy the parameter input into the field.
  void getDataFromConstraint(std::vector<std::vector<std::string>> param);
  // generating a.models file and eliminate eol.
  void generateModells(std::string const &file3);
  // if necessary, eliminate eol.
  void handleInputFiles(std::string const &file1, std::string const &file2);
  // building tuples of options and values.
  void generateTuple();
  // filtering function returns true if model matches one of the constraints.
  bool ifMatchConstraints(std::vector<Tuple> param);

private:
  // eliminate trailing whitespaces (newlines).
  std::string readAndTrimTrailingSpaces(std::string const &file);
  // turn the given Configuration to actual string.
  std::string thisConfigToString(std::vector<Tuple> tempConfig);
  // main logic permutating every possible configuration.
  void generatePermutations(const std::vector<std::vector<Tuple>> &data,
                            std::vector<Tuple> &currentPermutation,
                            int categoryIndex, std::ofstream &buffer);
  // helper function for ifMatchConstraints.
  void resetConstraints();
};
#endif // SOLVER_H_
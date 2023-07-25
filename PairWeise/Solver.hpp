#ifndef SOLVER_H_
#define SOLVER_H_

#include <string>
#include <utility>
#include <vector>

struct Tuple
{
  std::string Option_;
  std::string Value_;
};

struct TupleForConstraints
{
  std::string Option_;
  std::string value_;
  bool Match = false;
};

struct Pair
{
  Tuple Option1;
  Tuple Option2;
};

// Models with pr. membervariables.
class Solver {
  std::vector<std::vector<Tuple>> tupleOption;
  std::vector<std::vector<TupleForConstraints>> tupleConstraints;
  std::vector<std::vector<std::string>> optionCopy_;
  std::vector<std::vector<std::string>> constraintsCopy_;

public:
  // Adding the various parameters to the options.
  void getDataFromOption(std::vector<std::vector<std::string>> param);
  // Adding the various set of constraints.
  void getDataFromConstraint(std::vector<std::vector<std::string>> param);
  // Main logic for generating modells. Depending on coming UB might
  // have to be adjusted.
  void generateModells();
  void generateTuple();

private:
  // filtering function return true if model match one of constraints.
  bool ifMatchConstraints(std::vector<Tuple> param);
  // eliminate trailing whitespaces (newlines).
  std::string readAndTrimTrailingSpaces(std::string const & file);
};
#endif // SOLVER_H_
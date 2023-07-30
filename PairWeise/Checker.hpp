#ifndef CHECKER_H_
#define CHECKER_H_

#include <string>
#include <utility>
#include <vector>
#include "./Solver.hpp"

class Checker {

public:
    // read data from file.
    void readDataInput(const std::string &options,
                  const std::string &constraints);
    void readDataModel(const std::string &models);
    // this function call all checker methods.
    bool ifModel();
    bool ifOptionAndConstraints();
    int errorCode_;
private:
    Solver s;
    std::vector<std::vector<std::string>> optionFile;
    std::vector<std::vector<std::string>> constraintFile;
    std::vector<std::vector<std::string>> modelFile;
    std::vector<std::vector<TupleForConstraints>> tupleConstraintsCopy;
    std::vector<std::vector<Tuple>> Model;
    // setter of model field.
    void setModel();
    // in jedem Model alle Optionen genau einmal angegeben werden.
    // jedes Model auch alle Constraints erfuellt.
    int ifConditionValid();
    // handle invalide Input Dateien.
    int ifOptionValid();
    // in den Constraint gibt es nur Optionen und Werte aus der .options Datei.
    int ifConstraintValid();
    // helper function;
    bool ifThisTupleOfConstraintValid(TupleForConstraints param);
    bool ifThisCongifurationValid(std::vector<Tuple> param, std::vector<std::string> possibleOption);
};
#endif // CHECKER_H_
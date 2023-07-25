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
    std::vector<std::string> file1_;
    std::vector<std::string> file2_;
    std::vector<std::string> file3_;
    // setter of model field.
    void setModel(std::vector<std::string> param);
    // in jedem Model alle Optionen genau einmal angegeben werden.
    int ifCondition1Valid();
    // jedes Model auch alle Constraints erfuellt.
    int ifCondition2Valid();
    // In den Modellen und in den Constraint 
    // gibt es nur Optionen und Werte aus der .options Datei.
    int ifCondition3Valid();
    // handle invalide Input Dateien.
    int ifOptionValid();
    int ifConstraintValid();
    // helper function;
    bool andTheRest(int i);
    void helperFunctionBuildData();
};
#endif // CHECKER_H_
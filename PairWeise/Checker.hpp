#ifndef CHECKER_H_
#define CHECKER_H_

#include <string>
#include <utility>
#include <vector>
#include "./Solver.hpp"

struct model
{
    std::string prozessor_, ram_, bildschirm_;
};

class Checker {
    option option_;
    std::vector<constraint> constraints_;
    std::vector<model> models_;
public:
    // read data from file.
    void readData(const std::string &options,
                  const std::string &constraints,
                  const std::string &models);
    // this function call all checker methods.
    void Check();
private:
    // setter of option field.
    void setOption(std::vector<std::string> param);
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
    int ifCondition4Valid();
};
#endif // CHECKER_H_
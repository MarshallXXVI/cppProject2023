#ifndef MODELL_H_
#define MODELL_H_

#include <vector>
#include <string>
#include <utility>

class Models {
    std::vector<std::string> prozessor_;
    std::vector<std::string> ram_;
    std::vector<std::string> bildschirm_;
    public:
        void getDataFromParse(std::vector<std::string> param);
        void generateModells();
    private:
        std::string thisModellToString(int i, int j, int k);

};
#endif  // MODELL_H_
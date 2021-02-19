#ifndef MENU_HPP
#define MENU_HPP
#include "List.hpp"
#include "Switch.hpp"


class Menu {
public:
    int menuList();
private:
    void readFile();
    void writeFile();
    void showDataAsFile();
    void aboutStudent();

    List<Switch> _switches;
};


#endif //MENU_HPP

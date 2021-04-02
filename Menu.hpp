#ifndef MENU_HPP
#define MENU_HPP
#include "List.hpp"
#include "Switch.hpp"


class Menu {
public:
    int menuList();
private:
    void readFile();
    void writeFile() const;
    void addEntry();
    void removeEntry();
    void showDataAsFile() const;
    void aboutStudent() const;

    List<Switch> _switches;
};


#endif //MENU_HPP

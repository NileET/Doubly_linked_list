#include "Menu.hpp"
#include <fstream>

int Menu::menuList() {
    while (true) {
        system("cls");
        std::cout << " 1. " << std::endl;
        std::cout << "\n ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:

            case 5:
                return 0;
            default:
                std::cerr << "";
                system("pause");
                system("cls");
        }
    }
}

void Menu::readFile() {
    const char* fileName = "switch_list.db";
    std::ifstream fin(fileName);
    std::cout << " Data file: " << fileName << '.' << std::endl;
    if (!fin.is_open()) {
        std::cerr << " File is not open!" << std::endl;
        return;
    }

    char* line = new char[1024];
    int countLines = 0;
    while (fin.getline(line, 1024, '\n')) {
        ++countLines;
    }
    delete[] line;
    line = nullptr;

    for (size_t i = 0; i < countLines; ++i) {
        std::string modelName; std::getline(fin, modelName, ';');

        std::pair<int, int> baseSpeed; fin >> baseSpeed.first >> baseSpeed.second;
        fin.ignore(1);

        int portCount; fin >> portCount;
        fin.ignore(1);

        double width, length, high; fin >> width >> length >> high;
        fin.ignore(1);

        _switches.push_back(Switch(modelName, baseSpeed, portCount,{width, length, high}));
    }
    std::cout << " File has been read." << std::endl;
    fin.close();
}

void Menu::writeFile() {
    const char* fileName = "switch_list.db";
    std::ofstream fout(fileName);
    std::cout << " Data file: " << fileName << '.' << std::endl;
    if (!fout.is_open()) {
        std::cerr << " File is not open!" << std::endl;
        return;
    }

    for (size_t i = 0; i < _switches.size(); ++i) {

    }
    std::cout << " File has been recorded." << std::endl;
    fout.close();
}

void Menu::showData() {

}

void Menu::aboutStudent() {

}

#include "Menu.hpp"
#include <fstream>

int Menu::menuList() {
    while (true) {
        system("cls");
        std::cout << " 1. Open file\n"
                  << " 2. Save file\n"
                  << " 3. Add entry to the list\n"
                  << " 4. Remove entry from the list\n"
                  << " 5. Display the list\n"
                  << " 6. EXIT\n" << std::endl;
        std::cout << " Select the action you want";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                return 0;
            default:
                std::cerr << "";
                system("pause");
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
    if (countLines == 0) {
        std::cerr << " File is empty!" << std::endl;
        return;
    }

    for (size_t i = 0; i < countLines; ++i) {
        std::string modelName; std::getline(fin, modelName, ';');

        std::pair<int, int> baseSpeed; fin >> baseSpeed.first >> baseSpeed.second;
        fin.ignore(1);

        int portCount; fin >> portCount;
        fin.ignore(1);

        double width, length, high; fin >> width >> length >> high;
        fin.ignore(1);

        _switches.push_back(Switch(modelName, baseSpeed, portCount, {width, length, high}));
    }
    std::cout << " File has been read." << std::endl;
    fin.close();
}

void Menu::writeFile() {
    std::cout << " Enter the file name to write it: ";
    std::string fileName; std::cin >> fileName;
    std::ofstream fout(fileName);
    std::cout << "\n Data file: " << fileName << '.' << std::endl;
    if (!fout.is_open()) {
        std::cerr << " File is not open!" << std::endl;
        return;
    }

    for (auto it = _switches.begin(); it != _switches.end(); ++it) {
        fout << (*it).getModelName()            << ';'
             << (*it).getBaseSpeed().first      << ' '
             << (*it).getBaseSpeed().second     << ';'
             << (*it).getPortCount()            << ';'
             << (*it).getModelSize().__width    << ' '
             << (*it).getModelSize().__length   << ' '
             << (*it).getModelSize().__high     << ';' << std::endl;
    }
    std::cout << " File has been recorded." << std::endl;
    fout.close();
}

void Menu::showDataAsFile() {
    for (auto it = _switches.begin(); it != _switches.end(); ++it) {
        std::cout << (*it).getModelName()       << ';'
             << (*it).getBaseSpeed().first      << ' '
             << (*it).getBaseSpeed().second     << ';'
             << (*it).getPortCount()            << ';'
             << (*it).getModelSize().__width    << ' '
             << (*it).getModelSize().__length   << ' '
             << (*it).getModelSize().__high     << ';' << std::endl;
    }
}

void Menu::aboutStudent() {
    std::cout << " Completed by Daniil Andreevich Zholudev\n"
              << " IEUIS-2-5\n"
              << " Variant 7" << std::endl;
}

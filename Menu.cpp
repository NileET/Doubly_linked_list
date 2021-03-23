#include "Menu.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

int Menu::menuList() {
    while (true) {
        std::system("cls");
        std::cout << " 1. Open file\n"
                  << " 2. Save file\n"
                  << " 3. Add entry to the list\n"
                  << " 4. Remove entry from the list\n"
                  << " 5. Display the list\n"
                  << " 6. EXIT\n" << std::endl;

        std::cout << " Select the action you want: ";
        int choice;
        std::cin >> choice;
        std::system("cls");

        switch (choice) {
            // Open file
            case 1:
                readFile(); break;
            // Save file
            case 2:
                writeFile(); break;
            // Add entry to the list
            case 3:
                addEntry(); break;
            // Remove entry from the list
            case 4:
                removeEntry(); break;
            // Display the list
            case 5:
                showDataAsFile(); break;
            // EXIT
            case 6:
                aboutStudent();
                std::system("pause");
                return 0;
            default:
                std::cerr << "\n\tERROR\n Try again..." << std::endl;
        }
        std::system("pause");
    }
}

void Menu::readFile() {
    const char* fileName = "products.txt";
    std::ifstream fin(fileName);
    std::cout << " Data file: " << fileName << '.' << std::endl;
    if (!fin.is_open()) {
        std::cerr << " File is not open..." << std::endl;
        return;
    }

    char* buf_line = new char[1024];
    while (fin.getline(buf_line, 1024, '\n')) {
        std::istringstream ss(buf_line);
        std::string modelName; std::getline(ss, modelName, ';');

        std::pair<int, int> baseSpeed; ss >> baseSpeed.first >> baseSpeed.second;
        ss.ignore(1);

        int portCount; ss >> portCount;
        ss.ignore(1);

        double width, length, high; ss >> width >> length >> high;
        ss.ignore(1);

        _switches.push_back(Switch(modelName, baseSpeed, portCount, {width, length, high}));
    }
    delete[] buf_line;

    if (_switches.is_empty()) {
        std::cout << "File is empty" << std::endl;
    }

    std::cout << " File has been read." << std::endl;
    fin.close();
}

void Menu::writeFile() {
    if (_switches.is_empty()) {
        std::cerr << "Error of saving data to file" << std::endl
        << "Probably, product.txt is empty or not opened..." << std::endl;
        return;
    }

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
    size_t id = 1;
    for (auto it = _switches.begin(); it != _switches.end(); ++it) {
        std::cout << id << ") "
                  << (*it).getModelName()            << ';'
                  << (*it).getBaseSpeed().first      << ' '
                  << (*it).getBaseSpeed().second     << ';'
                  << (*it).getPortCount()            << ';'
                  << (*it).getModelSize().__width    << ' '
                  << (*it).getModelSize().__length   << ' '
                  << (*it).getModelSize().__high     << ';' << std::endl;
        ++id;
    }
}

void Menu::aboutStudent() {
    std::cout << " Completed by Daniil Andreevich Zholudev\n"
              << " IEUIS-2-5\n"
              << " Variant 7" << std::endl;
}

void Menu::addEntry() {
    int choice;
    while (true) {
        std::cout << " Add an entry to ... of the list\n"
                  << "\t 1. the beginning\n"
                  << "\t 2. the ending\n"
                  << "\t 3. the middle\n"
                  << "\t 4. CANCEL!\n" << std::endl;

        std::cout << " Select the action you want: ";
        std::cin >> choice;

        if (choice > 0 && choice < 5) {
            break;
        } else {
            std::cerr << "\n\tERROR\n Try again..." << std::endl;
        }
    }

    // For cancel
    if (choice == 4) {
        std::cout << "Cancel..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000) );
        return;
    }

    std::system("cls");
    std::cout << " Enter data..." << std::endl;

    try {
        std::cout << "\tModel: ";
        std::string modelName;
        std::getline(std::cin, modelName);

        std::cout << "\tBase baud rate (Mbps): ";
        std::pair<int, int> baseSpeed;
        std::cin >> baseSpeed.first >> baseSpeed.second;

        std::cout << "\tNumber of ports: ";
        int portCount; std::cin >> portCount;

        std::cout << "\tDimensions: " << std::endl;
        double width, length, high;
        std::cout << "\t\twidth - ";  std::cin >> width;
        std::cout << "\t\tlength - "; std::cin >> length;
        std::cout << "\t\thigh - ";   std::cin >> high;

        Switch sw(modelName, baseSpeed, portCount, {width, length, high});

        switch (choice) {
            case 1:
                _switches.push_front(sw);
                break;
            case 2:
                _switches.push_back(sw);
                break;
            case 3:
                std::system("cls");
                std::cout << "/********************" << std::endl;
                showDataAsFile();
                std::cout << "********************/" << std::endl;

                while (true) {
                    std::cout << "\n Enter the line number to which you want to add the entry: ";
                    size_t index;
                    std::cin >> index;
                    --index;
                    if (index >= 0 && index <= _switches.size()) {
                        _switches.insert(sw, index);
                        break;
                    }
                    std::cerr << "\n\tERROR\n Try again..." << std::endl;
                }
                break;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}

void Menu::removeEntry() {
    while (true) {
        int choice;
        std::cout << " Remove an entry from ... of the list\n"
                  << "\t 1. the beginning\n"
                  << "\t 2. the ending\n"
                  << "\t 3. the middle\n"
                  << "\t 4. CANCEL!\n" << std::endl;

        std::cout << " Select the action you want: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                _switches.pop_front();
                break;
            case 2:
                _switches.pop_back();
                break;
            case 3:
                std::system("cls");
                std::cout << "/********************" << std::endl;
                showDataAsFile();
                std::cout << "********************/" << std::endl;

                while (true) {
                    std::cout << "\n Enter the line number for which you want to delete the entry: ";
                    size_t index;
                    std::cin >> index;
                    --index;
                    if (index >= 0 && index <= _switches.size()) {
                        _switches.remove(index);
                        break;
                    }
                    std::cerr << "\n\tERROR\n Try again..." << std::endl;
                }
                break;
            case 4:
                std::cout << "Cancel..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                return;
            default:
                std::cerr << "\n\tERROR\n Try again..." << std::endl;
                std::system("pause");
                std::system("cls");
                continue;
        }
        break;
    }
}

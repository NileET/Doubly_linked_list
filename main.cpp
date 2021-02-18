#include "List.hpp"
#include "Device.hpp"


int main() {
    List<int> lst;
    for (int i = 1; i <= 20; ++i) {
        lst.push_back(i);
    }
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << ' ';
    }
    Device dev;
    std::cout << std::endl << dev;
    return 0;
}

#include <iostream>

int main() {
#ifdef NDEBUG
    std::cout << "Running in Release mode\n";
#else
    std::cout << "Running in Debug mode\n";
#endif
    std::cout << "arch btw\n";
    return 0;
}

#include <iostream>   // library for reading & writing from the console/keyboard

int main(int argc, char* argv[]) {
    
    int total = 1;
    for (int i = 1; i < argc; i++) {
         
        int x = std::stoi(argv[i]);
        total = total * x;
    }

    std::cout << "product of integers: " << total << std::endl;
}
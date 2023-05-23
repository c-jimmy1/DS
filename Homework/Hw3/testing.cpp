#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "Matrix.h"

#define __EPSILON 0.0000000001 //Need this to compare doubles because representation.

int main() {

    Matrix m1(2, 3, 0.0);
    Matrix m2(2, 3, 0.0);

    m1.set(0,0,1.0);
    m1.set(0,1,2.0);
    m1.set(0,2,3.0);
    m1.set(1,0,4.0);
    m1.set(1,1,5.0);
    m1.set(1,2,6.0);

    m2.set(0,0,1.0);
    m2.set(0,1,2.0);
    m2.set(0,2,3.0);
    m2.set(1,0,4.0);
    m2.set(1,1,5.0);
    m2.set(1,2,6.0);
    // m2.set(2,0,7.0);
    // m2.set(2,1,8.0);
    // m2.set(2,2,9.0);


    std::cout << m1 << "\n" << m2 << std::endl;

    Matrix m3(2,3,1.0);
    std::cout << m3 << std::endl;
    std::cout << "Done printing." << std::endl;

    // m2.swap_row(0,1);
    // std::cout << m2 << std::endl;

    // m2.transpose();
    // std::cout << m2 << std::endl;

    m1.subtract(m2);
    std::cout << m1 << std::endl;
    return 0;

}


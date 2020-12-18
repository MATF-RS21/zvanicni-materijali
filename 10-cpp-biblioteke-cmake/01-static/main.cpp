#include <iostream>

#include "fraction.hpp"
#include "list.hpp"

int main()
{
    matf::list fs;
    fs.push_back(matf::fraction(1, 2));
    fs.push_back(matf::fraction(3, 5));
    fs.push_back(matf::fraction(4, 10));

    std::cout << fs << std::endl;

    return 0;
}
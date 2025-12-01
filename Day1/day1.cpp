#include <iostream>
#include <fstream>
#include <string>

int LineParse(std::string element)
{
    int result = std::stoi(element.substr(1, element.length()));
    return element.substr(0, 1) == "L" ? result*-1 : result;
}

int main()
{
    std::cout << LineParse("L52") << std::endl;
    std::cout << LineParse("R52") << std::endl;
    std::cout << LineParse("L522") << std::endl;
    std::cout << LineParse("R522") << std::endl;
    std::cout << LineParse("L2") << std::endl;
    std::cout << LineParse("R2") << std::endl;
}
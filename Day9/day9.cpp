#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std::chrono;



std::vector<std::pair<int, int>> LineParse(std::string line, char delimiter)
{   
    std::vector<std::pair<int, int>> allRangesInt;
    std::stringstream stringToParse(line);
    std::string stringResult;
    
    while(getline(stringToParse, stringResult, delimiter))
    {
        size_t pos = stringResult.find(',');
        assert(pos != std::string::npos); //npos = -1

        int x = std::stoll(stringResult.substr(0, pos));
        int y = std::stoll(stringResult.substr(pos + 1));

        allRangesInt.push_back(std::make_pair(x, y));
    }

    return allRangesInt;
}

int ReadFile(std::string fileName, std::vector<std::pair<int, int>>& outIdsRanges)
{
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            outIdsRanges = LineParse(line, ',');
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}



int main()
{
    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input9.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------


    //PART 2 -------------------------------------------------

}
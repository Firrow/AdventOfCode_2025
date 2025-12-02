#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>

#include <cstdint> //ajout pour version maison sinon int64_t ne passent pas


std::vector<std::pair<std::int64_t, std::int64_t>> LineParse(std::string line, char delimiter)
{   
    std::vector<std::pair<std::int64_t, std::int64_t>> allRangesInt;
    std::vector<std::string> allRanges;
    std::stringstream stringToParse(line);
    std::string stringResult;
    
    while(getline(stringToParse, stringResult, delimiter))
    {
        size_t pos = stringResult.find('-');
        assert(pos != std::string::npos); //npos = -1

        std::int64_t from = std::stoll(stringResult.substr(0, pos));
        std::int64_t to = std::stoll(stringResult.substr(pos + 1));

        allRangesInt.push_back(std::make_pair(from, to));
    }

    return allRangesInt;
}

int ReadFile(std::string fileName, std::vector<std::pair<std::int64_t, std::int64_t>>& outIdsRanges)
{
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            outIdsRanges = LineParse(line, ',');
        }
        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}


int main()
{
    std::vector<std::pair<std::int64_t, std::int64_t>> allIdsRanges;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input2.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    ReadFile(filePath, allIdsRanges);
    std::cout << "fin" << "\n";
    //PART 2 -------------------------------------------------
}
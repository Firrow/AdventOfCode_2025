#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std::chrono;



int ReadFile(std::string fileName, std::vector<std::string>& outLines)
{
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            outLines.push_back(line);
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}

void GetNumbersAndOperators(std::vector<std::string>& _fileContent, std::vector<std::string>& outNumbers, std::vector<std::string>& outOperators)
{
    std::string element = "";

    for (size_t i = 0; i < _fileContent.size(); i++)
    {
        if (_fileContent[i] == " ")
        {
            continue;
        }
        else
        {
            if (_fileContent[i] == "*" || _fileContent[i] == "+")
            {
                outOperators.push_back(_fileContent[i]);
            }
            else
            {
                outNumbers.push_back(_fileContent[i]);
            }
        }
    }
}

/*std::int64_t Calculate(std::vector<std::string>& outNumbers, std::vector<std::string>& outOperators)
{
    std::int64_t count = 0;
    int calculQuantity = outOperators.size();

    for (size_t i = 0; i < outNumbers.size(); i++)
    {
        
    }
}*/



int main()
{
    std::vector<std::string> fileContent;
    std::vector<std::string> numbers;
    std::vector<std::string> operators;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input6.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    ReadFile(filePath, fileContent);
    GetNumbersAndOperators(fileContent, numbers, operators);

    //PART 2 -------------------------------------------------
}
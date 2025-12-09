#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std::chrono;


// PART1 ---------------------------------------------------------------------------------------------------------------------------
/*
void GetNumbersAndOperators(std::string& _line, std::vector<std::int64_t>& outNumbers, std::vector<char>& outOperators);

int ReadFile(std::string _fileName, std::vector<std::int64_t>& outNumbers, std::vector<char>& outOperators)
{
    std::ifstream file(_fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            GetNumbersAndOperators(line, outNumbers, outOperators);
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}

void GetNumbersAndOperators(std::string& _line, std::vector<std::int64_t>& outNumbers, std::vector<char>& outOperators)
{
    size_t out;
    std::int64_t element;

    // get all numbers
    while (!_line.empty())
    {
        try
        {
            element = std::stoll(_line, &out);
            _line = _line.substr(out);
            outNumbers.push_back(element);
        }
        catch(const std::exception& e)
        { break; }
    }

    // get all operators
    for(char c : _line) {
        switch(c) {
            case '*':
            case '+':
                outOperators.push_back(c);
                break;
            default:
                break;
        }
    }
}

std::int64_t Calculate(std::vector<std::int64_t>& _numbers, std::vector<char>& _operators, int QttNumberInCalcul)
{
    std::int64_t result = 0;
    int lengthLine = _operators.size();

    // for each columns
    for (size_t i = 0; i < lengthLine; i++) // ligne
    {
        char currentOperator = _operators[i];
        std::int64_t blocCalcul = _numbers[i]; // we initialize the calcul with the first element

        // for each element of column
        for (size_t j = 1; j < QttNumberInCalcul - 1; j ++)
        {
            int index = j * lengthLine + i;

            // calcul the bloc's result
            switch (currentOperator)
            {
                case '*':
                    blocCalcul *= _numbers[index];
                    break;
                case '+':
                    blocCalcul += _numbers[index];
                    break;
                default:
                    break;
            }
        }

        // calcul the final result
        result += blocCalcul;
    }
    
    return result;
}
*/

// PART2 ---------------------------------------------------------------------------------------------------------------------------

class Map
{
    private : 
        std::string map;
        int sizeX;

    public :
        Map(std::string _map, int _sizeX)
        {
            map = _map,
            sizeX = _sizeX;
        }

        char GetValueInMap(int _x, int _y)
        {
            // if we are out of x bounds of the map
            if (_x < 0 || _x >= sizeX)
            {
                return '\0';
            }

            int indexInMap = _y * this->sizeX + _x;
            return this->map.at(indexInMap);
        }



        const std::string& GetMap() { return map; }
        int GetSizeX() { return sizeX; }
};

int ReadFile(std::string _fileName, std::string& outDatas, int& outSizeX)
{
    std::ifstream file(_fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            outDatas += line;
            outSizeX = line.length();
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}

void CalculateColumn(char& currentOperator, std::int64_t& previousResult, std::string& number)
{
    switch (currentOperator)
    {
        case '*':
            previousResult *= std::stoll(number);
            break;
        case '+':
            previousResult += std::stoll(number);
            break;
        default:
            break;
    }
}

std::int64_t Calculate(Map& _map, int _QttNumberInCalcul)
{
    std::int64_t result = 0;
    std::string number = "";
    std::int64_t blocCalcul = 0;
    char currentOperator = '\0';


    // for each column
    for (size_t x = 0; x < _map.GetSizeX(); x++)
    {
        // for each char of column
        for (size_t y = 0; y < _QttNumberInCalcul; y++)
        {
            char element = _map.GetValueInMap(x, y);

            // if we are on the last line
            if (y == _QttNumberInCalcul - 1)
            {
                // if we are at the begining of the current bloc
                if (element == '*' || element == '+')
                {
                    currentOperator = element;
                    blocCalcul = (currentOperator == '*') ? 1 : 0;
                }
                // if we are at the end of the current bloc (current calcul) or at the end of the map
                if ((_map.GetValueInMap(x + 2, y) == '*' || _map.GetValueInMap(x + 2, y) == '+') || x == _map.GetSizeX() - 1)
                {
                    CalculateColumn(currentOperator, blocCalcul, number);
                    result += blocCalcul;

                    // reset bloc elements
                    blocCalcul = 0;
                    currentOperator = '\0';
                    break;
                }

                // at the end of the column, we have our number so we update the bloc calcul
                CalculateColumn(currentOperator, blocCalcul, number);
                number = "";
            }
            else
            {
                number += element;
            }
        }
    }

    return result;
}



int main()
{
    std::int64_t finalResult;
    const int QTT_LINE_IN_FILE = 5;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input6.txt               (QTT_LINE_IN_FILE = 5;)
    //   ../Inputs/inputTest.txt            (QTT_LINE_IN_FILE = 4;)

    //PART 1 -------------------------------------------------
    /*
    std::vector<std::int64_t> numbers;
    std::vector<char> operators;

    auto start = high_resolution_clock::now();
    ReadFile(filePath, numbers, operators);
    finalResult = Calculate(numbers, operators, QTT_LINE_IN_FILE);

    std::cout << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
    */

    //PART 2 -------------------------------------------------
    std::string datas = "";
    int sizeX = 0;

    auto start = high_resolution_clock::now();
    ReadFile(filePath, datas, sizeX);
    Map* map = new Map(datas, sizeX);
    finalResult = Calculate(*map, QTT_LINE_IN_FILE);

    std::cout << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std::chrono;
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

    while (!_line.empty())
    {
        try
        {
            element = std::stoll(_line, &out); // On recupere ??
            _line = _line.substr(out); // chaine de out jusqu'a la fin
            //std::cout << "element : " << element << "\n";
            outNumbers.push_back(element);
        }
        catch(const std::exception& e)
        { break; }
    }

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
    int lenghLine = _operators.size();

    for (size_t i = 0; i < lenghLine; i++) // ligne
    {
        char currentOperator = _operators[i];
        std::int64_t resultEachCalcul = _numbers[i];

        for (size_t j = 1; j < QttNumberInCalcul - 1; j ++) // colonne
        {
            int index = j * lenghLine + i;
            switch (currentOperator)
            {
                case '*':
                    resultEachCalcul *= _numbers[index];
                    break;
                case '+':
                    resultEachCalcul += _numbers[index];
                    break;
                default:
                    break;
            }
        }

        result += resultEachCalcul;
    }
    
    return result;
}



int main()
{
    std::int64_t finalResult;
    std::vector<std::int64_t> numbers;
    std::vector<char> operators;
    const int QTT_LINE_IN_FILE = 5;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input6.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, numbers, operators);
    finalResult = Calculate(numbers, operators, QTT_LINE_IN_FILE);

    std::cout << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;

    //PART 2 -------------------------------------------------
}
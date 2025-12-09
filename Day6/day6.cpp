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

    for (size_t i = 0; i < lengthLine; i++) // ligne
    {
        char currentOperator = _operators[i];
        std::int64_t resultEachCalcul = _numbers[i];

        for (size_t j = 1; j < QttNumberInCalcul - 1; j ++) // colonne
        {
            int index = j * lengthLine + i;
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
            outSizeX = line.length(); // avec retour à la ligne a prendre en compte dans la longueur de la ligne (+1 par rapport à ce qu'on voit)
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}

std::int64_t Calculate(Map& _map, int _QttNumberInCalcul)
{
    std::int64_t result = 0;
    std::string number = ""; //anciennement CalculCol
    std::int64_t resultatColumn;
    char currentOperator = '\0';
    int lenBlock = 1;


    for (size_t x = 0; x < _map.GetSizeX(); x++)
    {
        // Get Calcul to do
        for (size_t y = 0; y < _QttNumberInCalcul; y++)
        {
            char element = _map.GetValueInMap(x, y);
            std::cout << " x : " << x << "\n";
            std::cout << " y : " << y << "\n";
            std::cout << "element map : " << element << "\n";

            if (y == _QttNumberInCalcul - 1) // si on est sur la dernière ligne
            {
                // si fin du bloc
                if ((_map.GetValueInMap(x + 2, y) == '*' || _map.GetValueInMap(x + 2, y) == '+') || x == _map.GetSizeX() - 1) // et que l'element à droite sur la ligne des operator est un operateur => bloc fini
                {
                    // CALCUL COLONNE --------------------------------------------------------------
                    switch (currentOperator) // fin ligne
                    {
                        case '*':
                            resultatColumn *= std::stoi(number);
                            break;
                        case '+':
                            resultatColumn += std::stoi(number);
                            break;
                        default:
                            break;
                    }

                    std::cout << "resultatColumn temps : " << resultatColumn << "\n";
                    // -------------------------------------------------------------------------------

                    result += resultatColumn;
                    std::cout << "result temp : " << result << "\n";
                    number = "";
                    resultatColumn = 0;
                    currentOperator = '\0';
                    break;
                }
                if (element == '*' || element == '+') // si début du bloc
                {
                    currentOperator = element;
                    resultatColumn = (currentOperator == '*') ? 1 : 0;
                    //calculCol += currentOperator;
                    //std::cout << "calculCol : " << calculCol << "\n";
                }
                //else if (element == ' ')
                {
                    //calculCol += currentOperator;
                    // CALCUL COLONNE --------------------------------------------------------------
                    switch (currentOperator) // fin ligne
                    {
                        case '*':
                            resultatColumn *= std::stoll(number);
                            break;
                        case '+':
                            resultatColumn += std::stoll(number);
                            break;
                        default:
                            break;
                    }

                    std::cout << "resultatColumn temps : " << resultatColumn << "\n";
                    // -------------------------------------------------------------------------------
                }

                number = "";
            }
            else
            {
                number += element;
                std::cout << "number : " << number << "\n";
            }

            std::cout << " ------------------------- " << "\n";
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
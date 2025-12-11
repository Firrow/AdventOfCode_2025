#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std::chrono;



class Map
{
    private : 
        std::string map;
        int sizeX;
        int sizeY;

    public :
        Map(std::string _map, int _sizeX, int _sizeY)
        {
            map = _map,
            sizeX = _sizeX;
            sizeY = _sizeY;
        }

        char GetValueInMap(int _x, int _y)
        {
            // if we are out of x bounds of the map
            if (_x < 0 || _x >= sizeX || _y < 0 || _y >= sizeY)
            {
                return '\0';
            }

            std::int64_t indexInMap = _y * this->sizeX + _x;
            return this->map.at(indexInMap);
        }



        const std::string& GetMap() { return map; }
        int GetSizeX() { return sizeX; }
        int GetSizeY() { return sizeY; }
};

std::int64_t ReadFile(std::string _fileName, std::string& outDatas, int& outSizeX, int& outSizeY)
{
    std::ifstream file(_fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            outSizeY++;
            outSizeX = outSizeX == 0 ? line.length() : outSizeX;
            outDatas += line;
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}


std::int64_t CountSplitTachyon(Map& _map, std::vector<std::pair<int, int>>& activeSpliters)
{
    int currentX = 0;
    int currentY = 0;

    // for each element of the map
    for (size_t index = 0; index < _map.GetMap().size(); index++)
    {
        currentX = index % _map.GetSizeX();
        currentY = index / _map.GetSizeX();
        char currentindex = _map.GetValueInMap(currentX, currentY);
        
        // if current element is a spliter
        if (_map.GetValueInMap(currentX, currentY) == '^')
        {
            // if this is the first spliter
            if (_map.GetValueInMap(currentX, currentY - 2) == 'S')
            {
                activeSpliters.push_back(std::make_pair(currentX, currentY));
            }
            else
            {
                int limitResearch = 0;

                // search the previous spliter above the current spliter (if it doesn't exist -> y = 0)
                for (size_t y = currentY - 1; y > 0; y--)
                {
                    if (_map.GetValueInMap(currentX, y) == '^')
                    {
                        limitResearch = y;
                        break;
                    }
                }
                
                // for each element in column before and after the current spliter
                for (size_t yInLimit = currentY - 1; yInLimit > limitResearch; yInLimit--)
                {
                    // check if there is another active spliter
                    if (_map.GetValueInMap(currentX - 1, yInLimit) == '^' || _map.GetValueInMap(currentX + 1, yInLimit) == '^')
                    {
                        // add the current spliter to the list of active spliter 
                        activeSpliters.push_back(std::make_pair(currentX, currentY));
                        break;
                    }
                }
                
            }
        }
        
    }
    
    return activeSpliters.size();
}

std::int64_t CalculateElement(Map& _map, std::vector<std::int64_t>& previousRow, int elementX, int elementY, char posRelativeToSpliter);

std::int64_t CountTimeline(Map& _map, std::vector<std::pair<int, int>>& activeSpliters)
{
    int currentX = 0;
    int currentY = 0;
    std::int64_t resultatLine = 0;
    std::vector<std::int64_t> previousRow = {};
    for (size_t i = 0; i < _map.GetSizeX(); i++)
    {
        previousRow.push_back(0);
    }
    std::vector<std::int64_t> currentLine = {};

    for (size_t index = 0; index < _map.GetMap().size(); index++)
    {
        currentX = index % _map.GetSizeX();
        currentY = index / _map.GetSizeX();
        std::int64_t leftElement = 0;
        std::int64_t rightElement = 0;
        std::int64_t element = 0;
        char currentindex = _map.GetValueInMap(currentX, currentY);

        // update line
        if (currentX == 0 && currentY > 0)
        {
            for (size_t i = 0; i < currentLine.size(); i++)
            {
                std::cout << currentLine[i] << " ";
            }
            std::cout << "\n";
            
            previousRow = currentLine;
            currentLine.clear();
        }

        if (_map.GetValueInMap(currentX - 1, currentY) == '^') //si l'element a gauche est un spliter (actif ou non)
        {
            element = CalculateElement(_map, previousRow, currentX, currentY, 'G');
        }
        else if (_map.GetValueInMap(currentX + 1, currentY) == '^') //si l'element a droite est un spliter (actif ou non)
        {
            element = CalculateElement(_map, previousRow, currentX, currentY, 'D');
            
        } 
        else if (_map.GetValueInMap(currentX, currentY) == '^')
        {
            element = 0;
        }
        else if (_map.GetValueInMap(currentX, currentY - 1 ) == 'S')
        {
            element = 1;
        } 
        else {
            element = previousRow[currentX];
        }

        currentLine.push_back(element);
    }

    // on calcul le resultat de la derniere ligne
    for (size_t i = 0; i < currentLine.size(); i++)
    {
        resultatLine += currentLine[i];
    }
    
    return resultatLine; // on return le resultat de la dernière ligne
}

std::int64_t CalculateElement(Map& _map, std::vector<std::int64_t>& previousRow, int elementX, int elementY, char posRelativeToSpliter)
{
    std::int64_t calcul = 0;

    switch (posRelativeToSpliter)
    {
        case 'G':
        {
            if (_map.GetValueInMap(elementX + 1, elementY) == '^')
            {
                // prendre les 3 elements dans previousRow
                calcul = previousRow[elementX - 1] + previousRow[elementX] + previousRow[elementX + 1];
            }
            else
            {
                // prendre l'element en haut et a droite dans previousRow
                calcul = previousRow[elementX] + previousRow[elementX - 1];
            }
            break;
        }
        case 'D':
        {
            // impossible car ne peux pas avoir un spliter à gauche si on en a deje un a droite
            if (_map.GetValueInMap(elementX - 1, elementY) == '^')
            {
                // prendre les 3 elements dans previousRow
                calcul = previousRow[elementX - 1] + previousRow[elementX] + previousRow[elementX + 1];
            }
            else
            {
                // prendre l'element en haut et a gauche dans previousRow
                calcul = previousRow[elementX] + previousRow[elementX + 1];
            }
            break;
        }
        default:
            break;
    }

    return calcul;
}


int main()
{
    std::string datas;
    int sizeX = 0;
    int sizeY = 0;
    std::vector<std::pair<int, int>> activeSpliters;
    std::int64_t finalResultPart1 = 0;
    std::int64_t finalResultPart2 = 0;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input7.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    
    auto start = high_resolution_clock::now();
    ReadFile(filePath, datas, sizeX, sizeY);
    Map* map = new Map(datas, sizeX, sizeY);

    /*finalResultPart1 = CountSplitTachyon(*map, activeSpliters);

    std::cout << "finalResult - Part1 : " << finalResultPart1 << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;*/
    
    
    //PART 2 -------------------------------------------------
    finalResultPart2 = CountTimeline(*map, activeSpliters);

    std::cout << "finalResult : " << finalResultPart2 << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
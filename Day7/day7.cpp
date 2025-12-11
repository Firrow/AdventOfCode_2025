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

// PART1 ----------------------------------------------------------------------------------------------------------------------------------------
std::int64_t CountSplitTachyon(Map& _map, std::vector<std::pair<int, int>>& activesplitters)
{
    int currentX = 0;
    int currentY = 0;

    // for each element of the map
    for (size_t index = 0; index < _map.GetMap().size(); index++)
    {
        currentX = index % _map.GetSizeX();
        currentY = index / _map.GetSizeX();
        char currentindex = _map.GetValueInMap(currentX, currentY);
        
        // if current element is a splitter
        if (_map.GetValueInMap(currentX, currentY) == '^')
        {
            // if this is the first splitter
            if (_map.GetValueInMap(currentX, currentY - 2) == 'S')
            {
                activesplitters.push_back(std::make_pair(currentX, currentY));
            }
            else
            {
                int limitResearch = 0;

                // search the previous splitter above the current splitter (if it doesn't exist -> y = 0)
                for (size_t y = currentY - 1; y > 0; y--)
                {
                    if (_map.GetValueInMap(currentX, y) == '^')
                    {
                        limitResearch = y;
                        break;
                    }
                }
                
                // for each element in column before and after the current splitter
                for (size_t yInLimit = currentY - 1; yInLimit > limitResearch; yInLimit--)
                {
                    // check if there is another active splitter
                    if (_map.GetValueInMap(currentX - 1, yInLimit) == '^' || _map.GetValueInMap(currentX + 1, yInLimit) == '^')
                    {
                        // add the current splitter to the list of active splitter 
                        activesplitters.push_back(std::make_pair(currentX, currentY));
                        break;
                    }
                }
            }
        }
    }
    
    return activesplitters.size();
}

// PART2 ----------------------------------------------------------------------------------------------------------------------------------------
std::int64_t CalculateElement(Map& _map, std::vector<std::int64_t>& previousRow, int elementX, int elementY, char posRelativeTosplitter);

std::int64_t CountTimeline(Map& _map, std::vector<std::pair<int, int>>& activesplitters)
{
    int currentX = 0;
    int currentY = 0;
    std::int64_t resultatLine = 0;
    std::vector<std::int64_t> previousRow;
    for (size_t i = 0; i < _map.GetSizeX(); i++)
    {
        previousRow.push_back(0);
    }
    std::vector<std::int64_t> currentRow = {};

    for (size_t index = 0; index < _map.GetMap().size(); index++)
    {
        currentX = index % _map.GetSizeX();
        currentY = index / _map.GetSizeX();
        char currentindex = _map.GetValueInMap(currentX, currentY);
        std::int64_t element = 0;

        // update rows
        if (currentX == 0 && currentY > 0)
        {
            previousRow = currentRow;
            currentRow.clear();
        }

        if (_map.GetValueInMap(currentX, currentY - 1 ) == 'S') // if current element is the ray source
        {
            element = 1;
        } 
        else if (_map.GetValueInMap(currentX, currentY) == '^') // if current element is a splitter
        {
            element = 0;
        }
        else if (_map.GetValueInMap(currentX - 1, currentY) == '^') // if current element has a splitter on its left
        {
            element = CalculateElement(_map, previousRow, currentX, currentY, 'G');
        }
        else if (_map.GetValueInMap(currentX + 1, currentY) == '^') // if current element has a splitter on its right
        {
            element = CalculateElement(_map, previousRow, currentX, currentY, 'D');
        } 
        else 
        {
            element = previousRow[currentX];
        }

        // add calculate element on the current row
        currentRow.push_back(element);
    }

    // add up all the items in the last row
    for (size_t i = 0; i < currentRow.size(); i++)
    {
        resultatLine += currentRow[i];
    }
    
    return resultatLine;
}

std::int64_t CalculateElement(Map& _map, std::vector<std::int64_t>& previousRow, int elementX, int elementY, char posRelativeTosplitter)
{
    std::int64_t calcul = 0;

    switch (posRelativeTosplitter)
    {
        case 'G':
        {
            if (_map.GetValueInMap(elementX + 1, elementY) == '^') // if current element is between 2 splitters, add the 3 elements above it
            {
                calcul = previousRow[elementX - 1] + previousRow[elementX] + previousRow[elementX + 1];
            }
            else // add the element at the top left and the one directly above it
            {
                calcul = previousRow[elementX] + previousRow[elementX - 1];
            }
            break;
        }
        case 'D':
        {
            // If there is a splitter on the right, we do not check if there is one on the left because if there is, 
            //      we have already processed it (see else if line 159 and 195).

            // add the element at the top right and the one directly above it 
            calcul = previousRow[elementX] + previousRow[elementX + 1];
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
    std::vector<std::pair<int, int>> activesplitters;
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

    /*finalResultPart1 = CountSplitTachyon(*map, activesplitters);

    std::cout << "finalResult - Part1 : " << finalResultPart1 << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;*/
    
    
    //PART 2 -------------------------------------------------
    finalResultPart2 = CountTimeline(*map, activesplitters);

    std::cout << "finalResult : " << finalResultPart2 << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
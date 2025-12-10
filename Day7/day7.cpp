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

            int indexInMap = _y * this->sizeX + _x;
            return this->map.at(indexInMap);
        }



        const std::string& GetMap() { return map; }
        int GetSizeX() { return sizeX; }
        int GetSizeY() { return sizeY; }
};

int ReadFile(std::string _fileName, std::string& outDatas, int& outSizeX, int& outSizeY)
{
    std::ifstream file(_fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            outSizeY++;
            outSizeX = outSizeX == 0 ? line.length() : outSizeX; //-1 to avoid line break
            outDatas += line;
            /*for (size_t i = 0; i < line.length(); i++)
            {
                outDatas.push_back(i);
            }*/
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}


int CountSplitTachyon(Map& _map)
{
    // TODO : compter tous les spliter sauf quand ils sont sous un autre spliter qui touche le faisceau --> ne toucheront jamais de tachyon !
    
    int currentX = 0;
    int currentY = 0;
    std::vector<std::pair<int, int>> activeSpliters;

    for (size_t index = 0; index < _map.GetMap().size(); index++)
    {
        currentX = index % _map.GetSizeX();
        currentY = index / _map.GetSizeX();
        char currentindex = _map.GetValueInMap(currentX, currentY);
        
        std::cout << " index : " << index << "\n";
        std::cout << " x : " << currentX << " - y : " << currentY << "\n";

        if (_map.GetValueInMap(currentX, currentY) == '^') // si spliter
        {
            std::cout << " SPLITER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << "\n";
            if (_map.GetValueInMap(currentX, currentY - 2) == 'S') // premier spliter
            {
                activeSpliters.push_back(std::make_pair(currentX, currentY));
                std::cout << " c'est le 1er spliter " << "\n";
            }
            else
            {
                int limitResearch = 0;

                for (size_t y = currentY - 1; y > 0; y--)
                {
                    if (_map.GetValueInMap(currentX, y) == '^')
                    {
                        limitResearch = y;
                        break;
                    }
                }
                std::cout << " limitResearch : " << limitResearch << "\n";
                
                for (size_t yInLimit = currentY - 1; yInLimit > limitResearch; yInLimit--)
                {
                    if (_map.GetValueInMap(currentX - 1, yInLimit) == '^' || _map.GetValueInMap(currentX + 1, yInLimit) == '^') // s'il y a un spliter entre le spliter actuel et le précédent
                    {
                        std::cout << " J'AI UN SPLITER ACTIF DANS MA LIMITE a y : " << yInLimit << "\n";
                        activeSpliters.push_back(std::make_pair(currentX, currentY));
                        break;
                    }
                }
                
            }
            std::cout << "-----------------" << "\n";
        }
        
    }
    
    return activeSpliters.size();
}



int main()
{
    std::string datas;
    int sizeX = 0;
    int sizeY = 0;
    std::vector<std::pair<int, int>> activeSpliter;
    int finalResult = 0;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input7.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, datas, sizeX, sizeY);
    Map* map = new Map(datas, sizeX, sizeY);
    finalResult = CountSplitTachyon(*map);

    std::cout << "finalResult : " << finalResult << "\n"; // TOO HIGH !
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
    
    //PART 2 -------------------------------------------------
}
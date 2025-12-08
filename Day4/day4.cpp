#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
using namespace std::chrono;



class Map
{
    private : 
        std::vector<int> map;
        int sizeX;
        int sizeY;

    public :
        Map(std::vector<int> _map, int _sizeX, int _sizeY)
        {
            map = _map,
            sizeX = _sizeX,
            sizeY = _sizeY;
        }

        int GetValueInMap(int _x, int _y)
        {
            // if we are out of bounds of the map
            if (_x < 0 || _x >= sizeX || _y < 0 || _y >= sizeY)
            {
                return 0;
            }
            
            int indexInMap = _y * this->sizeX + _x;
            return this->map.at(indexInMap);
        }

        void ChangeValueInMap(int indexInMap, int newValue)
        {
            this->map.at(indexInMap) = newValue;
        }

        const std::vector<int>& GetMap() { return map; }
        int GetSizeX() { return sizeX; }
        int GetSizeY() { return sizeY; }
};

int ReadFile(std::string _fileName, std::vector<int>& _map, int& _sizeX, int& _sizeY)
{
    std::ifstream file(_fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {

            _sizeY++;
            _sizeX = _sizeX == 0 ? line.length() : _sizeX;

            for (size_t i = 0; i < line.length(); i++)
            {
                if (line[i] == '.')
                {
                    _map.push_back(0);
                }
                else
                {
                    _map.push_back(1);
                }
            }
        }
        file.close();
    } else {
        std::cout << "Impossible to read file" << std::endl;
    }

    return 0;
}

//Part1
/*
int CountAccessibleRolls(Map& _map, int limit)
{
    int accessibleRollsQtt = 0;

    // Pour chaque éléments de la map
    for (size_t i = 0; i < _map.GetMap().size(); i++)
    {
        int currentX = i % _map.GetSizeX();
        int currentY = i / _map.GetSizeY();

        if (_map.GetValueInMap(currentX, currentY) == 0)
        {
            continue;
        }

        int rollNeighborsQtt = 0;

        //On regarde les 8 voisins
        rollNeighborsQtt += _map.GetValueInMap(currentX - 1, currentY - 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX, currentY - 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX + 1, currentY - 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX - 1, currentY);
        rollNeighborsQtt += _map.GetValueInMap(currentX + 1, currentY);
        rollNeighborsQtt += _map.GetValueInMap(currentX - 1, currentY + 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX, currentY + 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX + 1, currentY + 1);

        if (rollNeighborsQtt < limit)
        {
            accessibleRollsQtt++;
        }
    }    
    
    return accessibleRollsQtt;
}
*/

int CountAccessibleRolls(Map& _map, int limit)
{
    int accessibleRollsQtt = 0;
    int currentX = 0;
    int currentY = 0;

    for (size_t i = 0; i < _map.GetMap().size(); i++)
    {
        currentX = i % _map.GetSizeX();
        currentY = i / _map.GetSizeY();

        if (_map.GetValueInMap(currentX, currentY) == 0)
        {
            continue;
        }

        int rollNeighborsQtt = 0;

        // We check all neighbors of the current element
        rollNeighborsQtt += _map.GetValueInMap(currentX - 1, currentY - 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX, currentY - 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX + 1, currentY - 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX - 1, currentY);
        rollNeighborsQtt += _map.GetValueInMap(currentX + 1, currentY);
        rollNeighborsQtt += _map.GetValueInMap(currentX - 1, currentY + 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX, currentY + 1);
        rollNeighborsQtt += _map.GetValueInMap(currentX + 1, currentY + 1);

        if (rollNeighborsQtt < limit)
        {
            accessibleRollsQtt++;
            // we update the map : remove all accessible rolls
            _map.ChangeValueInMap(i, 0);
        }
    }
    
    return accessibleRollsQtt;
}



int main()
{
    //   ../Inputs/input4.txt
    //   ../Inputs/inputTest.txt

    int sizeX = 0;
    int sizeY = 0;
    std::vector<int> elementOfMap;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //PART 1 -------------------------------------------------
    /*
    int limit = 4;
    auto start = high_resolution_clock::now();
    ReadFile(filePath, elementOfMap, sizeX, sizeY);
    Map* map = new Map(elementOfMap, sizeX, sizeY);

    std::cout << CountAccessibleRolls(*map, limit) << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
    */

    //PART 2 -------------------------------------------------
    int limit = 4;

    auto start = high_resolution_clock::now();
    ReadFile(filePath, elementOfMap, sizeX, sizeY);
    Map* map = new Map(elementOfMap, sizeX, sizeY);
    int accessibleRollQttInMap = 0;
    int finalResult = 0;

    do
    {
        accessibleRollQttInMap = CountAccessibleRolls(*map, limit);
        finalResult += accessibleRollQttInMap;
    } while (accessibleRollQttInMap > 0);
    
    std::cout << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
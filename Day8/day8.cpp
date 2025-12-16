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



void LineParse(std::string _line, char _delimiter, std::vector<std::tuple<int, int, int>>& outData)
{     
    int arrCoor[3] = {};
    int i = 0;
    std::stringstream ss(_line);
	
    std::string temp;

    while (getline(ss, temp, _delimiter))
    {
        arrCoor[i] = std::stoi(temp);
        i++;
    }

    outData.push_back(std::make_tuple(arrCoor[0], arrCoor[1], arrCoor[2]));
}

int ReadFile(std::string fileName, std::vector<std::tuple<int, int, int>>& outPoints)
{
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            LineParse(line, ',', outPoints);
        }
        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}

void GetDistancePoints(std::vector<std::tuple<int, int, int>>& _allPoints, std::vector<std::tuple<float, int, int>>& outAllPointsDistance)
{
    for (size_t i = 0; i < _allPoints.size(); i++) // point1
    {
        for (size_t j = i+1; j < _allPoints.size(); j++) //point2
        {
            std::int64_t distance = std::sqrt(std::pow(std::get<0>(_allPoints[i]) - std::get<0>(_allPoints[j]), 2) +
                                              std::pow(std::get<1>(_allPoints[i]) - std::get<1>(_allPoints[j]), 2) +
                                              std::pow(std::get<2>(_allPoints[i]) - std::get<2>(_allPoints[j]), 2));

            outAllPointsDistance.push_back(std::make_tuple(distance, i, j));
        }
    }
    
    
}



int main()
{
    std::vector<std::tuple<int, int, int>> allPoints;
    std::vector<std::tuple<float, int, int>> allPointsDistance;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input8.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, allPoints);

    /*for (const auto& t : allPoints) {
        std::cout << std::get<0>(t) << " - "
                  << std::get<1>(t) << " - "
                  << std::get<2>(t) << '\n';
    }*/

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;

    //PART 2 -------------------------------------------------
}
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



std::pair<std::int64_t, std::int64_t> LineParse(std::string line)
{   
    std::pair<int, int> allPoints;
    int pos = line.find(",");

    int x = std::stoll(line.substr(0, pos));
    int y = std::stoll(line.substr(pos + 1));

    return std::make_pair(x, y);
}

int ReadFile(std::string fileName, std::vector<std::pair<std::int64_t, std::int64_t>>& allPoints)
{
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            allPoints.push_back(LineParse(line));
        }
        file.close();
    } else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}

std::int64_t CalculAreaLargestRectangle(std::vector<std::pair<std::int64_t, std::int64_t>>& allRedTiles)
{
    std::int64_t result = 0;

    for (size_t i = 0; i < allRedTiles.size(); i++) // point1
    {
        for (size_t j = 0; j < allRedTiles.size(); j++) // point2
        {
            //std::cout << "Xa = " << allRedTiles[i].first << " - Xb = " << allRedTiles[j].first << "\n";
            //std::cout << "Ya = " << allRedTiles[i].second << " - Yb = " << allRedTiles[j].second << "\n";
            //std::cout << " calcul : " << std::abs(allRedTiles[i].first - allRedTiles[j].first) << " + 1 * " << std::abs(allRedTiles[i].second - allRedTiles[j].second) << " + 1 \n";
            std::int64_t resultTemp = (std::abs(allRedTiles[i].first - allRedTiles[j].first) + 1) *
                                      (std::abs(allRedTiles[i].second - allRedTiles[j].second) + 1);
            
            //std::cout << " resultat =  " << resultTemp <<  "\n";

            if (resultTemp >= result)
            {
                result = resultTemp;
            }

            //std::cout << " ----------------------------------------- \n";
        }
    }

    return result;
}



int main()
{
    std::vector<std::pair<std::int64_t, std::int64_t>> allRedTiles;
    std::int64_t finalResult = 0;

    std::string filePath;
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input9.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    auto start = high_resolution_clock::now();

    ReadFile(filePath, allRedTiles);

    finalResult = CalculAreaLargestRectangle(allRedTiles);
    std::cout << finalResult << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;

    //PART 2 -------------------------------------------------

}
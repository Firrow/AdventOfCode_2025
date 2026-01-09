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

class Rectangle
{
    private:
        struct Point
        {
            std::int64_t x;
            std::int64_t y;
        };

        Point p1;
        Point p2;

    public:
        Rectangle(std::int64_t _xMin, std::int64_t _xMax, std::int64_t _yMin, std::int64_t _yMax)
        {
            // diagonal sens from up to down and left to right
            // p1 diagonal rectangle
            p1.x = _xMin;
            p1.y = _yMin;

            // p2 diagonal rectangle
            p2.x = _xMax;
            p2.y = _yMax;
        }

        std::pair<std::int64_t, std::int64_t> GetP1()
        {
            return std::make_pair(p1.x, p1.y);
        }

        std::pair<std::int64_t, std::int64_t> GetP2()
        {
            return std::make_pair(p2.x, p2.y);
        }
};



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

// PART 1 ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

// PART 2 ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void GetAllRectangles(std::vector<std::pair<std::int64_t, std::int64_t>>& allRedTiles, std::vector<Rectangle>& out_allRectangles)
{
    for (size_t i = 0; i < allRedTiles.size(); i++) // point1
    {
        //std::cout << "current point :" << allRedTiles[i].first << ", " << allRedTiles[i].second << " --------------------------------------------------------\n";

        for (size_t j = 0; j < allRedTiles.size(); j++) // point2
        {
            std::int64_t xMin;
            std::int64_t xMax;
            std::int64_t yMin;
            std::int64_t yMax;

            if (allRedTiles[i].first == allRedTiles[j].first && allRedTiles[i].second == allRedTiles[j].second)
            {
                continue;
            }

            //get xMin and xMax
            if (allRedTiles[i].first < allRedTiles[j].first)
            {
                xMin = allRedTiles[i].first;
                xMax = allRedTiles[j].first;
            }
            else
            {
                xMin = allRedTiles[j].first;
                xMax = allRedTiles[i].first;
            }

            //get yMin and yMax
            if (allRedTiles[i].second < allRedTiles[j].second)
            {
                yMin = allRedTiles[i].second;
                yMax = allRedTiles[j].second;
            }
            else
            {
                yMin = allRedTiles[j].second;
                yMax = allRedTiles[i].second;
            }
            
            //std::cout << xMin << ", " << yMin << " - " << xMax << ", " << yMax << "\n";

            Rectangle rec{xMin, xMax, yMin, yMax};
            out_allRectangles.push_back(rec);
        }
    }
}

// PROBLEME HERE
bool CheckCollision(Rectangle& rectangle, std::vector<std::pair<std::int64_t, std::int64_t>>& allRedTiles)
{
    for (size_t i = 0; i < allRedTiles.size(); i++)
    {
        std::pair<std::int64_t, std::int64_t> shapeLinePoint1;
        std::pair<std::int64_t, std::int64_t> shapeLinePoint2;

        // the last point make a line with the first one
        if (allRedTiles[i] == allRedTiles.back()) // PROBLEM : ne passe jamais ici
        {
            shapeLinePoint1 = allRedTiles[i];
            shapeLinePoint2 = allRedTiles[0];
        }
        else
        {
            shapeLinePoint1 = allRedTiles[i];
            shapeLinePoint2 = allRedTiles[i + 1];
        }

        std::cout << "current line point1 :" << shapeLinePoint1.first << ", " << shapeLinePoint1.second << "\n";
        std::cout << "current line point2 :" << shapeLinePoint2.first << ", " << shapeLinePoint2.second << "\n";

        if (shapeLinePoint1.first == shapeLinePoint2.first) // vertical
        {
            if (((shapeLinePoint1.first > rectangle.GetP1().first) && (shapeLinePoint1.first < rectangle.GetP2().first)) && (shapeLinePoint1.second < rectangle.GetP2().second) || (shapeLinePoint2.second > rectangle.GetP1().second))
            {
                return true;
            }
        }
        else if (shapeLinePoint1.second == shapeLinePoint2.second) // horizontal PROBLEM HERE : ENTRE TOUJOURS ICI
        {
            if (((shapeLinePoint1.second > rectangle.GetP1().second) && (shapeLinePoint1.second < rectangle.GetP2().second)) && (shapeLinePoint1.first < rectangle.GetP2().first) || (shapeLinePoint2.first > rectangle.GetP1().first))
            {
                return true;
            }
        }
    }
    
    return false;
}

std::int64_t CalculAreaRectangle(Rectangle& rectangle)
{
    return (std::abs(rectangle.GetP1().first - rectangle.GetP2().first) + 1) *
           (std::abs(rectangle.GetP1().second - rectangle.GetP2().second) + 1);
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
    /*auto start = high_resolution_clock::now();

    ReadFile(filePath, allRedTiles);

    finalResult = CalculAreaLargestRectangle(allRedTiles);
    std::cout << finalResult << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;*/

    //PART 2 -------------------------------------------------
    std::vector<Rectangle> AllRectangles;

    auto start = high_resolution_clock::now();
    ReadFile(filePath, allRedTiles);

    // convertir en diagonale
    GetAllRectangles(allRedTiles, AllRectangles);

    // check si collision
        // si non : calculer aire + enregistrer l'aire
    // return la plus grande
    for(Rectangle& rectangle : AllRectangles)
    {
        if (!CheckCollision(rectangle, allRedTiles))
        {
            std::int64_t rectangleArea = CalculAreaRectangle(rectangle);
            finalResult = rectangleArea > finalResult ? rectangleArea : finalResult;
        }
    }

    std::cout << finalResult << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
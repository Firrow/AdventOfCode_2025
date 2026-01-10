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

        bool FindRectangle(Rectangle& rectangle, std::vector<Rectangle>& rectangles)
        {
            for (Rectangle rec : rectangles)
            {
                if (rectangle.GetP1().first == rec.GetP1().first &&
                    rectangle.GetP1().second == rec.GetP1().second &&
                    rectangle.GetP2().first == rec.GetP2().first &&
                    rectangle.GetP2().second == rec.GetP2().second )
                {
                    return true;
                }
            }
            
            return false;
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

            Rectangle rec{xMin, xMax, yMin, yMax};
            if(!rec.FindRectangle(rec, out_allRectangles))
            {
                out_allRectangles.push_back(rec);
            }
        }
    }
}

bool CheckCollision(Rectangle& rectangle, std::vector<std::pair<std::int64_t, std::int64_t>>& allRedTiles)
{
    std::cout << "rectangle p1 :" << rectangle.GetP1().first << ", " << rectangle.GetP1().second << "\n";
    std::cout << "rectangle p2 :" << rectangle.GetP2().first << ", " << rectangle.GetP2().second << "\n";
    std::cout << "\n";

    for (size_t i = 0; i < allRedTiles.size(); i++)
    {
        std::pair<std::int64_t, std::int64_t> shapeLinePoint1;
        std::pair<std::int64_t, std::int64_t> shapeLinePoint2;

        // the last point make a line with the first one
        if (allRedTiles[i] == allRedTiles.back())
        {
            shapeLinePoint1 = allRedTiles[i];
            shapeLinePoint2 = allRedTiles[0];
        }
        else
        {
            shapeLinePoint1 = allRedTiles[i];
            shapeLinePoint2 = allRedTiles[i + 1];
        }

        //std::cout << "current line p1 :" << shapeLinePoint1.first << ", " << shapeLinePoint1.second << "\n";
        //std::cout << "current line p2 :" << shapeLinePoint2.first << ", " << shapeLinePoint2.second << "\n";
        //std::cout << "\n";

        if (shapeLinePoint1.first == shapeLinePoint2.first) // vertical
        {
            //std::cout << " - VERTICAL - " << "\n";
            /*bool part1 = (shapeLinePoint1.first > rectangle.GetP1().first);
            bool part2 = (shapeLinePoint1.first < rectangle.GetP2().first);
            bool part1et2 = ((shapeLinePoint1.first > rectangle.GetP1().first) && (shapeLinePoint1.first < rectangle.GetP2().first));
            bool part3 = (shapeLinePoint1.second < rectangle.GetP2().second);
            bool part4 = (shapeLinePoint2.second > rectangle.GetP1().second);
            bool part3et4 = ((shapeLinePoint1.second < rectangle.GetP2().second) && (shapeLinePoint2.second > rectangle.GetP1().second));
            bool tout = ((shapeLinePoint1.first > rectangle.GetP1().first) && (shapeLinePoint1.first < rectangle.GetP2().first)) && ((shapeLinePoint1.second < rectangle.GetP2().second) && (shapeLinePoint2.second > rectangle.GetP1().second));

            std::cout << " line_X > RecP1_X : " << part1 << "\n";
            std::cout << " line_X < RecP2_X : " << part2 << "\n";
            std::cout << " line_X > RecP1_X && line_X < RecP2_X : " << part1et2 << "\n";
            std::cout << " lineP1_Y < RecP2_Y : " << part3 << "\n";
            std::cout << " lineP2_Y > RecP1_Y : " << part4 << "\n";
            std::cout << " lineP1_Y < RecP2_Y && lineP2_Y > RecP1_Y : " << part3et4 << "\n";
            std::cout << " collision : " << tout << "\n";
            std::cout << " -------------------------- \n";

            if (((shapeLinePoint1.first > rectangle.GetP1().first) && (shapeLinePoint1.first < rectangle.GetP2().first)) && ((shapeLinePoint1.second < rectangle.GetP2().second) && (shapeLinePoint2.second > rectangle.GetP1().second)))
            {
                return true;
            }*/

            bool conditionX = (shapeLinePoint1.first > rectangle.GetP1().first) && (shapeLinePoint1.first < rectangle.GetP2().first);
            bool conditionY1 = (rectangle.GetP1().second <= shapeLinePoint1.second && rectangle.GetP2().second >= shapeLinePoint1.second);
            bool conditionY2 = (rectangle.GetP1().second <= shapeLinePoint2.second && rectangle.GetP2().second >= shapeLinePoint2.second);

            if (conditionX && (conditionY1 || conditionY2))
            {
                return true;
            }
        }
        else if (shapeLinePoint1.second == shapeLinePoint2.second) // horizontal
        {
            //std::cout << " - HORIZONTAL - " << "\n";
            /*bool part1 = (shapeLinePoint1.second > rectangle.GetP1().second);
            bool part2 = (shapeLinePoint1.second < rectangle.GetP2().second);
            bool part1et2 = ((shapeLinePoint1.second > rectangle.GetP1().second) && (shapeLinePoint1.second < rectangle.GetP2().second));
            bool part3 = (shapeLinePoint1.first < rectangle.GetP2().first);
            bool part4 = (shapeLinePoint2.first > rectangle.GetP1().first);
            bool part3et4 = ((shapeLinePoint1.first < rectangle.GetP2().first) && (shapeLinePoint2.first > rectangle.GetP1().first));
            bool tout = ((shapeLinePoint1.second > rectangle.GetP1().second) && (shapeLinePoint1.second < rectangle.GetP2().second)) && ((shapeLinePoint1.first < rectangle.GetP2().first) && (shapeLinePoint2.first > rectangle.GetP1().first));

            std::cout << " line_Y > RecP1_Y : " << part1 << "\n";
            std::cout << " line_Y < RecP2_Y : " << part2 << "\n";
            std::cout << " line_Y > RecP1_Y && line_Y < RecP2_Y : " << part1et2 << "\n";
            std::cout << " lineP1_X < RecP2_X : " << part3 << "\n";
            std::cout << " lineP2_X > RecP1_X : " << part4 << "\n";
            std::cout << " lineP1_X < RecP2_X && lineP2_X > RecP1_X : " << part3et4 << "\n";
            std::cout << " collision : " << tout << "\n";
            std::cout << " -------------------------- \n";

            if (((shapeLinePoint1.second > rectangle.GetP1().second) && (shapeLinePoint1.second < rectangle.GetP2().second)) && ((shapeLinePoint1.first < rectangle.GetP2().first) && (shapeLinePoint2.first > rectangle.GetP1().first)))
            {
                return true;
            }*/

            bool conditionY = (shapeLinePoint1.second > rectangle.GetP1().second) && (shapeLinePoint1.second < rectangle.GetP2().second);
            bool conditionX1 = (rectangle.GetP1().first <= shapeLinePoint1.first && rectangle.GetP2().first >= shapeLinePoint1.first);
            bool conditionX2 = (rectangle.GetP1().first <= shapeLinePoint2.first && rectangle.GetP2().first >= shapeLinePoint2.first);

            if (conditionY && (conditionX1 || conditionX2))
            {
                return true;
            }
        }
    }
    //std::cout << " PAS DE COLLISION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n";
    //std::cout << " -------------------------- \n";
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

    for(Rectangle& rectangle : AllRectangles)
    {
        if (!CheckCollision(rectangle, allRedTiles))
        {
            //std::cout << "rectangle point1 :" << rectangle.GetP1().first << ", " << rectangle.GetP1().second << "\n";
            //std::cout << "rectangle point2 :" << rectangle.GetP2().first << ", " << rectangle.GetP2().second << "\n";
            std::cout << "\n";

            std::int64_t rectangleArea = CalculAreaRectangle(rectangle);
            //std::cout << "AIRE : " << rectangleArea << "\n";
            finalResult = rectangleArea > finalResult ? rectangleArea : finalResult;

            std::cout << " -------------------------- \n";
        }
    }

    std::cout << finalResult << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
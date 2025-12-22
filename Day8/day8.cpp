#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std::chrono;


class Clustering
{
    public:
        Clustering(size_t size)
        {
            parentList.reserve(size);

            // we add to parent list the parent of each point (representing by the parentList index)
            for (int i = 0; i < size; i++)
            {
                parentList.push_back(i);
            }
        }

        // Merge two clusters by the highest points of the trees
        void MergeCluster(int pointA, int pointB)
        {
            // Get the highest point of the tree
            pointB = GetPointParent(pointB);
            pointA = GetPointParent(pointA);
            parentList[pointB] = parentList[pointA];
        }

        // Get the highest point of the tree
        int GetPointParent(int point)
        {
            while (parentList[point] != point)
            {
                point = parentList[point];
            }
            
            return point;
        }

        // Return a map with the point and the current size of his cluster
        std::unordered_map<int, int> GetSizeCluster()
        {
            std::unordered_map<int, int> clustersSize;

            for (size_t i = 0; i < parentList.size(); i++)
            {
                // Calculate the site of each cluster
                clustersSize[GetPointParent(parentList[i])] += 1; 
            }

            return clustersSize;
        }

        bool IsOnlyOneCluster()
        {
            int firstElement = GetPointParent(0);

            for (size_t i = 1; i < parentList.size(); i++)
            {
                if (GetPointParent(parentList[i]) != firstElement)
                {
                    return false;
                }
            }

            return true;
        }

    private :
        std::vector<int> parentList;
};



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
        std::cout << "Impossible to read file." << std::endl;
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

void SortPointsByDistances(std::vector<std::tuple<float, int, int>>& outAllPointsDistance)
{
    std::sort(outAllPointsDistance.begin(), outAllPointsDistance.end());

    /*for (int i = 0; i < outAllPointsDistance.size(); i++) 
        std::cout << "Distance : " << std::get<0>(outAllPointsDistance[i]) << " - " 
                  << "index1 : " << std::get<1>(outAllPointsDistance[i]) << " - "
                  << "index2 : " << std::get<2>(outAllPointsDistance[i]) << "\n";*/
}



int main()
{
    constexpr int LOOP = 1000;
    std::vector<std::tuple<int, int, int>> allPoints;
    std::vector<std::tuple<float, int, int>> allPointsDistance;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input8.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    /*auto start = high_resolution_clock::now();
    ReadFile(filePath, allPoints);

    GetDistancePoints(allPoints, allPointsDistance);

    SortPointsByDistances(allPointsDistance);

    Clustering clustering{allPoints.size()};

    for (size_t i = 0; i < LOOP; i++)
    {
        clustering.MergeCluster(std::get<1>(allPointsDistance[i]), std::get<2>(allPointsDistance[i]));
    }

    // Create a vector with all clusters and sizes
    std::vector<int> largestSizes;
    for (std::pair<int, int> cluster : clustering.GetSizeCluster())
    {
        largestSizes.push_back(cluster.second);
    }
    std::sort(largestSizes.begin(), largestSizes.end(), [](int a, int b) { return a > b; });

    int finalResult = largestSizes[0] * largestSizes[1] * largestSizes[2];

    std::cout << "finalResult : " << finalResult << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;*/

    //PART 2 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, allPoints);

    GetDistancePoints(allPoints, allPointsDistance);

    SortPointsByDistances(allPointsDistance);

    Clustering clustering{allPoints.size()};

    int i = 0;
    while (!clustering.IsOnlyOneCluster())
    {
        clustering.MergeCluster(std::get<1>(allPointsDistance[i]), std::get<2>(allPointsDistance[i]));
        i++;
    }

    // Get the X value of the two lasts points of the allPointDistance
    int finalResult = std::get<0>(allPoints[std::get<1>(allPointsDistance[i - 1])]) * std::get<0>(allPoints[std::get<2>(allPointsDistance[i - 1])]);

    std::cout << "finalResult : " << finalResult << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
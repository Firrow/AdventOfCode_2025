#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std::chrono;

int ReadFile(std::string _fileName, std::vector<std::string>& outIdsRanges, std::vector<std::string>& outIdsToProcess)
{
    std::ifstream file(_fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            if (line.empty())
            {
                break;
            }
            
            outIdsRanges.push_back(line);
        }
        while(getline(file, line)) {
            outIdsToProcess.push_back(line);
        }

        file.close();
    } 
    else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}

void ConvertRanges(std::vector<std::string>& _IdsRangesInFile, std::vector<std::pair<std::int64_t, std::int64_t>>& _IdsRanges)
{
    for (std::string range : _IdsRangesInFile)
    {
        size_t pos = range.find('-');
        assert(pos != std::string::npos); //npos = -1

        std::int64_t from = std::stoll(range.substr(0, pos));
        std::int64_t to = std::stoll(range.substr(pos + 1));

        _IdsRanges.push_back(std::make_pair(from, to));
    }
}

void SortRangesByFirstElement(std::vector<std::pair<std::int64_t, std::int64_t>>& _IdsRanges)
{
    std::sort(_IdsRanges.begin(), _IdsRanges.end());
}

//Part1
int CountIDInRange(std::vector<std::string>& _IdsRanges, std::vector<std::string>& _IdsToProcess)
{
    int count = 0;

    for (std::string range : _IdsRanges)
    {
        size_t pos = range.find('-');
        assert(pos != std::string::npos); //npos = -1

        std::int64_t from = std::stoll(range.substr(0, pos));
        std::int64_t to = std::stoll(range.substr(pos + 1));

        for (auto it = _IdsToProcess.begin(); it != _IdsToProcess.end();)
        {
            std::int64_t id = std::stoll(*it);
            if (id >= from && id <= to)
            {
                count++;
                it = _IdsToProcess.erase(it);
            }
            else {
                it++;
            }
        }
    }

    return count;
}

std::vector<std::pair<std::int64_t, std::int64_t>> SimplifyIntervals(std::vector<std::pair<std::int64_t, std::int64_t>>& _IdsRanges)
{
    std::vector<std::pair<std::int64_t, std::int64_t>> newIdsRanges;
    std::int64_t previousTo = 0;
    std::int64_t currentFrom = -1;
    std::int64_t currentTo = -1;

    for (size_t i = 0; i < _IdsRanges.size(); i++)
    {
        currentFrom = _IdsRanges[i].first;
        currentTo = _IdsRanges[i].second;

        if (currentFrom > previousTo + 1) // we create a new interval
        {
            newIdsRanges.push_back(std::make_pair(currentFrom, currentTo));
        }
        else // we modify or not the current interval
        {
            if (currentTo >= previousTo)
            {
                newIdsRanges.back().second = currentTo;
            }
        }

        previousTo = currentTo;
    }
    
    return newIdsRanges;
}

//Part2
std::int64_t CountAllValidIDs(std::vector<std::pair<std::int64_t, std::int64_t>>& _IdsRanges)
{
    std::int64_t count = 0;
    for (size_t i = 0; i < _IdsRanges.size(); i++)
    {
        count += (_IdsRanges[i].second - _IdsRanges[i].first) + 1;
    }

    return count;
}



int main()
{
    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    std::vector<std::string> IdsRangesInFile;
    std::vector<std::string> IdsToProcessInFile;
    std::vector<std::pair<std::int64_t, std::int64_t>> IdsRanges;
    std::vector<std::pair<std::int64_t, std::int64_t>> newIdsRanges;

    //   ../Inputs/input5.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    
    /*auto start = high_resolution_clock::now();
    ReadFile(filePath, IdsRangesInFile, IdsToProcessInFile);
    int finalResult = CountIDInRange(IdsRangesInFile, IdsToProcessInFile);

    std::cout << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;*/
    
    //PART 2 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, IdsRangesInFile, IdsToProcessInFile);
    ConvertRanges(IdsRangesInFile, IdsRanges);
    SortRangesByFirstElement(IdsRanges);
    newIdsRanges = SimplifyIntervals(IdsRanges);

    std::int64_t finalResult = CountAllValidIDs(newIdsRanges);

    std::cout << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
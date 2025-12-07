#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>

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
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}



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



int main()
{
    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    std::vector<std::string> IdsRanges;
    std::vector<std::string> IdsToProcess;

    //   ../Inputs/input5.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, IdsRanges, IdsToProcess);
    int finalResult = CountIDInRange(IdsRanges, IdsToProcess);

    std::cout << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
    //PART 2 -------------------------------------------------

}
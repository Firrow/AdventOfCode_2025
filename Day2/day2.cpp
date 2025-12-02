#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <chrono>
#include <set>
using namespace std::chrono;

#include <cstdint> //ajout pour version maison sinon int64_t ne passent pas
#include <algorithm>


std::vector<std::pair<std::int64_t, std::int64_t>> LineParse(std::string line, char delimiter)
{   
    std::vector<std::pair<std::int64_t, std::int64_t>> allRangesInt;
    std::vector<std::string> allRanges;
    std::stringstream stringToParse(line);
    std::string stringResult;
    
    while(getline(stringToParse, stringResult, delimiter))
    {
        size_t pos = stringResult.find('-');
        assert(pos != std::string::npos); //npos = -1

        std::int64_t from = std::stoll(stringResult.substr(0, pos));
        std::int64_t to = std::stoll(stringResult.substr(pos + 1));

        allRangesInt.push_back(std::make_pair(from, to));
    }

    return allRangesInt;
}

int ReadFile(std::string fileName, std::vector<std::pair<std::int64_t, std::int64_t>>& outIdsRanges)
{
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            outIdsRanges = LineParse(line, ',');
        }
        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}

std::int64_t CalculInvalidIDsQuantity(std::vector<std::pair<std::int64_t, std::int64_t>>& idsRanges, int part)
{
    std::int64_t invalidIDsTotal = 0;

    switch (part)
    {
        case 1:
            for(auto it = idsRanges.begin(); it != idsRanges.end(); it++)
            {
                for (std::int64_t id = it->first; id <= it->second; id++)
                {
                    // convertir id en stringid
                    std::string stringID = std::to_string(id);
                    if (stringID.length() % 2 == 0)
                    {
                        // séparer stringID en 2 (avec substr)
                        std::string idPart1 = stringID.substr(0, stringID.length() / 2);
                        std::string idPart2 = stringID.substr(stringID.length() / 2);
                    
                        // si les deux parties sont ==
                        if (idPart1 == idPart2)
                        {
                            invalidIDsTotal += id;
                        }
                    }
                }
            }
            break;
        case 2:
            for(auto it = idsRanges.begin(); it != idsRanges.end(); it++)
            {
                for (std::int64_t id = it->first; id <= it->second; id++)
                {
                    // convertir id en stringid
                    std::string stringID = std::to_string(id);
                    int patternLen = 1;
                    bool isAValidPattern = false;

                    while (patternLen <= stringID.length() / 2) // si la longueur du pattern est inférieure à la moitié de la longueur du mot
                    {
                        if ((stringID.length() % patternLen == 0) && isAValidPattern == false) // si la longueur du pattern permet de diviser la longueur de la chaine de chara
                        {
                            // on check s'il existe au moins un pattern
                            std::vector<std::string> chunks;
                            for (size_t pos = 0; pos < stringID.length(); pos+=patternLen)
                            {
                                chunks.push_back(stringID.substr(pos, patternLen));
                            }

                            bool allEqual = true;
                            for (const auto& s : chunks) {
                                if (s != chunks[0]) {
                                    allEqual = false;
                                    break;
                                }
                            }

                            if (allEqual) {
                                isAValidPattern = true;
                            }
                        }
                        
                        patternLen++;
                    }

                    if (isAValidPattern)
                    {
                        invalidIDsTotal += id;
                        continue;
                    }
                }
            }
            break;
        default:
            break;
    }

    return invalidIDsTotal;
}


int main()
{
    std::vector<std::pair<std::int64_t, std::int64_t>> allIdsRanges;
    std::int64_t finalResult = -1;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input2.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    /*auto start = high_resolution_clock::now();
    ReadFile(filePath, allIdsRanges);
    finalResult = CalculInvalidIDsQuantity(allIdsRanges, 1);

    std::cout << "Final result: " << finalResult << "\n";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;*/

    //PART 2 -------------------------------------------------
    auto start = high_resolution_clock::now();

    ReadFile(filePath, allIdsRanges);
    finalResult = CalculInvalidIDsQuantity(allIdsRanges, 2);
    std::cout << "Final result: " << finalResult << "\n";

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
            
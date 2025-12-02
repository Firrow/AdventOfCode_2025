#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>

#include <cstdint> //ajout pour version maison sinon int64_t ne passent pas


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

std::int64_t CalculInvalidIDsQuantity(std::vector<std::pair<std::int64_t, std::int64_t>>& idsRanges)
{
    std::int64_t invalidIDsTotal = 0;

    for(auto it = idsRanges.begin(); it != idsRanges.end(); it++)
    {
		//std::cout << it->first << std::endl;
		//std::cout << it->second << std::endl;

        for (std::int64_t id = it->first; id <= it->second; id++)
        {
            // convertir id en stringid
            std::string stringID = std::to_string(id);
            // si stringID a un nombre de character pair : if stringID.lenght() % 2 == 0
            if (stringID.length() % 2 == 0)
            {
                std::cout << stringID << std::endl;
                // séparer stringID en 2 (avec substr)
                std::string idPart1 = stringID.substr(0, stringID.length() / 2);
                std::string idPart2 = stringID.substr(stringID.length() / 2);
                
                std::cout << idPart1 << " | " << idPart2 << std::endl;

                // si les deux parties sont ==
                if (idPart1 == idPart2)
                {
                    invalidIDsTotal += id;
                }
                
                //invalidIDsQuantity += idPart1 == idPart2 ? id : 0;
            }
        }
        std::cout << "------------------------------" << std::endl;
    
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
    ReadFile(filePath, allIdsRanges);
    finalResult = CalculInvalidIDsQuantity(allIdsRanges);
    std::cout << "Final result: " << finalResult << "\n";
    //PART 2 -------------------------------------------------
}
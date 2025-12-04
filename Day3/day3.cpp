#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <chrono>
using namespace std::chrono;



int ReadFile(std::string fileName, std::vector<std::string>& banks)
{
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            banks.push_back(line);
        }
        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }

    return 0;
}

void GetJoltageBank(std::string& bank, std::vector<int>& outBatteriesBank)
{
    for (int i = 0; i < bank.length(); i++)
    {
        outBatteriesBank.push_back(std::stoi(std::string(1, bank[i])));
    }
}

int GetPositionInVector(std::vector<int>& v, int searchValue)
{
    return std::find(v.begin(), v.end(), searchValue) - v.begin();
}

int GetHighterJoltagePart1(std::vector<int>& batteriesBank)
{
    int biggerJoltagInBank = -1;
    int totalJoltageOfBank = -1;

    for (int i = 0; i < batteriesBank.size(); i++)
    {
        if (batteriesBank[i] > biggerJoltagInBank)
        {
            biggerJoltagInBank = batteriesBank[i];
        }
    }

    int posJoltage = GetPositionInVector(batteriesBank, biggerJoltagInBank);

    // for each element before the bigger
    for (int i = 0; i < posJoltage; i++)
    {
        std::string calculJoltageString = std::to_string(batteriesBank[i]) + std::to_string(biggerJoltagInBank);
        int calculJoltage = std::stoi(calculJoltageString);

        if (calculJoltage > totalJoltageOfBank)
        {
            totalJoltageOfBank = calculJoltage;
        }
    }
    // for each element after the bigger
    for (int i = posJoltage + 1; i < batteriesBank.size(); i++)
    {
        std::string calculJoltageString = std::to_string(biggerJoltagInBank) + std::to_string(batteriesBank[i]);
        int calculJoltage = std::stoi(calculJoltageString);

        if (calculJoltage > totalJoltageOfBank)
        {
            totalJoltageOfBank = calculJoltage;
        }
    }

    return totalJoltageOfBank;
}

std::int64_t GetHighterJoltagePart2(std::vector<int>& batteriesBank, int batteriesQuantity)
{
    // interval = [previousPos+1 ; (-bankLen + 1) + x]
    std::string totalJoltageOfBankString = "";
    std::int64_t totalJoltageOfBank = 0;
    int previousPos = -1;
    int lenInterval = batteriesBank.size() - batteriesQuantity + 1;


    //for (int x = 0; x < batteriesBank.size(); x++) // on parcours la banque
    while (batteriesQuantity >= 0)
    {
        int biggerInInterval = -1;

        //At the end of the bank, the interval decrease to avoid "out of range"
        if (batteriesQuantity <= lenInterval)
        {
            lenInterval--;
        }

        for (int y = previousPos + 1; y <= previousPos + 1 + lenInterval; y++) // on parcourt le petit interval où peut se trouver le chiffre le plus grand qui nous interesse
        {
            //trouver le plus gros
            std::cout << "element actuel : " << batteriesBank[y] << "\n";
            if (batteriesBank[y] > biggerInInterval)
            {
                biggerInInterval = batteriesBank[y];
            }
            
        }

        std::cout << "plus gros dans l'interval [ " << previousPos + 1 << " - " << (previousPos + 1 + lenInterval) << " ] => " << biggerInInterval << "\n";

        //ajouter le plus gros à la chaine de character (concaténation)
        std::string biggerInIntervalString = std::to_string(biggerInInterval);
        totalJoltageOfBankString += biggerInIntervalString;

        //calcul position biggerInInterval dans bank
        int qttOccurrenceValueBiggerInTotalJoltageOfBankString = std::count(totalJoltageOfBankString.begin(), totalJoltageOfBankString.end(), biggerInIntervalString.at(0));
        int count = 0;
        if (qttOccurrenceValueBiggerInTotalJoltageOfBankString > 1)
        {
            for (int p = 0; p <= totalJoltageOfBankString.size(); ++p) 
            {
                std::string eTemp = std::string(1, totalJoltageOfBankString[p]);
                //std::cout << "element actuel : " << eTemp << "\n";
                //std::cout << "biggerInIntervalString actuel : " << biggerInIntervalString << "\n";
                if (eTemp == biggerInIntervalString) {
                    count++;
                    if (count == qttOccurrenceValueBiggerInTotalJoltageOfBankString) {
                        previousPos = p;
                    }
                }
            }
        }
        else
        {
            previousPos = GetPositionInVector(batteriesBank, biggerInInterval);
        }
        
        batteriesQuantity--;
    }

    //convertir chiffre final
    totalJoltageOfBank = std::stoll(totalJoltageOfBankString);
    std::cout << "plus gros actuel: " << totalJoltageOfBank << "\n";

    //return chiffre final
    return totalJoltageOfBank;
}



int main()
{
    std::vector<std::string> batteriesBanks;
    std::vector<int> convertBatteriesBank;
    int finalResult = 0;
    std::int64_t finalResult2 = 0;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input3.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    /*auto start = high_resolution_clock::now();
    ReadFile(filePath, batteriesBanks);

    for (std::string bank : batteriesBanks)
    {
        GetJoltageBank(bank, convertBatteriesBank);
        int biggerJoltage = GetHighterJoltagePart1(convertBatteriesBank);
        finalResult += biggerJoltage;

        convertBatteriesBank.clear();
    }

    std::cout << "Final result: " << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;*/

    //PART 2 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, batteriesBanks);

    for (std::string bank : batteriesBanks)
    {
        std::cout << "BANK ACTUELLE : " << bank << "\n";
        GetJoltageBank(bank, convertBatteriesBank);
        std::int64_t biggerJoltage = GetHighterJoltagePart2(convertBatteriesBank, 12);
        finalResult2 += biggerJoltage;

        convertBatteriesBank.clear();
        std::cout << " ------------------ " << "\n";
    }

    std::cout << "Final result: " << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
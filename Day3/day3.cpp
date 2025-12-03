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

int GetHighterJoltage(std::vector<int>& batteriesBank)
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

    int posJoltage = std::find(batteriesBank.begin(), batteriesBank.end(), biggerJoltagInBank) - batteriesBank.begin();

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



int main()
{
    std::vector<std::string> batteriesBanks;
    std::vector<int> convertBatteriesBank;
    int finalResult = 0;

    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input3.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    auto start = high_resolution_clock::now();
    ReadFile(filePath, batteriesBanks);

    for (std::string bank : batteriesBanks)
    {
        GetJoltageBank(bank, convertBatteriesBank);
        int biggerJoltage = GetHighterJoltage(convertBatteriesBank);
        finalResult += biggerJoltage;

        convertBatteriesBank.clear();
    }

    std::cout << "Final result: " << finalResult << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
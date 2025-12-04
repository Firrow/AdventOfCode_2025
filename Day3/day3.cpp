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

// FIRST SOLUTION FOUND FOR PART 1 :
//1. Get the bigger element of the bank
//2. Create a number of two element with all digit before and after the bigger
//3. At each time you create a number, compare it with the previous to know which one is the biggest
//4. return the last biggest
/*int GetHighterJoltagePart1(std::vector<int>& batteriesBank)
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
}*/

// SOLUTION FOUND FOR PART 2 WHO WORK FOR THE PART 1 TOO
std::int64_t GetHighterJoltage(std::vector<int>& batteriesBank, int batteriesQuantity)
{
    // interval = [previousBiggerPosition + 1; batteriesBank.len - batteriesQuantity]
    std::string totalJoltageOfBankString = "";
    std::int64_t totalJoltageOfBank = 0;
    int previousPos = -1;

    // go through the bank
    for (int i = batteriesQuantity; i > 0; i--)
    {
        int biggerInInterval = -1;
        int biggerPos = 0;
        int lenInterval = batteriesBank.size() - batteriesQuantity;

        for (int y = previousPos + 1; y <= lenInterval; y++) // go through the interval where we can find the bigger digit for the final result digit position 
        {
            //find the bigger
            if (batteriesBank[y] > biggerInInterval)
            {
                biggerInInterval = batteriesBank[y];
                biggerPos = y;
            }
        }

        previousPos = biggerPos;

        //add the bigger to the final result
        std::string biggerInIntervalString = std::to_string(biggerInInterval);
        totalJoltageOfBankString += biggerInIntervalString;

        batteriesQuantity--;
    }

    //return the convert result
    return std::stoll(totalJoltageOfBankString);
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
        GetJoltageBank(bank, convertBatteriesBank);
        std::int64_t biggerJoltage = GetHighterJoltage(convertBatteriesBank, 12);
        finalResult2 += biggerJoltage;

        convertBatteriesBank.clear();
    }

    std::cout << "Final result: " << finalResult2 << "\n";
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
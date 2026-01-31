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
#include <bitset>
#include <assert.h>

using namespace std::chrono;
using BitSet = std::bitset<16>;


struct Machine
{
    BitSet objectif;
    std::vector<BitSet> buttons;
    std::vector<int> joltage;
};

Machine ParseLine(std::string& line)
{   
    std::istringstream streamLine { line };
    std::string element;
    Machine machine{};

    while (std::getline(streamLine, element, ' '))
    {
        switch (element[0])
        {
            case '[':
                {
                    machine.objectif = BitSet{element.data()+1, element.size()-2, '.', '#'};
                }
                break;
            case '(':
                {
                    BitSet bitset{}; // create bitset with 0

                    for (size_t i = 1; i < element.size() - 1; i++) // fill bitset thanks to buttons value
                    {
                        if(element[i] != ',')
                        {
                            bitset.set(element[i]-'0', true); // -'0' : 0 car dans table ASCII = 48 donc on fait X en valeur ASCII - 48)
                        }
                    }

                    machine.buttons.push_back(bitset); // add the filled bitset to the machine
                }
                break;
            case '{':
                {
                    std::vector<int> joltages{};
                    std::string newValue = "";

                    for (size_t i = 1; i < element.size() - 1; i++)
                    {
                        if(element[i] != ',')
                        {
                            newValue.push_back(element[i]);
                        }
                        else
                        {
                            joltages.push_back(std::stoi(newValue));
                            newValue = "";
                        }
                    }

                    joltages.push_back(std::stoi(newValue));
                    machine.joltage = joltages;
                }
                break;
            default:
                break;
        }
    }

    return machine;
}

int ReadFile(std::string _fileName, std::vector<Machine>& outMachines)
{
    std::ifstream file(_fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            if (line.empty())
            {
                break;
            }
            
            outMachines.push_back(ParseLine(line));
        }
        file.close();
    } 
    else {
        std::cout << "Impossible to read file." << std::endl;
    }

    return 0;
}




int main()
{
    std::vector<Machine> machines;
    std::int64_t finalResult = 0;

    std::string filePath;
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input10.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    auto start = high_resolution_clock::now();

    ReadFile(filePath, machines);

    //std::cout << finalResult << "\n";

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "EXECUTION TIME (s): " << duration.count() / 1000000.0 << std::endl;
}
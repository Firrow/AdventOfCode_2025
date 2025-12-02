#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <cmath>



int LineParse(std::string element)
{
    int result = std::stoi(element.substr(1, element.length()));
    return element.substr(0, 1) == "L" ? result*-1 : result;
}

std::pair<int, int> ParseDelta(int delta)
{
    int centaine;
    int dizaine;
    delta = abs(delta);
    
    centaine = delta < 100 ? 0 : delta / 100;
    dizaine = delta < 100 ? delta : delta % 100;

    return std::make_pair(centaine, dizaine);
}

int ReadFile(std::string fileName, int start, int partProblem)
{
    int decoyValue = start;
    int result = 0;
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            int delta = LineParse(line);
            switch (partProblem)
            {
                case 1:
                {
                    decoyValue = (decoyValue + delta) % 100;
                    result += decoyValue == 0 ? 1 : 0;

                    break;
                }
                case 2:
                {
                    std::pair<int, int> splitDelta = ParseDelta(delta);

                    result += splitDelta.first;                                     //=> we add the value of the hundred to the result
                    if (delta < 0)                                                  // if rotation is to the left (Lxx) =>  we add +1 if the tens number is bigger than the current decoy value
                    {
                        result += (splitDelta.second >= decoyValue && decoyValue != 0) ? 1 : 0;
                    }
                    else                                                            // if rotation is to the right (Rxx) =>  we add +1 if the tens number exceeds the value to reach zero on decoy
                    {
                        result += splitDelta.second >= 100 - decoyValue ? 1 : 0;
                    }

                    decoyValue = (decoyValue + delta) % 100;                        //we get value between -99 and 99
                    decoyValue = decoyValue < 0 ? decoyValue + 100 : decoyValue;    //we get value between 0 and 99

                    break;
                }
                default:
                    break;
            }
        }
        file.close();
    } else {
        std::cout << "Cannot open the file." << std::endl;
    }
    
    return result;
}


int main()
{
    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input.txt
    //   ../Inputs/inputTest.txt

    //PART 1 -------------------------------------------------
    //std::cout << ReadFile(filePath, 50, 1);

    //PART 2 -------------------------------------------------
    std::cout << ReadFile(filePath, 50, 2);

    return 0;
}
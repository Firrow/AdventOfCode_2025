#include <iostream>
#include <fstream>
#include <string>



int LineParse(std::string element)
{
    int result = std::stoi(element.substr(1, element.length()));
    return element.substr(0, 1) == "L" ? result*-1 : result;
}

int ReadFile(std::string fileName, int start, int partProblem)
{
    int temp = start;
    int result = 0;
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            //parse
            std::cout << "parse :" << LineParse(line) << "\n";
            //calcul previous + line
            temp = (temp + LineParse(line)) % 100;
            std::cout << "temp :" << temp << "\n";
            //check if +1 or not
            switch (partProblem)
            {
                case 1:
                    if (temp == 0)
                    {
                        result++;
                    }
                    break;
                /*case 2:
                    if (temp)
                    {
                    }
                    break;*/
                default:
                    break;
            }
            
            std::cout << " ----------------------------------- \n";
        }
        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }
    
    return result;
}



int main()
{
    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    //   ../Inputs/input.txt
    //PART 1 -------------------------------------------------
    std::cout << ReadFile(filePath, 50, 1);

    //PART 2 -------------------------------------------------
    //std::cout << ReadFile(filePath, 0, 2);
}
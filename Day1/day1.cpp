#include <iostream>
#include <fstream>
#include <string>



int LineParse(std::string element)
{
    int result = std::stoi(element.substr(1, element.length()));
    return element.substr(0, 1) == "L" ? result*-1 : result;
}

//void ParseCalculResult(int resultAddition)
std::pair<int, int> ParseCalculResult(int resultAddition)
{
    std::cout << "temp :" << resultAddition << "\n";

    int centaine;
    int dizaine;

    // si le nombre est composé de 1 ou 2 chiffres
    if (resultAddition < 0)
    {
        std::string numberToGetDizaine = std::to_string(resultAddition);
        resultAddition = std::stoi(numberToGetDizaine.substr(1));
    }
    
    if (resultAddition < 100)
    {
        centaine = 0;
        dizaine = resultAddition;
    }
    else
    {
        centaine = resultAddition / 100;

        std::string numberToGetDizaine = std::to_string(resultAddition);
        dizaine = std::stoi(numberToGetDizaine.substr(numberToGetDizaine.length()-2));
    }

    return std::make_pair(centaine, dizaine);
}

int CalculNumberZeroCrossing(int centaine, int dizaine, int start, int temp)
{
    
    //return crossingNumber;
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
            //check if +1 or not
            switch (partProblem)
            {
                case 1:
                {
                    //calcul previous + line
                    temp = (temp + LineParse(line)) % 100;
                    if (temp == 0)
                    {
                        result++;
                    }
                    break;
                }
                case 2:
                {
                    temp = temp + LineParse(line);
                    std::pair<int, int> decomposition = ParseCalculResult(temp);
                    std::cout << "CENTAINE  :" << decomposition.first << "\n";
                    std::cout << "DIZAINE :" << decomposition.second << "\n";
                    //result += CalculNumberZeroCrossing(decomposition.first, decomposition.second, start, temp);
                    //std::cout << "result temporaire :" << result << "\n";
                    break;
                }
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
    //std::cout << ReadFile(filePath, 50, 1);

    //PART 2 -------------------------------------------------
    std::cout << ReadFile(filePath, 50, 2);
}
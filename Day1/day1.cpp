#include <iostream>
#include <fstream>
#include <string>



int LineParse(std::string element)
{
    int result = std::stoi(element.substr(1, element.length()));
    return element.substr(0, 1) == "L" ? result*-1 : result;
}

int ReadFile(std::string fileName, int start)
{
    int temp = start;
    std::ifstream file(fileName);
    std::string line;
    
    if(file.is_open()) {
        while(getline(file, line)) {
            std::cout << line << '\n';
            //parse
            //calcul previous + line
            //check if +1 or not
        }
        file.close();
    } else {
        std::cout << "Impossible d'ouvrir le fichier." << std::endl;
    }
    
    return 0;
}



int main()
{
    std::string filePath; 
    std::cout << "Enter the input file: ";
    std::cin >> filePath;

    ReadFile(filePath, 0);
}
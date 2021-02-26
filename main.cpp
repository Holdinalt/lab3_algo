#include <iostream>
#include <map>

void startBlock(std::map <std::string, int>);

int main() {
    static std::map <std::string, int> mainMap;

    std::string input;

    while (std::cin >> input) {

        //std::cout << input << " input\n";

        int separator = input.find('=');

        if (input == "{"){
            startBlock(mainMap);
            continue;
        }

        try{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            mainMap[input.substr(0, separator)] = number;
        } catch (...){
            int argValue = mainMap[input.substr(separator + 1)]; //variable
            std::cout << argValue << "\n";
            mainMap[input.substr(0, separator)] = argValue;
        }
    }

    return 0;
}

void startBlock(std::map <std::string, int> thisMap){
    //std::cout << "started new block\n";
    std::string input;
    std::cin >> input;
    while(input != "}"){
        //std::cout << input << " input\n";
        int separator = input.find('=');

        if (input == "{"){
            startBlock(thisMap);
            std::cin >> input;
            continue;
        }

        try{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            thisMap[input.substr(0, separator)] = number;
        } catch (...){
            int argValue = thisMap[input.substr(separator + 1)]; //variable
            std::cout << argValue << "\n";
            thisMap[input.substr(0, separator)] = argValue;
        }
        std::cin >> input;
    }
    //std::cout << "block end\n";
}


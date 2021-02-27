#include <iostream>
#include <map>
#include <vector>

void startBlock();
int getValFromMap(std::string);
void blockStart();
void blockEnd();

int cacheTime = 10;

std::vector<std::map <std::string, int>> mapVector;

std::map <std::string, int> cacheMap;

int main() {


    std::string input;

    mapVector.emplace_back(); //addMap

    while (std::cin >> input) {

        //std::cout << input << " input\n";

        if (input == "{"){
            startBlock();
            continue;
        }

        int separator = input.find('=');

        try{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            mapVector[0][input.substr(0, separator)] = number;
        } catch (...){
            int argValue = mapVector[0][input.substr(separator + 1)]; //variable
            std::cout << argValue << "\n";
            mapVector[0][input.substr(0, separator)] = argValue;
        }
    }

    return 0;
}

void startBlock(){
    blockStart();
    //std::cout << "started new block\n";
    std::string input;
    std::cin >> input;
    while(input != "}"){
        //std::cout << input << " input\n";

        if (input == "{"){
            startBlock();
            std::cin >> input;
            continue;
        }

        int separator = input.find('=');

        try{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            mapVector.back()[input.substr(0, separator)] = number;
            cacheMap[input.substr(0, separator)] = number;
        } catch (...){
            int argValue = getValFromMap(input.substr(separator + 1)); //variable

            std::cout << argValue << "\n";
            mapVector.back()[input.substr(0, separator)] = argValue;
            cacheMap[input.substr(0, separator)] = argValue;
        }
        std::cin >> input;
    }
    blockEnd();
    //std::cout << "block end\n";
}

int getValFromMap(const std::string str){
    unsigned int i = mapVector.size();
    while (i > 0){
        if(mapVector[i-1].count(str) == 1){
            return mapVector[i-1][str];
        }
        i--;
    }
    return 0;
}

void blockStart(){
    if(mapVector.size() % cacheTime == 0){
        mapVector.push_back(cacheMap);
    }
    mapVector.emplace_back(); //addMap
}

void blockEnd(){
    mapVector.pop_back();
    if(mapVector.size() % cacheTime == 0){
        mapVector.pop_back();
    }
}
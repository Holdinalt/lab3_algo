#include <iostream>
#include <map>
#include <vector>

void startBlock();
int getValFromMap(const long*);
void blockStart();
void blockEnd();

int cacheTime = 50;

std::vector<std::map <long, int>> mapVector;

std::map <long, int> cacheMap;

int main() {


    std::string input;

    mapVector.emplace_back(); //addMap

    while (std::cin >> input) {

        //std::cout << input << " input\n";

        int separator = input.find('=');

        if (input == "{"){
            startBlock();
            continue;
        }

        try{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            mapVector.back()[std::hash<std::string>{}((input.substr(0, separator)))] = number;
        } catch (...){
            int argValue = mapVector.back()[std::hash<std::string>{}(input.substr(separator + 1))]; //variable
            std::cout << argValue << "\n";
            mapVector.back()[std::hash<std::string>{}((input.substr(0, separator)))] = argValue;
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
        int separator = input.find('=');

        if (input == "{"){
            startBlock();
            std::cin >> input;
            continue;
        }

        try{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            mapVector.back()[std::hash<std::string>{}(input.substr(0, separator))] = number;
            cacheMap[std::hash<std::string>{}(input.substr(0, separator))] = number;
        } catch (...){
            long hash = std::hash<std::string>{}(input.substr(separator + 1));
            int argValue = getValFromMap(&hash); //variable

            std::cout << argValue << "\n";
            mapVector.back()[std::hash<std::string>{}(input.substr(0, separator))] = argValue;
            cacheMap[std::hash<std::string>{}(input.substr(0, separator))] = argValue;
        }
        std::cin >> input;
    }
    blockEnd();
    //std::cout << "block end\n";
}

int getValFromMap(const long *hash){
    unsigned int i = mapVector.size();
    while (i > 0){
        if(mapVector[i-1].count(*hash) == 1){
            return mapVector[i-1][*hash];
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
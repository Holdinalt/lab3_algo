#include <iostream>
#include <map>
#include <vector>

std::map <int, int> makeCacheMap();
void startBlock();
int getValFromMap(int);
void blockStart();
void blockEnd();
int getVariableId(std::string str);

int cacheTime = 1000;

std::vector<std::map <int, int>> mapVector;

int counter = 1;

std::map <std::string, int> hashMap;


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

        bool variable = true;

        for (char elem : input.substr(separator + 1)){
            unsigned int intElem = (int)elem;
            if ((intElem >= 48 && intElem <=57) || intElem == 45){
                variable = false;
            }
        }

        if(variable){
            int argValue = mapVector[0][getVariableId(input.substr(separator + 1))]; //variable
            std::cout << argValue << "\n";
            mapVector[0][getVariableId(input.substr(0, separator))] = argValue;
        } else{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            mapVector[0][getVariableId(input.substr(0, separator))] = number;
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

        bool variable = true;

        for (char elem : input.substr(separator + 1)){
            unsigned int intElem = (int)elem;
            if ((intElem >= 48 && intElem <=57) || intElem == 45){
                variable = false;
            }
        }

        if(variable){
            int argValue = getValFromMap(getVariableId(input.substr(separator + 1))); //variable

            std::cout << argValue << "\n";
            mapVector.back()[getVariableId(input.substr(0, separator))] = argValue;
        } else{
            int number = std::stoi(input.substr(separator + 1)); //number
            //std::cout << input.substr(0, separator) << " = " << number << "\n";
            mapVector.back()[getVariableId(input.substr(0, separator))] = number;
        }
        std::cin >> input;
    }
    blockEnd();
    //std::cout << "block end\n";
}

int getValFromMap(const int str){
    int i = (int)mapVector.size() - 1;

    while (i > -1){
        if(mapVector[i].count(str) == 1){
            return mapVector[i][str];
        }
        i--;
    }
    return 0;
}

void blockStart(){
    if(mapVector.size() % cacheTime == 0){
        mapVector.push_back(makeCacheMap());
    }
    mapVector.emplace_back();
}

void blockEnd(){
    mapVector.pop_back();
    if(mapVector.size() % cacheTime == 0){
        mapVector.pop_back();
    }
}

std::map <int, int> makeCacheMap(){

    std::map <int, int> cacheMap;

    int size = mapVector.size();

    for (unsigned int i = (size / cacheTime - 1) * cacheTime; i < size; ++i){
        for(const auto& pair : mapVector[i]) {
            cacheMap[pair.first] = pair.second;
        }
    }
    return cacheMap;
}

int getVariableId(std::string str){
    if (hashMap[str] != 0){
        return hashMap[str];
    }else{
        hashMap[str] = counter;
        counter++;
        return counter - 1;
    }
}
#include "fenparser.h"
#include <string>
#include <iostream>

void FenParser::parseFen(std::string& fenPosition, int board[][8]){
     for (int i = 0; i < fenPosition.length(); i++){
        std::cout << fenPosition[i];
    }
}


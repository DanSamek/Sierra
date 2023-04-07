#include <string>

#ifndef board_h
#define board_h

namespace Board{

class board
{
public:
    int* board;
    bool player;
    bool* castles;
    std::string enPassand;
    int halfMoveClock;
    int fullMoveNumber;
};
void parseFen(std::string& fen);

}    

#endif
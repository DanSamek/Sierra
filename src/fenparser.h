#include <string>

#ifndef fenparser_h
#define fenparser_h

namespace FenParser{
    void parseFen(std::string& fen, int board[][8]);
}    

#endif
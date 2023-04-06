#include<string>
#include "fenparser.cpp"
std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

int main(int argc, char* argv[]){
	if(argv[1]) FEN = argv[1];	
	int board[8][8];
	FenParser::parseFen(FEN, board);
	return 0;
}
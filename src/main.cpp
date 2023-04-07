#include<string>
#include "board.cpp"
std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int main(int argc, char* argv[]){
	if(argv[1]) FEN = argv[1];	
	Board::parseFen(FEN);
	return 0;
}
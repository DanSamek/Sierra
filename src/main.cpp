#include<string>
#include "board.cpp"
std::string FEN = "rnbqkbnr/8/8/pppppppp/PPPP1PPP/8/8/RNBQKBNR w KQkq h6 0 1";

int main(int argc, char* argv[]){
	if(argv[1] == "FEN"){
		Board::parseFen(FEN);
	} 
	if (argv[1] == "perft"){
		int perftDepth = (int)argv[2] - '0';
		// Todo
	} 
	return 0;
}
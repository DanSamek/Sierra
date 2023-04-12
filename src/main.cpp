#include<string>
#include "board.cpp"
#include "movegen.cpp"
std::string FEN = "3k4/8/8/2R5/8/5R2/8/3K4 w - - 0 1";

int main(int argc, char* argv[]){
	if(argc < 2)	
	{
		std::cout << "2 args needed!!";
		return 0;
	}
	std::string task(argv[1]);
	//std::string FEN(argv[2]);
	if(task == "FEN"){
		Board::board b = Board::parseFen(FEN);
		Movegen::generateAllMoves(b.board, b.player);
	} 
	if (task == "perft"){
		// max depth 9
		int perftDepth = (int)argv[2] - '0';
	} 
	return 0;
}
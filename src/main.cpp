#include<string>
#include "board.cpp"
#include "movegen.cpp"
std::string FEN = "k7/8/8/5pP1/8/8/8/K7 w - f6 0 1";

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
		Movegen::generateAllMoves(b, b.player);
	} 
	if (task == "perft"){
		// max depth 9
		int perftDepth = (int)argv[2] - '0';
	} 
	return 0;
}
#include "8puzzle.h"

eightpuzzle::eightpuzzle(){ //default constructor
	root = nullptr;
}
void eightpuzzle::startGame(){
	block* b = new block;
	vector<char> top = {'1', '2', '3'};
	vector<char> mid = {'4','5','6'};
	vector<char> bottom = {'7', '*', '8'};
	b->board.push_back(top);
	b->board.push_back(mid);
	b->board.push_back(bottom);
	outputPuzzle(b);
}
void eightpuzzle::outputPuzzle(block* cur){
	for(unsigned i = 0; i < 3; i++){ //output the puzzle line by line
			for(unsigned j = 0; j < 3; j++){
				cout << cur->board.at(i).at(j) << " ";
			}
			cout << endl;
		}

}
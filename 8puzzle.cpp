#include "8puzzle.h"

eightpuzzle::eightpuzzle(){ //default constructor
	root = nullptr;
}
void eightpuzzle::startGame(){
	block* b = new block;
	bool foundGoal = false;
    nodesExpanded = 0;
    queueNodes = 0;

	//sample board

	b->board = {'1', '2', '3', '4', '5', '6', '7', '*', '8'};

	//initialize parent and children
	b->up = nullptr;
	b->down = nullptr;
	b->right = nullptr;
	b->left = nullptr;
	b->parent = nullptr;

	//prrint out puzzle 
	outputPuzzle(b);
	solveCheck(b->board);
}
void eightpuzzle::outputPuzzle(block* cur){
	for(unsigned i = 0; i < 9; i++){ //output the puzzle line by line
			cout << cur->board.at(i) << " ";
			if((i+1) % 3 == 0 ){
				cout << endl;
			}
	}
}

bool eightpuzzle::solveCheck(vector<char> board){
	vector<char> solution = {'1', '2', '3', '4', '5', '6', '7', '8', '*'};
	cout << "in check" << endl;
	if(board == solution){
		cout << "true";
		return true;
	}
	else {
		cout << "false";
		return false;
		
	}
}
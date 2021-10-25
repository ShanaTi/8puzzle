#include "8puzzle.h"

eightpuzzle::eightpuzzle(){ //default constructor
	root = nullptr;
}
void eightpuzzle::startGame(){
	block* b = new block;
	bool foundGoal = false;

	//sample board
	vector<char> top = {'1', '2', '3'};
	vector<char> mid = {'4','5','6'};
	vector<char> bottom = {'7', '*', '8'};
	b->board.push_back(top);
	b->board.push_back(mid);
	b->board.push_back(bottom);

	//initialize parent and children
	b->up = nullptr;
	b->down = nullptr;
	b->right = nullptr;
	b->left = nullptr;

	//prrint out puzzle 
	outputPuzzle(b);
	solveCheck(b->board);
}
void eightpuzzle::outputPuzzle(block* cur){
	for(unsigned i = 0; i < 3; i++){ //output the puzzle line by line
			for(unsigned j = 0; j < 3; j++){
				cout << cur->board.at(i).at(j) << " ";
			}
			cout << endl;
		}
}

bool eightpuzzle::solveCheck(vector<vector<char>> board){
	vector<vector<char>> solution;
	vector<char> topSol = {'1', '2', '3'};
	vector<char> midSol = {'4','5','6'};
	vector<char> bottomSol = {'7', '8', '*'};

	solution.push_back(topSol);
	solution.push_back(midSol);
	solution.push_back(bottomSol);

	if(board == solution){
		return true;
		cout << "true";
	}
	else {
		return false;
		cout << "false";
	}
}
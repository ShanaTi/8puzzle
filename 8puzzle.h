#ifndef _8puzzle_h_included_
#define _8puzzle_h_included_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

struct block{ //  node with 4 children(4 directions)
    vector<vector<char>> board; //vector with puzzle board
	block* up; // child that has the blank move up
	block* down; // child that has the blank move down
	block* left; // child that has the blank move left
	block* right; // child that has the blank move right
	block* parent; // keeps track of parent node
	
};
class eightpuzzle{ 
    private: 
    block* root; 
    block* goal; // goal state
    bool foundGoal; // marks if the goal state has been found or not
    bool solveCheck(vector<vector<char>>); // tests if the current puzzle is solved
    public:
    eightpuzzle();
    void startGame();
    void outputPuzzle(block*);
};

//////////////////////////////////////////////////////////
// definitions temporary
//////////////////////////////////////////////////////////

eightpuzzle::eightpuzzle(){ //default constructor
	root = nullptr;
}
void eightpuzzle::startGame(){
	block* b = new block;
	bool foundGoal = false;

	//sample board
	vector<char> top = {'1', '2', '3'};
	vector<char> mid = {'4','5','6'};
	vector<char> bottom = {'7', '8', '*'};
	b->board.push_back(top);
	b->board.push_back(mid);
	b->board.push_back(bottom);

	//initialize parent and children
	b->up = nullptr;
	b->down = nullptr;
	b->right = nullptr;
	b->left = nullptr;

	//prrint out puzzle 
    cout << "ouput" << endl;
	outputPuzzle(b);
    cout << "checking" << endl;
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
        cout << "true" << endl;
		return true;
	}
	else {
        cout << "false" << endl;
		return false;
	}
}



#endif
#ifndef _8puzzle_h_included_
#define _8puzzle_h_included_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

struct block{ //  node with 4 children(4 directions)
    vector<char> board;
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
    int nodesExpanded; // number of nodes that have been expanded
    int queueNodes; // number of nodes currently in queue
   // tests if the current puzzle is solved
  bool solveCheck(vector<char>);
    public:
    eightpuzzle();
    void startGame();
    void outputPuzzle(block*);
    void FromOne(block*);
    void FromTwo(block*);
    void FromThree(block* );
    void FromFour(block*);
    void FromFive(block* );
    void FromSix(block* );
    void FromSeven(block*);
    void FromEight(block*);
    void FromNine(block*);
    void goUp(block*, vector<char>);
    void goDown(block*, vector<char>);
    void goLeft(block*, vector<char>);
    void goRight(block*, vector<char>);

};

//////////////////////////////////////////////////////////
// definitions temporary
//////////////////////////////////////////////////////////


#endif
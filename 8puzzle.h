#ifndef _8puzzle_h_included_
#define _8puzzle_h_included_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <queue> //priority_queue
using namespace std;

struct block{ //  node with 4 children(4 directions)
  vector<char> board; //vector of puzzle board
	block* up; // child that has the blank move up
	block* down; // child that has the blank move down
	block* left; // child that has the blank move left
	block* right; // child that has the blank move right
	block* parent; // keeps track of parent node
  int cost; //cost to reach node
  int heuristicVal; //heuristic value
};

class comparison{ // comparator to help with priority queue ordering
  public:
    bool operator()(block* b1, block* b2) const{
      return ((b1->cost + b1->heuristicVal) > (b2->cost + b2->heuristicVal) );
    }

};
class eightpuzzle{ 
    private: 
    block* root; //starting node
    block* goal; // goal state
    bool foundSolution; // marks if the goal state has been found or not
    int nodesExpanded; // number of nodes that have been expanded
    int queueNodes; // number of nodes currently in queue
   // tests if the curckrent puzzle is solved
    bool solveCheck(vector<char>);
    void checkQueue(); //updates queue count
    list<block*> path; //path of the solution
    vector<vector<char>> pastPositions; //list of previous puzzle configurations ( to keep track of duplicates)
    priority_queue<block*, vector<block*>, comparison> pQ; // priority queue
    vector<char> solution = {'1', '2', '3', '4', '5', '6', '7', '8', '0'}; // solved puzzle
    int calcManDist(vector <char>, unsigned);
    int choice; // algorithm choice
    int depth; //solution depth
    int xVal, yVal; //x and y values of current spot being examined
    int solxVal, solyVal; // x and y values of where it would be in the solution
    void setXY(unsigned); //set current x and y
    void setSolVal(char); // set solution x and y
    bool hasExisted(vector<char>); // check if certain configuration has existed before or not
    void search(block*); // search algorithm
    int findBlank(block*); // finds where the blank tile is
    void printPath(); // output path
    int findHeuristic(vector<char>); // calculate heuristic value
    int misplacedTiles(vector<char>); // calculate misplaced tiles heuristic
    int manhattanDist(vector<char>); // calculate manhattan distance heuristic
    void FromOne(block*); // move from 1 position, similar for followig functions
    void FromTwo(block*);
    void FromThree(block*);
    void FromFour(block*);
    void FromFive(block*);
    void FromSix(block*);
    void FromSeven(block*);
    void FromEight(block*);
    void FromNine(block*);
    void goUp(block*, vector<char>); // expand node for the up directon
    void goDown(block*, vector<char>);
    void goLeft(block*, vector<char>);
    void goRight(block*, vector<char>);
    void backtrack(block*); // reorder path
    public:
    eightpuzzle();
    void startGame(bool); // creates starter node
    void pickAlgo(int); // select algorithm
    void outputPuzzle(block*); // prints out puzzle 

};

//// 
#endif
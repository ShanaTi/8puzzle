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

	b->board = {'1', '2', '3', '4', '5', '6', '7', '0', '8'};

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

//check if a specific board position matches the solution
bool eightpuzzle::solveCheck(vector<char> board){
	vector<char> solution = {'1', '2', '3', '4', '5', '6', '7', '8', '0'};
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
//////////////////////
// using these numbers to represent positions where the blank could be
// minus one since vectors start at 0
// 1  2  3
// 4  5  6 
// 7  8  9
//////////////////////////////
void eightpuzzle::FromOne(block* cur){ // if the blank is in the 1s spot 
/*  can either go to the right or down*/ 
   vector<char> tempR = cur->board;
   vector<char> tempD = cur->board;
   swap(tempR.at(0), tempR.at(1)); //go right
   goRight(cur, tempR); //assign child to parent
   swap(tempD.at(0), tempD.at(3)); //go down
   goDown(cur, tempD);//assign child to parent
}

void eightpuzzle::FromTwo(block* cur){ // if the blank is in the 2s spot 
/* can either go to the left, right or down*/ 
   vector<char> tempR = cur->board;
   vector<char> tempL = cur->board;
   vector<char> tempD = cur->board;
   swap(tempR.at(1), tempR.at(2)); //go right
   goRight(cur, tempR); 
    swap(tempL.at(1), tempL.at(0)); //go left
   goLeft(cur, tempL); 
   swap(tempD.at(1), tempD.at(4)); //go down
   goDown(cur, tempD);
}

void eightpuzzle::FromThree(block* cur){ // if the blank is in the 3s spot 
/* can either go to the left or down*/ 
   vector<char> tempL = cur->board;
   vector<char> tempD = cur->board;
   swap(tempL.at(2), tempL.at(1)); //go left
   goLeft(cur, tempL); 
   swap(tempD.at(2), tempD.at(5)); //go down
   goDown(cur, tempD);
}

void eightpuzzle::FromFour(block* cur){ // if the blank is in the 4s spot 
/* can either go to the right, up or down*/ 
   vector<char> tempR = cur->board;
   vector<char> tempD = cur->board;
   vector<char> tempU = cur->board;
   swap(tempR.at(3), tempR.at(4)); //go right
   goRight(cur, tempR);
   swap(tempD.at(3), tempD.at(6)); //go down
   goDown(cur, tempD);
   swap(tempU.at(3), tempU.at(0)); //go up
   goUp(cur, tempU);
}

void eightpuzzle::FromFive(block* cur){ // if the blank is in the 5s spot 
/*can either go to the left, right or down*/ 
   vector<char> tempR = cur->board;
   vector<char> tempL = cur->board;
   vector<char> tempD = cur->board;
   vector<char> tempU = cur->board;
   swap(tempR.at(4), tempR.at(5)); //go right
   goRight(cur, tempR); 
    swap(tempL.at(4), tempL.at(3));//go left
   goLeft(cur, tempL); 
   swap(tempD.at(4), tempD.at(7)); //go down
   goDown(cur, tempD);
   swap(tempU.at(4), tempU.at(1)); //go up
   goUp(cur, tempU); 
}

void eightpuzzle::FromSix(block* cur){ // if the blank is in the 6s spot 
/*can either go to the left, up or down*/ 
   vector<char> tempL = cur->board;
   vector<char> tempD = cur->board;
   vector<char> tempU = cur->board;
   swap(tempL.at(5), tempL.at(4)); //go left
   goLeft(cur, tempL); 
   swap(tempD.at(5), tempD.at(8)); //go down
   goDown(cur, tempD);
    swap(tempU.at(5), tempU.at(2)); //go up
   goUp(cur, tempU);
}

void eightpuzzle::FromSeven(block* cur){ // if the blank is in the 7s spot 
/*can either go to the right or up*/ 
   vector<char> tempR = cur->board;
   vector<char> tempU = cur->board;
   swap(tempR.at(6), tempR.at(4)); //go right
   goRight(cur, tempR);
   swap(tempU.at(6), tempU.at(3)); //go up
   goUp(cur, tempU); 
}

void eightpuzzle::FromEight(block* cur){ // if the blank is in the 8s spot 
/* can either go to the left, right or down*/ 
   vector<char> tempR = cur->board;
   vector<char> tempL = cur->board;
   vector<char> tempU = cur->board;
   swap(tempR.at(7), tempR.at(8)); //go right
   goRight(cur, tempR);
    swap(tempL.at(7), tempL.at(6)); //go left
   goLeft(cur, tempL); 
   swap(tempU.at(7), tempU.at(4)); // go up
   goUp(cur, tempU);
}

void eightpuzzle::FromNine(block* cur){ // if the blank is in the 9s spot 
/* can either go to the left or up*/ 
   vector<char> tempL = cur->board;
   vector<char> tempU = cur->board;
   swap(tempL.at(8), tempL.at(7)); // go left
   goLeft(cur, tempL);
   swap(tempU.at(8), tempU.at(5)); // go up
   goUp(cur, tempU); 
}
//add child to tree
 void eightpuzzle::goUp(block* cur, vector<char> newBoard){
      block* newMove = new block;
      newMove->board = newBoard;
      cur->up = newMove;
      cur->up->parent = cur;
      nodesExpanded += 1; //new node added, so increase count of expanded nodes
 }

  void eightpuzzle::goDown(block* cur, vector<char> newBoard){
      block* newMove = new block;
      newMove->board = newBoard;
      cur->down = newMove;
      cur->down->parent = cur;
      nodesExpanded += 1;
 }

   void eightpuzzle::goLeft(block* cur, vector<char> newBoard){
      block* newMove = new block;
      newMove->board = newBoard;
      cur->left = newMove;
      cur->left->parent = cur;
      nodesExpanded += 1;
 }

    void eightpuzzle::goRight(block* cur, vector<char> newBoard){
      block* newMove = new block;
      newMove->board = newBoard;
      cur->right = newMove;
      cur->right->parent = cur;
      nodesExpanded += 1;
 }
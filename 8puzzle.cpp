#include "8puzzle.h"

eightpuzzle::eightpuzzle(){ //default constructor
	root = nullptr;
}
void eightpuzzle::startGame(bool create){
	block* b = new block;
	foundSolution = false; // initialize values
   nodesExpanded = 0;
   queueNodes = 0;

	//sample board
   if(!create){
      b->board = {'0', '7', '2', '4', '6', '1', '3', '5', '8'}; // curently set to depth 24
   }
   else {
      char tempVal; //temp holder for user input
      vector<char> temp; // temp evctor to hold user input
      cout << "Please input your puzzle (9 digits separated by a space)" << endl;
      for (unsigned i = 0; i < 9; i++){
         cin >> tempVal;
         temp.push_back(tempVal);
      }
      b->board = temp;
   }
	

	//initialize parent and children
	b->up = nullptr;
	b->down = nullptr;
	b->right = nullptr;
	b->left = nullptr;
	b->cost = 0; // current cost is 0
   b->parent = nullptr;
   b->cost = 0; // default cost to get to node is 0 (starting point)
   b->heuristicVal = 0; // set to 0 as default

   root = b;
   //add to list of past board configurations
   pastPositions.push_back(root->board);
   pQ.push(root); // ad to priority queue
	//print out puzzle 
	outputPuzzle(b);
	//solveCheck(b->board);
}


void eightpuzzle::pickAlgo(int Userchoice){ // sets algorithm choice
   if(Userchoice == 1 || Userchoice == 2 || Userchoice == 3){
      choice = Userchoice;
   }
   else {
      cout << "error" << endl;
      return;
   }
   if(root == nullptr){
      cout << "error" << endl;
      return;
   }
   else {
      search(root);
   }
}

void eightpuzzle::outputPuzzle(block* tempBlock){
	for(unsigned i = 0; i < 9; i++){ //output the puzzle line by line
			cout << tempBlock->board.at(i) << " ";
			if((i+1) % 3 == 0 ){ // start a new line every 3
				cout << endl;
			}
	}
   cout << endl;
}

//check if a specific board position matches the solution
bool eightpuzzle::solveCheck(vector<char> board){
	if(board == solution){
	//	cout << "true" << endl;
		return true;
	}
	else {
	//	cout << "false" << endl;
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
void eightpuzzle::FromOne(block* tempBlock){ // if the blank is in the 1s spot 
/*  can either go to the right or down*/ 
   vector<char> tempR = tempBlock->board;
   vector<char> tempD = tempBlock->board;
   swap(tempR.at(0), tempR.at(1)); //go right
   goRight(tempBlock, tempR); //assign child to parent
   swap(tempD.at(0), tempD.at(3)); //go down
   goDown(tempBlock, tempD);//assign child to parent
}

void eightpuzzle::FromTwo(block* tempBlock){ // if the blank is in the 2s spot 
/* can either go to the left, right or down*/ 
   vector<char> tempR = tempBlock->board;
   vector<char> tempL = tempBlock->board;
   vector<char> tempD = tempBlock->board;
   swap(tempR.at(1), tempR.at(2)); //go right
   goRight(tempBlock, tempR); 
    swap(tempL.at(1), tempL.at(0)); //go left
   goLeft(tempBlock, tempL); 
   swap(tempD.at(1), tempD.at(4)); //go down
   goDown(tempBlock, tempD);
}

void eightpuzzle::FromThree(block* tempBlock){ // if the blank is in the 3s spot 
/* can either go to the left or down*/ 
   vector<char> tempL = tempBlock->board;
   vector<char> tempD = tempBlock->board;
   swap(tempL.at(2), tempL.at(1)); //go left
   goLeft(tempBlock, tempL); 
   swap(tempD.at(2), tempD.at(5)); //go down
   goDown(tempBlock, tempD);
}

void eightpuzzle::FromFour(block* tempBlock){ // if the blank is in the 4s spot 
/* can either go to the right, up or down*/ 
   vector<char> tempR = tempBlock->board;
   vector<char> tempD = tempBlock->board;
   vector<char> tempU = tempBlock->board;
   swap(tempR.at(3), tempR.at(4)); //go right
   goRight(tempBlock, tempR);
   swap(tempD.at(3), tempD.at(6)); //go down
   goDown(tempBlock, tempD);
   swap(tempU.at(3), tempU.at(0)); //go up
   goUp(tempBlock, tempU);
}

void eightpuzzle::FromFive(block* tempBlock){ // if the blank is in the 5s spot 
/*can either go to the left, right or down*/ 
   vector<char> tempR = tempBlock->board;
   vector<char> tempL = tempBlock->board;
   vector<char> tempD = tempBlock->board;
   vector<char> tempU = tempBlock->board;
   swap(tempR.at(4), tempR.at(5)); //go right
   goRight(tempBlock, tempR); 
    swap(tempL.at(4), tempL.at(3));//go left
   goLeft(tempBlock, tempL); 
   swap(tempD.at(4), tempD.at(7)); //go down
   goDown(tempBlock, tempD);
   swap(tempU.at(4), tempU.at(1)); //go up
   goUp(tempBlock, tempU); 
}

void eightpuzzle::FromSix(block* tempBlock){ // if the blank is in the 6s spot 
/*can either go to the left, up or down*/ 
   vector<char> tempL = tempBlock->board;
   vector<char> tempD = tempBlock->board;
   vector<char> tempU = tempBlock->board;
   swap(tempL.at(5), tempL.at(4)); //go left
   goLeft(tempBlock, tempL); 
   swap(tempD.at(5), tempD.at(8)); //go down
   goDown(tempBlock, tempD);
    swap(tempU.at(5), tempU.at(2)); //go up
   goUp(tempBlock, tempU);
}

void eightpuzzle::FromSeven(block* tempBlock){ // if the blank is in the 7s spot 
/*can either go to the right or up*/ 
   vector<char> tempR = tempBlock->board;
   vector<char> tempU = tempBlock->board;
   swap(tempR.at(6), tempR.at(7)); //go right
   goRight(tempBlock, tempR);
   swap(tempU.at(6), tempU.at(3)); //go up
   goUp(tempBlock, tempU); 
}

void eightpuzzle::FromEight(block* tempBlock){ // if the blank is in the 8s spot 
/* can either go to the left, right or down*/ 
   vector<char> tempR = tempBlock->board;
   vector<char> tempL = tempBlock->board;
   vector<char> tempU = tempBlock->board;
   swap(tempR.at(7), tempR.at(8)); //go right
   goRight(tempBlock, tempR);
    swap(tempL.at(7), tempL.at(6)); //go left
   goLeft(tempBlock, tempL); 
   swap(tempU.at(7), tempU.at(4)); // go up
   goUp(tempBlock, tempU);
}

void eightpuzzle::FromNine(block* tempBlock){ // if the blank is in the 9s spot 
/* can either go to the left or up*/ 
   vector<char> tempL = tempBlock->board;
   vector<char> tempU = tempBlock->board;
   swap(tempL.at(8), tempL.at(7)); // go left
   goLeft(tempBlock, tempL);
   swap(tempU.at(8), tempU.at(5)); // go up
   goUp(tempBlock, tempU); 
}

//add child to tree
 void eightpuzzle::goUp(block* tempBlock, vector<char> newBoard){
      block* newMove = new block;

   if(foundSolution){ // if solution is found, don't need to expand anymore
         return;
   }
      if(hasExisted(newBoard)){ // if expanded in the past, don't need to do again
         tempBlock->up = nullptr;
         return;
      }
      else{ // transfer info into node & update values
         newMove->board = newBoard;
         newMove->cost = tempBlock->cost + 1;
         newMove->heuristicVal = findHeuristic(newBoard);
         tempBlock->up = newMove;
         tempBlock->up->parent = tempBlock;
         pastPositions.push_back(newBoard);
         pQ.push(tempBlock->up); 
         checkQueue();  // check if max queue sizes needs to update
         nodesExpanded += 1; //new node added, so increase count of expanded nodes 
      }
    
      if(solveCheck(newBoard)){ // if solution is found, set flag for goal
         foundSolution = true;
         goal = tempBlock->up;
         return;
      }
      
 }

  void eightpuzzle::goDown(block* tempBlock, vector<char> newBoard){
       block* newMove = new block;
      if(foundSolution){
         return;
      }
      if(hasExisted(newBoard)){
         tempBlock->down = nullptr;
         return;
      }
      else{
         newMove->board = newBoard;
         newMove->cost = tempBlock->cost + 1;
         newMove->heuristicVal = findHeuristic(newBoard);
         tempBlock->down = newMove;
         tempBlock->down->parent = tempBlock;
         pastPositions.push_back(newBoard);
         pQ.push(tempBlock->down);   
         checkQueue();
         nodesExpanded += 1;
      }
     
     
      if(solveCheck(newBoard)){
         foundSolution = true;
         goal = tempBlock->down;
         return;
      }
      
 }

   void eightpuzzle::goLeft(block* tempBlock, vector<char> newBoard){
      block* newMove = new block;
      if(foundSolution){
            return;
         }
      if(solveCheck(newBoard)){
            foundSolution = true;
            goal = tempBlock->left;
            return;
      }
      else {
         newMove->board = newBoard;
         newMove->cost = tempBlock->cost + 1;
         newMove->heuristicVal = findHeuristic(newBoard);
         tempBlock->left = newMove;
         tempBlock->left->parent = tempBlock;
         pastPositions.push_back(newBoard);
         pQ.push(tempBlock->left);   
         checkQueue();
         nodesExpanded += 1; 
      }
         if(hasExisted(newBoard)){
            tempBlock->left = nullptr;
            return;
         }

      
 }

    void eightpuzzle::goRight(block* tempBlock, vector<char> newBoard){
      block* newMove = new block;
      if(foundSolution){
            return;
         }
      if(hasExisted(newBoard)){
         tempBlock->right = nullptr;
         return;
      }
      else{
         newMove->board = newBoard;
         newMove->cost = tempBlock->cost + 1;
         newMove->heuristicVal = findHeuristic(newBoard);
         tempBlock->right = newMove;
         tempBlock->right->parent = tempBlock;
         pastPositions.push_back(newBoard);
         pQ.push(tempBlock->right);   
         checkQueue();
         nodesExpanded += 1; 
      } 
     
      if(solveCheck(newBoard)){
         foundSolution = true;
         goal = tempBlock->right;
         return;
      }
      return;
      
 }

 bool eightpuzzle::hasExisted(vector<char> board){ 
    //if certain configuration already exists, don't need to expand
    // search thru vector of past positions
    for(unsigned i = 0; i < pastPositions.size(); i++){
       if(board == pastPositions.at(i)){
          return true;
       }   
    }
    return false;
 }

 void eightpuzzle::search(block* tempBlock){ //main search algorithm
    if(pQ.empty()){
       cout << "Failure" << endl;
       return;
    }

    if(solveCheck(tempBlock->board)){ // set goal flag if solution is found
       foundSolution = true;
       goal = tempBlock;
    }
    else{
       pQ.pop();
    }

    int loc = findBlank(tempBlock); //find index of blank spot

    if(loc == 0){ // depending on where the blank is, go different directions
       FromOne(tempBlock);
    }
    else if (loc == 1){
       FromTwo(tempBlock);
    }
   else if (loc == 2){
       FromThree(tempBlock);
    }

    else if (loc == 3){
       FromFour(tempBlock);
    }

    else if (loc == 4){
       FromFive(tempBlock);
    }

    else if (loc == 5){
       FromSix(tempBlock);
    }

    else if (loc == 6){
       FromSeven(tempBlock);
    }

    else if (loc == 7){
       FromEight(tempBlock);
    }

    else if (loc == 8){
       FromNine(tempBlock);
    }
    else{
       cout << "Failure" << endl;
       return;
    }

   if(foundSolution){ // if solution found
      while(pQ.top() != goal){ //while node on top isn't the solution
         pQ.pop(); //remove from queue
      }
      outputPuzzle(pQ.top());
      backtrack(pQ.top());
   //  printPath();
   }
   else{
      if(!pQ.empty()){
         outputPuzzle(pQ.top());
         search(pQ.top());
      }
   }
}

 int eightpuzzle::findBlank(block* tempBlock){
    int blankLoc = 0;

    for(int i = 0; i < 9; i++){ //goes thru the vector to find where the blank is
       if(tempBlock->board.at(i) == '0'){
          blankLoc = i;
       }
    }
    return blankLoc;
 }

void eightpuzzle::printPath(){
   cout << "printing path" << endl;
   int pathsize = path.size();
   depth = pathsize;
   for(unsigned i = 0; i < pathsize; i++){ // similar to printing board
      	for(unsigned i = 0; i < 9; i++){ 
            cout << path.front()->board.at(i) << " ";
            if((i+1) % 3 == 0 ){
               cout << endl;
			}
         
	   }
      cout << endl;
      path.pop_front();
   }
   cout << "Depth: " << depth - 1 << endl;
   cout << "nodes expanded:" << nodesExpanded << endl;
   cout << "the maximum number of nodes in a queue at a time was " << queueNodes << endl;
 }

void eightpuzzle::backtrack(block* tempBlock){
   if (tempBlock == root){
      path.push_front(tempBlock);
      printPath();
   }
   else {
      path.push_front(tempBlock);
      backtrack(tempBlock->parent);
   }
}

void eightpuzzle::checkQueue(){
   if(pQ.size() > queueNodes){ // if queue count is outdated
      queueNodes = pQ.size(); //update the count
   }
}
 int eightpuzzle::findHeuristic(vector<char> board){
    //returns different values based on how the user wants to solve the problem
    if(choice == 1){ //ucs
       return 0; //heuristic for uniform cost search is 0
    }
    else if (choice == 2){
       return misplacedTiles(board);
    }
    else if (choice == 3){
       return manhattanDist(board);
    }
    return 0;  
 }


int eightpuzzle::misplacedTiles(vector<char> board){
   int heurVal = 0;
  
   for (unsigned i = 0; i < 9; i++){
      if(board.at(i) != solution.at(i) ){ //if it doesn't match the solution, it's in the wrong plce
         heurVal += 1;
      }
   }
   if(board.at(8) != '0') { // doesn't count the blank as a misplaced tile, 
   //so if blank is anywhere but the end, remove from count
      heurVal= heurVal - 1;
   }
   return heurVal;
}

int eightpuzzle::manhattanDist(vector<char> board){
   int heurVal = 0;
      for (unsigned i = 0; i < 9; i++){
      if(board.at(i) != solution.at(i) ){ //if it doesn't match the solution, it's in the wrong plce
         if(board.at(i) != '0'){
         heurVal += calcManDist(board, i);
         }
      }
   }
   return heurVal;
}
//////////////////////
// using these numbers to represent positions 
// minus one since vectors start at 0
// where x = 1 | 2 | 3
// 1  2  3 y = 1
// 4  5  6 y = 2
// 7  8  9 y = 3
//////////////////////////////
int eightpuzzle::calcManDist(vector<char> board, unsigned i){
   int dx, dy;
  setSolVal(board.at(i));
  setXY(i);
  dx = abs(xVal - solxVal);
  dy = abs(yVal - solyVal);
  return dx + dy;
}

void eightpuzzle::setSolVal(char v){ // sets values of x/y for solution (goal)
    if(v == '1'){
      solxVal = 1;
      solyVal = 1;
   }
   else if(v == '2'){
      solxVal = 2;
      solyVal = 1;
   }
   else if(v == '3'){
      solxVal = 3;
      solyVal = 1;
   }
   else if(v == '4'){
      solxVal = 1;
      solyVal = 2;
   }
   else if(v == '5'){
      solxVal = 2;
      solyVal = 2;
   }
   else if(v == '6'){
      solxVal = 3;
      solyVal = 2;
   }
   else if(v == '7'){
      solxVal = 1;
      solyVal = 3;
   }
   else if(v == '8'){
      solxVal = 2;
      solyVal = 3;
   }
   else if(v == '9'){
      solxVal = 3;
      solyVal = 3;
   }

}

void eightpuzzle::setXY(unsigned i){ // sets x/y values for current position
    if(i == 0){
      xVal = 1;
      yVal = 1;
   }
   else if (i == 1){
      xVal = 2;
      yVal = 1;
   }
   else if (i == 2){
      xVal = 3;
      yVal = 1;
   }
   else if (i == 3){
      xVal = 1;
      yVal = 2;
   }
   else if (i == 4){
      xVal = 2;
      yVal = 2;
   }
   else if (i == 5){
      xVal = 3;
      yVal = 2;
   }
   else if (i == 6){
      xVal = 1;
      yVal = 3;
   }
   else if (i == 7){
      xVal = 2;
      yVal = 3;
   }
   else if (i == 8){
      xVal = 3;
      yVal = 3;
   }
}
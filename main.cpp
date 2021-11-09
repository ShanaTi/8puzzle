#include "8puzzle.h"
int main(){

    int choice; // algorithm choice
    char uChoice; //user choice of puzzle type
    bool makeOwn; //  if user wants to input own 
    cout << "Do you want to see a demo with a sample puzzle board or create your own?" << endl;
    cout << "Type 'y' to input own board or 'n' to use the sample board" << endl;
    cin >> uChoice;
    if (uChoice == 'y' || makeOwn == 'Y'){
        makeOwn = true;
    }
    else {
        makeOwn = false;
    }
    eightpuzzle test;
    test.startGame(makeOwn);
    cout <<  "Pick an algorithm: " <<  endl << "'1' = uniform cost search" << endl;
    cout << "'2' = A* with misplaced tiles" << endl;
    cout << "'3' = A* with manhattan distance" << endl;
    cin >> choice;
    test.pickAlgo(choice);
    cout << "algorithm used " << choice << endl;
    return 0;
}

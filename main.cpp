#include <iostream>
#include "Board.h"

#define SIZE 101

int main()
{
    Board board(SIZE);
    //board.printBoard();

    for (unsigned i{}; i<10; ++i){
        board.simulatedAnnealing();
    }

    board.printShortestPath();

    return 0;
}

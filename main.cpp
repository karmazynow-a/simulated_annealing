#include <iostream>
#include "Board.h"

int main()
{
    Board board(20, true);

    //board.printShortestPath();

    for (unsigned i{}; i<10; ++i){
        board.simulatedAnnealing();
    }

    board.printShortestPath();

    return 0;
}

#include <iostream>
#include "Board.h"

int main()
{;
    Board board;
    //board.printShortestPath();

    for (unsigned i{}; i<10 && board.isTimeOk(); ++i){
        board.simulatedAnnealing();
    }

    board.printShortestPath();

    return 0;
}

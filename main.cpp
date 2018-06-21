#include <iostream>
#include "Board.h"

int main()
{;
    Board board;
    //board.printShortestPath();

    std::cout<<"Start"<<std::endl;
    while (board.isTimeOk()){
        board.simulatedAnnealing();
    }

    board.printShortestPath();

    return 0;
}

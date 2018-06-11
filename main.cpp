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

    std::vector<std::pair<int, int>> path = board.getShortestPath();
    std::cout<< "Length of path: " << d(path) <<std::endl;
    std::cout<< "Path: "<<std::endl;
/*
    for (auto el : path)
       std::cout<< el.first <<" "<< el.second <<std::endl;
*/
    return 0;
}

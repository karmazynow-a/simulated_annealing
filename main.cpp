#include <iostream>


#include "Board.h"
#include<time.h>


#define SIZE 50

int main()
{
    Board board(SIZE);
    //board.printBoard();
    std::vector<std::pair<int, int>> shortest_path = board.simulatedAnnealing();
    for (auto el : shortest_path)
       std::cout<< el.first <<" "<< el.second <<std::endl;

    shortest_path = board.simulatedAnnealing();
    for (auto el : shortest_path)
       std::cout<< el.first <<" "<< el.second <<std::endl;

    shortest_path = board.simulatedAnnealing();
    for (auto el : shortest_path)
       std::cout<< el.first <<" "<< el.second <<std::endl;

    return 0;
}

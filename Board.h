#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <time.h>

class Board{
public:
    Board (unsigned n = 20);

    void printBoard() const;

    void simulatedAnnealing();
    std::vector<std::pair<int, int>> getShortestPath() const {return m_shortestPath;}
private:
    void generateFile ();
    std::set<std::pair<int, int>> m_V;
    std::vector<std::pair<int, int>> m_shortestPath;
    unsigned m_n; //size
};

std::vector<std::pair<int, int>> randomize (std::vector<std::pair<int, int>> P);
double d(std::vector<std::pair<int, int>> P);

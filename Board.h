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

    std::vector<std::pair<int, int>> simulatedAnnealing();
private:
    void generateFile ();
    std::set<std::pair<int, int>> m_V;
    std::vector<std::pair<int, int>> shortest_path;
    unsigned m_n; //size
};

std::vector<std::pair<int, int>> randomize (std::vector<std::pair<int, int>> P);
double d(std::vector<std::pair<int, int>> P);
bool is_in (int a, int b, std::vector<std::pair<int, int>> P);

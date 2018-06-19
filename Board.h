#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <ctime>

struct Point{
    Point (int i=0, int a=0, int b=0) : m_a(a), m_b(b), m_i(i) {}
    friend bool operator<( const Point p1, const Point p2){
        return (p1.m_a < p2.m_a) || (!(p2.m_a < p1.m_a) && p1.m_b < p2.m_b);
    }
    int m_a, m_b, m_i;
};



class Board{
public:
    Board ();
    void simulatedAnnealing();
    std::vector<Point> getShortestPath() const {return m_shortestPath;}
    void printShortestPath() const;
    bool isTimeOk() const {return time_ok;}
private:
    std::vector<Point> m_V;
    std::vector<Point> m_shortestPath;
    unsigned m_n; //size
    std::clock_t m_timer;
    bool time_ok;
};

std::vector<Point> randomize (std::vector<Point> P, int max);
double d(std::vector<Point> P);

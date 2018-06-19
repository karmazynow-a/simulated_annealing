#include "Board.h"
#include <cmath>
#include <fstream>
#include <string>


#define MAX_IT 1000000

Board::Board (){
    std::ifstream file;

    m_timer=std::clock();
    time_ok = true;

    file.open("competition.txt");
    if(!file.is_open())
        std::cout<<"problem z plikiem";

    int i, a, b;
    while ( file >> i >> a >> b){
      m_V.emplace_back(Point (i, a, b));
      std::cout<<i<<" " <<a <<" "<<b<<std::endl;
    }
    file.close();

    for (auto el : m_V)
        m_shortestPath.emplace_back(el);

    m_n = m_shortestPath.size();
}


void Board::simulatedAnnealing(){
    std::vector<Point> P;
    P = m_shortestPath;

    for (int i {100}; i>=1; --i){
        //std::cout << "obecna najkrotsza scierzka ma dlugosc " << d(P) <<std::endl;
        double T = 0.001 * i * i;
        for (int it {}; it <= MAX_IT; ++it){
                if (clock() > m_timer + 1000*60*30){
                    time_ok = false;
                    goto EXIT;
                    }

                std::vector<Point> Pnew = randomize(P, m_n);
                if (d(Pnew) < d(P))
                    P = Pnew;
                else{
                    double x{(double) rand() / (RAND_MAX)};
                    if (x < exp((d(P) - d(Pnew))/T)){
                        P = Pnew;
                    }
                }
        }

    }

    //std::cout <<"długość starej ścieżki: "<<d(m_shortestPath)<< " i nowo obliczonej: "<<d(P)<<std::endl;
    EXIT:
    if (d(m_shortestPath) > d(P)){
        m_shortestPath.clear();
        for (int i{}; i < P.size(); ++i){
            m_shortestPath.emplace_back(Point(P[i].m_i, P[i].m_a, P[i].m_b));
        }
    }
}


std::vector<Point> randomize (std::vector<Point> P, int max){
    std::vector<Point> Pnew {P};
    int a, b, c, d;

    do{
        a = rand()%max;
        if (a == P.size()-1)
            b = 0;
        else
            b = a+1;

        c = rand()%max;
        if (c == P.size()-1)
            d = 0;
        else
            d = c+1;

    }while (a==c || b==d || a==d || b==c);

    auto tmp = Pnew[b];
    Pnew[b] = Pnew[d];
    Pnew[d] = tmp;

    return Pnew;
}

double d(std::vector<Point> P){
    double sum {};
    for (int i{}; i<P.size()-1; ++i){
        sum += sqrt(pow(P[i+1].m_a - P[i].m_a, 2) + pow(P[i+1].m_b - P[i].m_b, 2));
    }
    sum += sqrt(pow(P.back().m_a - P[0].m_a, 2) + pow(P.back().m_b - P[0].m_b, 2));
    return sum;
}

void Board::printShortestPath() const{
    std::cout<< "Length of path: " << d(m_shortestPath) <<std::endl;
    std::cout<< "Path: "<<std::endl;

    std::ofstream file("path.txt");
    file << "Len: " << d(m_shortestPath) <<std::endl;
    for (auto el : m_shortestPath)
       file << el.m_i << " " << el.m_a <<" "<< el.m_b <<std::endl;

    file.close();
}

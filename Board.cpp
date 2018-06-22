#include "Board.h"
#include <cmath>
#include <fstream>
#include <string>

#define MAX_IT 1000000

Board::Board () : m_timer (std::chrono::system_clock::now()), time_ok(true){
    std::ifstream file("competition.txt");

    if(!file.is_open())
        std::cout<<"problem z plikiem";

    int i, a, b;
    while ( file >> i >> a >> b){
      m_V.emplace_back(Point (i, a, b));
    }
    file.close();

    ++i;
    m_distances.resize(i);
    for (auto &el : m_distances)
        el.resize(i);

    for (auto el : m_V)
        m_shortestPath.emplace_back(el);

    for (auto el : m_V){
        for (auto o : m_V){
            m_distances[el.m_i][o.m_i] = sqrt(pow(el.m_a - o.m_a, 2) + pow(el.m_b - o.m_b, 2));
        }
    }

    m_n = m_shortestPath.size();
    std::cout<<"File loaded, elements: "<< m_n << std::endl;
}


void Board::simulatedAnnealing(){
    std::vector<Point> P {m_shortestPath};

    for (int i {100}; i>=1; --i){
        //std::cout << "obecna najkrotsza scierzka ma dlugosc " << d(P) <<std::endl;
        double T = 0.001 * i * i;
        for (int it {}; it <= MAX_IT; ++it){
                std::chrono::duration<double> period = std::chrono::system_clock::now() - m_timer;
                if (period > std::chrono::minutes(30) ){
                    std::cout << "Czas, który upłyną" << period.count() <<std::endl;
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

    EXIT:
    if (d(m_shortestPath) > d(P)){
        m_shortestPath.clear();
        for (int i{}; i < P.size(); ++i){
            m_shortestPath.emplace_back(Point(P[i].m_i, P[i].m_a, P[i].m_b));
        }
    }
    std::cout<<d(m_shortestPath)<<std::endl;
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

double Board::d(std::vector<Point> P){
    double sum {};
    for (int i{}; i<P.size()-1; ++i){
        sum += m_distances[P[i].m_i][P[i+1].m_i];
    }
    sum += m_distances[P.back().m_i][P[0].m_i];
    return sum;
}

void Board::printShortestPath(){
    std::cout<< "Length of path: " << d(m_shortestPath) <<std::endl;
    std::cout<< "Path: "<<std::endl;

    std::ofstream file("path.txt");
    file << "Len: " << d(m_shortestPath) <<std::endl;
    for (auto el : m_shortestPath)
       file << el.m_i << " " << el.m_a <<" "<< el.m_b <<std::endl;

    file.close();
}

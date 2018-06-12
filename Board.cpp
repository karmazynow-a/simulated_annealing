#include "Board.h"
#include <cmath>
#include <fstream>

#define MAX_IT 1000

Board::Board (unsigned n): m_n(n){
    std::ifstream file ("data.dat");

    if (!file.is_open()){
        generateFile();
        file.open("data.dat");
    }

    int i, a, b;
    while ( file >> i >> a >> b){
      m_V.emplace(std::make_pair(a, b));
      std::cout<<a <<" "<<b<<std::endl;
    }
    file.close();

    for (auto el : m_V)
        m_shortestPath.emplace_back(el);
}

void Board::printBoard() const{
        std::cout.width(1);
        for (int i{}; i<m_n+1; ++i)
            std::cout<<"--";
        std::cout<<std::endl;

        for (int i{}; i<m_n; ++i){
            std::cout<<"|";
            for (int j{}; j<m_n; ++j){
                if (m_V.find(std::make_pair(i,j))!= m_V.end())
                    std::cout<<1<<" ";
                else
                    std::cout<<0<<" ";
            }
            std::cout<<"|"<<std::endl;
        }

        for (int i{}; i<m_n+1; ++i)
            std::cout<<"--";
        std::cout<<std::endl;
    }

void Board::simulatedAnnealing(){
    std::vector<std::pair<int, int>> P;
    P = m_shortestPath;

    for (int i {100}; i>=1; --i){
        //std::cout << "obecna najkrotsza scierzka ma dlugosc " << d(P) <<std::endl;
        double T = 0.001 * i * i;
        for (int it {}; it <= MAX_IT; ++it){
                std::vector<std::pair<int, int>> Pnew = randomize(P);
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

    if (d(m_shortestPath) > d(P)){
        m_shortestPath.clear();
        for (int i{}; i < P.size(); ++i){
            m_shortestPath.emplace_back(std::make_pair(P[i].first, P[i].second));
        }
    }
}

std::vector<std::pair<int, int>> randomize (std::vector<std::pair<int, int>> P){
    std::vector<std::pair<int, int>> Pnew {P};
    int a, b, c, d;

    do{
        a = rand()%10;
        if (a == P.size()-1)
            b = 0;
        else
            b = a+1;

        c = rand()%10;
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

double d(std::vector<std::pair<int, int>> P){
    double sum {};
    for (int i{}; i<P.size()-1; ++i){
        sum += sqrt(pow(P[i+1].first - P[i].first, 2) + pow(P[i+1].second - P[i].second, 2));
    }
    sum += sqrt(pow(P.back().first - P[0].first, 2) + pow(P.back().second - P[0].second, 2));
    return sum;
}


void Board::generateFile (){
    std::ofstream file;
    file.open ("data.dat");

    std::set<std::pair<int, int>> data;
    srand(time(0));

    for (unsigned i{}; i<m_n; ){
        int a = rand()%m_n;
        int b = rand()%m_n;

        if (data.find(std::make_pair(a,b))== data.end()){
            data.emplace(std::make_pair(a,b));
            file << i << " " << a << " " << b <<std::endl;
            ++i;
        }
    }
    file.close();
}

void Board::printShortestPath() const{
    std::cout<< "Length of path: " << d(m_shortestPath) <<std::endl;
    std::cout<< "Path: "<<std::endl;
/*
    for (auto el : m_shortestPath)
       std::cout<< el.first <<" "<< el.second <<std::endl;
       */
}

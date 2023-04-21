#include<iostream>
#include<sstream>
#include <fstream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<string>
#include<iomanip>
#include"point.h"
#include"rangetreeFC.h"
#include <random>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
    vector<Point> origin;

    std::vector<uint16_t> rand_indices;

    for (uint16_t i = 0; i < 10000; i++)
        rand_indices.push_back(i);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(rand_indices.begin(), rand_indices.end(), std::default_random_engine(seed));

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> rand_point(0, 65535); // define the range

    for (int n = 0; n < 10000; ++n)
    {
        Point p;
        p.x = rand_point(gen);
        p.y = rand_point(gen);
        p.player_index = rand_indices[n];
        origin.emplace_back(p);
    }
    auto start = std::chrono::high_resolution_clock::now();
    rangetreeFC kradius(origin);
    kradius.buildtree();   //build rangetreeFC
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Building took: " << duration.count() << " microseconds" << endl;

    vector<Point> result;
    Point  from, to;
    int fromx, fromy, tox, toy;
    fromx = std::max(origin[5000].x-50000, 0);
    fromy = std::max(origin[5000].y-50000, 0);
    tox = std::min(origin[5000].x+50000, 65535);
    toy = std::min(origin[5000].y+50000, 65535);
    std::cout << "Original Point: " << origin[5000].x << " " << origin[5000].y << std::endl;
    from.x = fromx;
    from.y = fromy;
    to.x = tox;
    to.y = toy;
    auto start2 = std::chrono::high_resolution_clock::now();
    kradius.rangequery(from, to, result);
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    cout << "Range query took: " << duration2.count() << " microseconds" << endl;
    for (int i = 0; i < std::min(20, (int)result.size()); i++)
        std::cout << result[i].x << " " << result[i].y << " " << result[i].player_index << std::endl;
    std::cout << "Num points in range: " << (int)result.size() << std::endl;;

    return 0;
}

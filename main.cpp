#include <iostream>
#include <set>

#include "Game.h"

#define MAX_NUM 10000

using namespace std;

set<int> Tags = {
    10,       100,      500,      1000,     2000,      5000,
    10000,    20000,    50000,    100000,   1000000,   2000000,
    3000000,  4000000,  5000000,  6000000,  7000000,   8000000,
    9000000,  10000000, 20000000, 30000000, 40000000,  50000000,
    60000000, 70000000, 80000000, 90000000, 100000000
};

int main(){
    srand((unsigned)time(NULL));
    time_t begin;
    begin = clock();
    
    Game* game = new Game();
    game->init();

    game->reBegin();

    game->end();

    
    double ret = double(clock() - begin) / CLOCKS_PER_SEC;
    return 0;
}
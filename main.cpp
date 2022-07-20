#include <iostream>
#include <set>

#include "Game.h"

#define MAX_NUM 100000000

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
    long long int index = 0;
    bool flag = false;

    time_t begin;
    begin = clock();

    Game* game = new Game();

    while(index < MAX_NUM && !flag){
        game->begin();
        game->run(flag);
        game->reset();
        index++;

        if(Tags.count(index)){
            double ret = double(clock() - begin) / CLOCKS_PER_SEC;
            printf("                                                        \
                    循环 %-10lld 次程序执行时间为: %-10f 秒.\n",index,ret);
        }
        
    }

    game->end();
    game->~Game();

    double ret = double(clock() - begin) / CLOCKS_PER_SEC;
    printf("\n                                                             \
               循环 %-10d 次程序执行时间为: %-10f 秒.\n",index,ret);
    
    return 0;
}
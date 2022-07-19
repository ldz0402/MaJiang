#include <iostream>

#include "Game.h"

#define MAX_NUM 10000

using namespace std;

int main(){
    srand((unsigned)time(NULL));
    int index = 0;
    bool flag = false;

    time_t begin, end;
    begin = clock();

    time_t ends[100];
    long long ends_index = 0;
    int ten=1;

    Game* game = new Game();

    while(index < MAX_NUM && !flag){
        game->begin();
        game->run(flag);
        game->reset();
        index++;

        if((index+1)%ten == 0 && ends_index < 100){
            ends[ends_index] = clock();
            double ret = double(ends[ends_index] - begin) / CLOCKS_PER_SEC;
            printf("                                                        \
                    循环 %-10d 次程序执行时间为: %-10f 秒.\n",ten,ret);
            ends_index++;
            ten = ten<1000000? ten*10:ten+1000000;
        }
        
    }

    game->end();
    game->~Game();

    end = clock();
    double ret = double(end - begin) / CLOCKS_PER_SEC;
    printf("\n                                                             \
               循环 %-10d 次程序执行时间为: %-10f 秒.\n",index,ret);
    
    return 0;
}
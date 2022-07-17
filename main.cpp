#include <iostream>

#include "Game.h"

using namespace std;

void test(BaseBoard bd){
    bd.show();
}

void test(BaseBoard* bd){
    bd->show();
}

int main(){
    srand((unsigned)time(NULL));
    int index = 0;
    bool flag = false;

    time_t begin, end;
    begin = clock();

    time_t ends[100];
    long long ends_index = 0;
    int ten=1;

    while(index < 100000 && !flag){
        //printf("第%-8d次开局:\n",index);

        if((index+1)%ten == 0){
            ends[ends_index] = clock();

            double ret = double(ends[ends_index] - begin) / CLOCKS_PER_SEC;
            cout <<ten<<"次总运行时间为: " << ret << "秒!" << endl;

            ends_index++;
            ten = ten*10;
        }


        Game* game = new Game();
        game->begin();
        //game.show();
        game->run(flag);
        index++;
        game->~Game();
    }

    end = clock();
    double ret = double(end - begin) / CLOCKS_PER_SEC;
    cout <<index<< "次，总运行时间为: " << end - begin << "毫秒!" << endl;
    cout <<index<< "次，总运行时间为: " << ret << "秒!" << endl;

    printf("\n");
    return 0;
}
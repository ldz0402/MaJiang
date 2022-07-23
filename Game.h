#ifndef GAME_H_
#define GAME_H_

#include <set>
#include <map>
#include <vector>

#include "Player.h"

class Game{
    public:
        Game(bool Feng = true,bool Hua = false);
        // 初始化
        void init();

        // 获取当前所剩牌数
        int getBoardNums() const;

        // 发牌
        std::pair<std::set<NumBoard*>,std::set<StrBoard*>> getBoards(int num=1);

        // 游戏开始
        void begin();

        // 游戏进行
        void run(bool& hasWin);

        // 游戏结束
        void end();
        
        // 重新开始游戏
        void reBegin();

        // 展示当前玩家的牌
        void show() const;

        ~Game();

    private:
        // 4位玩家
        std::vector<Player*> Players;

        // 当前所剩牌数
        int BoardNums;

        std::vector<NumBoard*> NumBoards;
        std::vector<StrBoard*> StrBoards;
        void insert(NumBoard* numBoard);
        void insert(StrBoard* strBoard);
        
        // 当前庄家
        int player_index;

        // 游戏轮数
        int game_index;
};

#endif

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"

#include <set>
#include <vector>
#include <map>

class Player{
    public:
        Player(std::string name);
        
        // 获取玩家姓名
        std::string getName() const;

        // 摸牌
        void insert(NumBoard *numBoard);
        void insert(StrBoard *strBoard);

        // 打牌
        void remove();

        // 判断是否糊牌
        bool win(WinKind wk);
        

        // 返回玩家所有的牌，包括现有的和已经打出去的
        std::pair<std::set<NumBoard*>,std::set<StrBoard*>> getAllBoards() const;
        // 返回玩家所有打出去的牌
        std::pair<std::set<NumBoard*>,std::set<StrBoard*>> getDelBoards() const;
        // 返回玩家所拥有的牌
        std::pair<std::set<NumBoard*>,std::set<StrBoard*>> getOwnBoards() const;

        std::set<NumBoard*> getWanBoards() const;
        std::set<NumBoard*> getTiaoBoards() const;
        std::set<NumBoard*> getTongBoards() const;

        std::set<StrBoard*> getFengBoards() const;
        std::set<StrBoard*> getHuaBoards() const;

        // 清空玩家所有的牌
        void reset();

        // 展示玩家牌面
        void show() const;

        ~Player();
        
    private:
        std::string Name;

        std::vector<NumBoard*> Wans;
        std::vector<NumBoard*> Tiaos;
        std::vector<NumBoard*> Tongs;

        std::set<NumBoard*> DelNumBoards;

        std::vector<StrBoard*> Fengs;
        std::vector<StrBoard*> Huas;

        std::set<StrBoard*> DelStrBoards;

};

#endif
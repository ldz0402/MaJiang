#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"

#include <set>

static int SUM = 0;
static int MUT = 100000;

class Player{
    public:
        Player(std::string name);
        ~Player();
        void insert(BaseBoard *baseBoard);
        void remove();
        bool win(std::pair<WinKind,std::set<BaseBoard*>> win_format);
        std::string getName() const;
        void show() const;
        
    private:
        std::string Name;
        std::set<BaseBoard*> Boards;
        std::set<BaseBoard*> DelBoards;

};

#endif
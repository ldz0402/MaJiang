#ifndef GAME_H_
#define GAME_H_

#include <set>
#include <map>
#include <vector>

#include "Player.h"

class Game{
    public:
        Game(bool Feng = true,bool Hua = false);
        ~Game();
        int getBoardNums() const;
        void init_win_formats();
        void init_Players();

        void begin();
        void end();
        void run(bool& flag);
        void show() const;
        std::set<BaseBoard*> getBoards(int num=1);

    private:
        int BoardNums;
        std::vector<BaseBoard*> Boards;
        typedef std::pair<WinKind,std::set<BaseBoard*>> Win_Format;
        std::map<WinKind,std::set<BaseBoard*>>win_formats;
        std::vector<Player*> players;
        int player_index;
};

#endif

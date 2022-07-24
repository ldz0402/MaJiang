#include <iostream>

#include <stdlib.h>
#include "Game.h"

#include <cstdlib>
#include <ctime>

Game::Game(bool Feng,bool Hua){
    BoardNums = 0;

    for(int i=1;i<=9;++i){
      for (int j = 0; j < 4; ++j) {
        NumBoard* wanBoard = new NumBoard(BoardKind::Wan, i);
        NumBoard* tiaoBoard = new NumBoard(BoardKind::Tiao, i);
        NumBoard* tongBoard = new NumBoard(BoardKind::Tong, i);
        insert(wanBoard);
        insert(tiaoBoard);
        insert(tongBoard);
        BoardNums += 3;
      }
    }
    if(Feng){
        for(int j=0;j<4;++j){
            StrBoard* dongBoard = new StrBoard(BoardKind::Feng,"东");
            StrBoard* xiBoard = new StrBoard(BoardKind::Feng,"南");
            StrBoard* nanBoard = new StrBoard(BoardKind::Feng,"西");
            StrBoard* beiBoard = new StrBoard(BoardKind::Feng,"北");
            StrBoard* zhongBoard = new StrBoard(BoardKind::Feng,"中");
            StrBoard* faBoard = new StrBoard(BoardKind::Feng,"發");
            StrBoard* baiBoard = new StrBoard(BoardKind::Feng,"白");

            insert(dongBoard);
            insert(xiBoard);
            insert(nanBoard);
            insert(beiBoard);
            insert(zhongBoard);
            insert(faBoard);
            insert(baiBoard);
            
            BoardNums += 7;
        }
    }
    if(Hua){
        printf("I'm so sorry. It's not support now!\n");
    }
    
}

void Game::init(){
    printf("\
    欢迎来到李东焯精心的打造的《公平麻将》游戏:\n\
    您将在这里体会到最公平的游戏规则:\n\
    没有连胜:\n\
    没有连跪!\n\
    一切都靠运气和实力!\n"
    );

    std::string str;
    printf("接下来请输入4位玩家的的昵称:\n");

    printf("请输入一号玩家的名称:");
    while(true){    
        std::cin>>str;
        if(str.length() > 0 && str.length() < 7){
            Player* pe1 = new Player(str);
            Players.push_back(pe1);
            break;
        }else{
            printf("您输入的昵称过长或者过短，请重新输入：");
        }
    }
    printf("请输入二号玩家的名称:");
    while(true){    
        std::cin>>str;
        if(str.length() > 0 && str.length() < 7){
            Player* pe2 = new Player(str);
            Players.push_back(pe2);
            break;
        }else{
            printf("您输入的昵称过长或者过短，请重新输入：");
        }
    }
    printf("请输入三号玩家的名称:");
    while(true){    
        std::cin>>str;
        if(str.length() > 0 && str.length() < 7){
            Player* pe3 = new Player(str);
            Players.push_back(pe3);
            break;
        }else{
            printf("您输入的昵称过长或者过短，请重新输入：");
        }
    }
    printf("请输入四号玩家的名称:");
    while(true){    
        std::cin>>str;
        if(str.length() > 0 && str.length() < 7){
            Player* pe4 = new Player(str);
            Players.push_back(pe4);
            break;
        }else{
            printf("您输入的昵称过长或者过短，请重新输入：");
        }
    }
    
    printf("四位玩家:%-6s,%-6s,%-6s,%-6s已准备就位!\n",Players[0]->getName().c_str(),Players[1]->getName().c_str(),Players[2]->getName().c_str(),Players[3]->getName().c_str());
    printf("请开始享受游戏!\n");

}

int Game::getBoardNums() const{ return BoardNums; }

std::pair<std::set<NumBoard*>,std::set<StrBoard*>> Game::getBoards(int num){
    std::pair<std::set<NumBoard*>,std::set<StrBoard*>> res;

    if(BoardNums < num){
        return res;
    }

    for(int i=0;i<num;++i){
        int board_index = rand()%BoardNums;
        if (board_index<NumBoards.size())
        {
            res.first.insert(NumBoards[i]);
            NumBoards.erase(NumBoards.begin() + i);
        }else{
            res.second.insert(StrBoards[board_index - NumBoards.size()]);
            StrBoards.erase(StrBoards.begin() + board_index - NumBoards.size());
        }
        BoardNums--;
    }

    return res;
}

void Game::begin(){

    player_index = rand()%4;
    printf("-- 系统开始掷色子:");
    printf("%d--\n",player_index);
    
    printf("-- 开始发牌\n");

    printf("-- 从第%d位玩家:%-6s开始\n",player_index,Players[player_index]->getName().c_str());

    int loop = 1;
    while (loop <= 3) {
      for (int i = 0; i < Players.size(); ++i) {
        std::pair<std::set<NumBoard*>,std::set<StrBoard*>> res = getBoards(4);
        for(auto numBoard:res.first){
            Players[player_index]->insert(numBoard);
        }
        for(auto strBoard:res.second){
            Players[player_index]->insert(strBoard);
        }
        player_index = (player_index + 1) % Players.size();
      }
      loop++;
    }

    for (int i = 0; i < Players.size(); ++i) {
        std::pair<std::set<NumBoard*>,std::set<StrBoard*>> res = getBoards(1);
        for(auto numBoard:res.first){
            Players[player_index]->insert(numBoard);
        }
        for(auto strBoard:res.second){
            Players[player_index]->insert(strBoard);
        }
        player_index = (player_index + 1) % Players.size();
    }

    printf("-- 结束发牌\n");

}

void Game::run(bool& hasWin){
    printf("-- 开始摸牌\n");
    printf("-- 从第%d位玩家:%-6s开始\n",player_index,Players[player_index]->getName().c_str());
    int loop = 1;
    while(BoardNums>0){
      printf("-- 第%-2d轮摸牌\n",loop);
      for (int i = 0; i < Players.size(); ++i) {
        std::pair<std::set<NumBoard*>,std::set<StrBoard*>> res = getBoards(1);
        if(res.first.size()>0 || res.second.size()>0){
            system("clear");
            printf("\n\n-- %-6s摸牌\n",Players[player_index]->getName().c_str());
            for(auto numBoard:res.first){
                Players[player_index]->insert(numBoard);
            }
            for(auto strBoard:res.second){
                Players[player_index]->insert(strBoard);
            }

            if(Players[player_index]->win(WinKind::ShiSanYao)){
                hasWin = true;
                return;
            }else if(Players[player_index]->win()){
                hasWin = true;
                return;
            }

            Players[player_index]->remove();
        }else{
            break;
        }
        player_index = (player_index + 1) % Players.size();
      }

    }
    printf("本次游戏无人获胜!\n");
}

void Game::end(){

    show();

    printf("本轮游戏已结束,您是否继续游戏(y/n):\n");
    std::string str;
    std::cin>>str;
    if(str!="y"){
        printf("退出游戏\n");
    }else{
        reBegin();
    }

}

void Game::reBegin(){
    // 回收玩家所有的牌
    for(int i=0;i<Players.size();++i){
        auto boards = Players[i]->getAllBoards();
        for(auto board:boards.first){
            NumBoards.push_back(board);
            BoardNums++;
        }
        for(auto board:boards.second){
            StrBoards.push_back(board);
            BoardNums++;
        }
        Players[i]->reset();
    }

    begin();
    bool hasWin=false;
    run(hasWin);
    if(hasWin){
        printf("\n\n玩家%-6s获胜!\n\n",Players[player_index]->getName().c_str());
    }

}

void Game::show() const{
    for(auto player:Players){
        player->show();
    }
}

Game::~Game(){
    for(auto player:Players){
        delete player;
    }
    for(auto board:NumBoards){
        delete board;
    }
    for(auto board:StrBoards){
        delete board;
    }
    Players.clear();
    NumBoards.clear();
    StrBoards.clear();
}

void Game::insert(NumBoard* numBoard){
    NumBoards.push_back(numBoard);
}
void Game::insert(StrBoard* strBoard){
    StrBoards.push_back(strBoard);
}



















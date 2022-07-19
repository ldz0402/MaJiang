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
        Boards.push_back(wanBoard);
        Boards.push_back(tongBoard);
        Boards.push_back(tiaoBoard);
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

            Boards.push_back(dongBoard);
            Boards.push_back(xiBoard);
            Boards.push_back(nanBoard);
            Boards.push_back(beiBoard);
            Boards.push_back(zhongBoard);
            Boards.push_back(faBoard);
            Boards.push_back(baiBoard);
            
            BoardNums += 7;
        }
    }
    if(Hua){
        printf("I'm so sorry. It's not support now!\n");
    }

    init_win_formats();

    init_Players();

    
}

Game::~Game(){
    for(auto player:players){
        player->~Player();
    }
    for(auto bb:Boards){
        delete bb;
    }
    for(auto pair:win_formats){
        for(auto bb:pair.second){
            delete bb;
        }
    }
    win_formats.clear();
    Boards.clear();
    players.clear();
}

int Game::getBoardNums() const{
    return BoardNums;
}

void Game::init_win_formats(){
    Win_Format wf;
    wf.first = WinKind::ShiSanYao;

    std::set<BaseBoard*> format;
    NumBoard* n1 = new NumBoard(BoardKind::Wan,1);
    NumBoard* n2 = new NumBoard(BoardKind::Wan,9);
    NumBoard* n3 = new NumBoard(BoardKind::Tiao,1);
    NumBoard* n4 = new NumBoard(BoardKind::Tiao,9);
    NumBoard* n5 = new NumBoard(BoardKind::Tong,1);
    NumBoard* n6 = new NumBoard(BoardKind::Tong,9);

    StrBoard* n7 = new StrBoard(BoardKind::Feng,"东");
    StrBoard* n8 = new StrBoard(BoardKind::Feng,"南");
    StrBoard* n9 = new StrBoard(BoardKind::Feng,"西");
    StrBoard* n10 = new StrBoard(BoardKind::Feng,"北");
    StrBoard* n11 = new StrBoard(BoardKind::Feng,"中");
    StrBoard* n12 = new StrBoard(BoardKind::Feng,"發");
    StrBoard* n13 = new StrBoard(BoardKind::Feng,"白");

    format.insert(n1);
    format.insert(n2);
    format.insert(n3);
    format.insert(n4);
    format.insert(n5);
    format.insert(n6);
    format.insert(n7);
    format.insert(n8);
    format.insert(n9);
    format.insert(n10);
    format.insert(n11);
    format.insert(n12);
    format.insert(n13);

    wf.second=format;

    win_formats.insert(wf);

    
    
}

void Game::init_Players(){
    Player* zhangsan = new Player("张三");
    Player* lisi = new Player("李四");
    Player* wangwu = new Player("王五");
    Player* zhaoliu = new Player("赵六");
    
    players.push_back(zhangsan);
    players.push_back(lisi);
    players.push_back(wangwu);
    players.push_back(zhaoliu);

    
    player_index = rand()%4;

}

void Game::begin(){
    //printf("开始发牌,每人4张……\n");
    //printf("从第%d位玩家:%s开始发牌\n",player_index,players[player_index]->getName().c_str());

    int loop = 1;
    while (loop <= 3) {
      //printf("第%d轮发牌……\n", loop);
      for (int i = 0; i < players.size(); ++i) {
        //printf("给  %-5s 发牌……\n", players[player_index]->getName().c_str());
        std::set<BaseBoard *> res = getBoards(4);
        for (BaseBoard *child : res) {
          this->players[player_index]->insert(child);
        }
        player_index = (player_index + 1) % players.size();
      }
      loop++;
    }

    //printf("开始发牌,每人1张……\n");
    for(int i=0;i<players.size();++i){
        //printf("给  %-5s 发牌……\n",players[player_index]->getName().c_str());
        std::set<BaseBoard*> res = getBoards(1);
        for(BaseBoard* child:res){
            this->players[player_index]->insert(child);
        }
        player_index = (player_index+1)%players.size();
    }



    //printf("发牌结束\n");

}

void Game::end(){
    printf("游戏结束！\n");
}

void Game::run(bool& flag){
    //printf("从第%d位玩家:%s开始摸牌\n",player_index,players[player_index]->getName().c_str());
    std::set<BaseBoard*> boards = this->getBoards(1);
    this->players[player_index]->insert(*boards.begin());

    if(players[player_index]->win(*win_formats.begin())){
        printf("天胡 十三幺！！！\n");
        flag = true;
    }else{
        flag = false;
    }
    player_index = (player_index + 1)%players.size();

}

std::set<BaseBoard*> Game::getBoards(int num){
    std::set<BaseBoard*> res;
    for(int i=0;i<num;++i){
        int board_index = rand()%BoardNums;

        if (board_index < BoardNums) {
          res.insert(Boards[board_index]);
          Boards.erase(Boards.begin() + board_index);
          BoardNums--;
        }
    }
    return res;
}

void Game::reset(){
    for(auto player:players){
        auto boards = player->getBoards();
        for(auto board:boards){
            this->Boards.push_back(board);
            this->BoardNums++;
        }
        player->reset();
    }
}

void Game::show() const{
    for(auto player:players){
        player->show();
    }
}


















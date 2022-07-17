#include "Player.h"

#include <set>

Player::Player(std::string name):Name(name){}
Player::~Player(){
    for(BaseBoard* bb:Boards){
        delete bb;
    }
    for(BaseBoard* bb:DelBoards){
        delete bb;
    }
    Boards.clear();
    DelBoards.clear();
}


void Player::insert(BaseBoard* baseBoard){
    Boards.insert(baseBoard);
}

void Player::remove(){
    // 暂时随便打一张牌出去
    if (Boards.size() > 0) {
      DelBoards.insert(*Boards.begin());
      Boards.erase(Boards.begin());
    }else{
        printf("I'm so sorry! You don't have any board!\n");
    }
}

bool Player::win(std::pair<WinKind,std::set<BaseBoard*>> win_format){
    bool flag = false;
    switch (win_format.first)
    {
    case WinKind::ShiSanYao:
        {
            // 计算数量
            int sum = 14;
            int sum_cp = 0;
            // 计算乘积
            int mut = 2;
            int mut_cp = 1;

            int num[14]={0};
            int i=0;
            for(BaseBoard* child:win_format.second){
                try{
                  if (i > 13) {
                    throw i;
                  }
                  //printf("目标牌：");
                  //child->show();
                  //printf("\n");

                  for (BaseBoard* cd : Boards) {
                    //printf("我的牌：");
                    //cd->show();
                    if (child->getKind() == cd->getKind()) {
                    
                      if(auto str1 = dynamic_cast<StrBoard*>(cd)){
                        if(auto str2 = dynamic_cast<StrBoard*>(child)){
                            if(*str1 == *str2){
                                num[i]++;
                                //printf("匹配成功！\n");
                            }else{
                                //printf("匹配失败！\n");
                            }
                        }
                      }

                      if(auto num1 = dynamic_cast<NumBoard*>(cd)){
                        if(auto num2 = dynamic_cast<NumBoard*>(child)){
                            if(*num1 == *num2){
                                num[i]++;
                                //printf("匹配成功！\n");
                            }else{
                                //printf("匹配失败！\n");
                            }
                        }
                      }


                      
                      
                    }else{
                        //printf("匹配失败！\n");
                    }
                  }

                  if(num[i]!=0){
                    sum_cp += num[i];
                    mut_cp *= num[i];
                  }
                  ++i;
                }catch(int num){
                    printf("You have too many boards! You can't win by ShiSanYao!\n");
                }
            }
            if(sum==sum_cp&&mut==mut_cp) flag = true;

            if (sum_cp >= SUM && mut_cp <= MUT)
            {
                show();
                SUM = sum_cp;
                MUT = mut_cp < 2 ? 2 : mut_cp;
                printf("共接到%-2d/14张十三幺的牌,累乘结果为%-3d\n\n",sum_cp,mut_cp);
            }
            

        }
        break;
    
    default:
        printf("I'm so sorry! I can't judge whether you win by other type!\n");
        break;
    }
    return flag;
}

std::string Player::getName() const{
    return Name;
}

void Player::show() const{
    printf("%-5s:",getName().c_str());
    for(BaseBoard* board:Boards){
        board->show();
    }    
    printf("\n");
}
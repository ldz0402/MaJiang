#include "Player.h"

#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>


Player::Player(std::string name):Name(name){ }

std::string Player::getName() const{
    return Name;
}

bool compNum(const NumBoard* b1,const NumBoard* b2){
    return b1->getNum() < b2->getNum();
}
bool compStr(const StrBoard* b1,const StrBoard* b2){
    return b1->getName() < b2->getName();
}

void Player::insert(NumBoard *numBoard){
    switch (numBoard->getKind()) {
        case BoardKind::Wan:
            Wans.push_back(numBoard);
            sort(Wans.begin(),Wans.end(),compNum);
            break;
        case BoardKind::Tiao:
            Tiaos.push_back(numBoard);
            sort(Tiaos.begin(),Tiaos.end(),compNum);
            break;
        case BoardKind::Tong:
            Tongs.push_back(numBoard);
            sort(Tongs.begin(),Tongs.end(),compNum);
            break;
        default:
            break;
    }
}

void Player::insert(StrBoard *strBoard){
    switch (strBoard->getKind()){
        case BoardKind::Feng:
            Fengs.push_back(strBoard);
            sort(Fengs.begin(),Fengs.end(),compStr);
            break;
        case BoardKind::Hua:
            Huas.push_back(strBoard);
            sort(Huas.begin(),Huas.end(),compStr);
            break;
        default:
            break;
    }

}

static std::string getReplacedString(int strSize,int index){
    std::string res = std::to_string(index);
    
    int space = strSize - res.size();

    for(int i=0;i<space;++i){
        res = res + " ";
    }

    return res;
}

void Player::remove(){
    // 玩家选一张牌打出去
    printf("-- %-6s打牌\n",getName().c_str());
    std::string str = "";
    int four = Wans.size() + Tiaos.size() + Tongs.size();
    int three = Fengs.size() + Huas.size();
    int k=1;
    for(int i=0;i<four;++i){
        str = str + getReplacedString(4,k);
        k++;
    }
    for(int i=0;i<three;++i){
        str = str + getReplacedString(3,k);
        k++;
    }
    show();
    printf("             %s\n",str.c_str());

    printf("请选择你要打的牌:");
    int index;
    std::cin>>index;
    while(index<=0 || index > Wans.size()+Tiaos.size()+Tongs.size()+Fengs.size()){
        printf("没有第%-2d张牌!,请重新选择:",index);
        std::cin>>index;
    }

    if(index <= Wans.size()){
        int num = index;
        int i=1;
        for(auto wan:Wans){
            if(i==num){
                DelNumBoards.insert(wan);
                Wans.erase(Wans.begin()+i-1);
                break;
            }
            ++i;
        }
    }else if(index - Wans.size() <= Tiaos.size()){
        int num = index - Wans.size();
        int i=1;
        for(auto tiao:Tiaos){
            if(i==num){
                DelNumBoards.insert(tiao);
                Tiaos.erase(Tiaos.begin()+i-1);
                break;
            }
            ++i;
        }
        
    }else if(index - Wans.size() -Tiaos.size() <= Tongs.size()){
        int num = index - Wans.size() -Tiaos.size();
        int i=1;
        for(auto tong:Tongs){
            if(i==num){
                DelNumBoards.insert(tong);
                Tongs.erase(Tongs.begin()+i-1);
                break;
            }
            ++i;
        }

    }else if(index - Wans.size() - Tiaos.size() - Tongs.size() <= Fengs.size()){
        int num = index - Wans.size() - Tiaos.size() - Tongs.size();
        int i=1;
        for(auto feng:Fengs){
            if(i==num){
                DelStrBoards.insert(feng);
                Fengs.erase(Fengs.begin()+i-1);
                break;
            }
            ++i;
        }
    }

    show();
}

bool Player::win(WinKind wk){
    bool flag = false;
    switch (wk) {
        case WinKind::ShiSanYao:
            {
                int nums[13] = {0};
                for(auto wan:Wans){
                    if(wan->getNum()==1){
                        nums[0]++;
                    }else if(wan->getNum()==9){
                        nums[1]++;
                    }
                }
                for(auto tiao:Tiaos){
                    if(tiao->getNum()==1){
                        nums[2]++;
                    }else if(tiao->getNum()==9){
                        nums[3]++;
                    }
                }
                for(auto tong:Tongs){
                    if(tong->getNum()==1){
                        nums[4]++;
                    }else if(tong->getNum()==9){
                        nums[5]++;
                    }
                }
                for(auto feng:Fengs){
                    if(feng->getName()=="东"){
                        nums[6]++;
                    }else if (feng->getName()=="南"){
                        nums[7]++;
                    }else if (feng->getName()=="西"){
                        nums[8]++;
                    }else if (feng->getName()=="北"){
                        nums[9]++;
                    }else if (feng->getName()=="中"){
                        nums[10]++;
                    }else if (feng->getName()=="發"){
                        nums[11]++;
                    }else if (feng->getName()=="白"){
                        nums[12]++;
                    }
                }
                int sum = 0, mut = 1;
                for(int num:nums){
                    sum +=num;
                    mut *=num;
                }
                if(sum == 14 && mut == 2){
                    flag = true;
                }
            }
            break;
        default:
            printf("I'm so sorry! I can't judge whether you win by other type!\n");
            break;
    }
    return flag;
}

static bool isFormat(std::vector<int> vec){
    if(vec.size() == 0){
        return true;
    }else if(vec.size() < 3 || vec.size() % 3 != 0){
        return false;
    }

    bool res = false;

    // vec[0] 位于 AAA型
    if(vec[0] == vec[1] && vec[1] == vec[2]){
        std::vector<int> left(vec.begin()+3,vec.end());
        if(isFormat(left)){
            res = true;
        }
    }
    
    
    // vec[0] 位于 ABC型
    std::vector<int> left;
    int i=0,j=0;
    for(int k=1;k<vec.size();++k){
        if(vec[k]==vec[0]+1){
            i=k;
        }
        if(vec[k]==vec[0]+2){
            j=k;
        }
    }
    if(i!=0 && j!=0){
        std::vector<int> left;
        for(int k=1;k<vec.size();++k){
            if(k==i || k==j){
                continue;
            }
            left.push_back(vec[k]);
        }
        if(isFormat(left)){
            res = true;
        }
    }


    return res;
}

bool Player::win(){
    bool res = false;
    // 当前牌，用int表示
    std::vector<int> nums;
    for(auto board:Wans){
        nums.push_back(board->getNum());
    }
    for(auto board:Tiaos){
        nums.push_back(board->getNum()+10);
    }
    for(auto board:Tongs){
        nums.push_back(board->getNum()+20);
    }
    
    std::map<std::string,int> fengToInt = {
        {"东",1000},{"西",2000},
        {"南",3000},{"北",4000},
        {"中",5000},{"發",6000},
        {"白",7000}
        };

    for(auto board:Fengs){
        nums.push_back(fengToInt[board->getName()]);
    }

    sort(nums.begin(),nums.end());

    // 取走nums中成对的将
    for(int i=0;i<nums.size()-1;++i){
        if(nums[i]==nums[i+1]){
            // 取走将后剩下的牌
            std::vector<int> left;
            for(int j=0;j<nums.size();++j){
                if(j==i||j==i+1){
                    continue;
                }else{
                    left.push_back(nums[j]);
                }
            }

            // 判断left能否满足 m*AAA + n*ABC
            if(isFormat(left)){
                res = true;
                break;
            }
        }

    }

    return res;
}


std::pair<std::set<NumBoard*>,std::set<StrBoard*>> Player::getAllBoards() const{
    std::pair<std::set<NumBoard*>,std::set<StrBoard*>> res;

    for(auto num:getDelBoards().first){
        res.first.insert(num);
    }
    for(auto str:getDelBoards().second){
        res.second.insert(str);
    }
    for(auto num:getOwnBoards().first){
        res.first.insert(num);
    }
    for(auto str:getOwnBoards().second){
        res.second.insert(str);
    }

    return res;
}

std::pair<std::set<NumBoard*>,std::set<StrBoard*>> Player::getDelBoards() const{
    std::pair<std::set<NumBoard*>,std::set<StrBoard*>> res;
    for(auto num:DelNumBoards){
        res.first.insert(num);
    }
    for(auto str:DelStrBoards){
        res.second.insert(str);
    }
    return res;
}

std::pair<std::set<NumBoard*>,std::set<StrBoard*>> Player::getOwnBoards() const{
    std::pair<std::set<NumBoard*>,std::set<StrBoard*>> res;
    for(auto wan:Wans){
        res.first.insert(wan);
    }
    for(auto tiao:Tiaos){
        res.first.insert(tiao);
    }
    for(auto tong:Tongs){
        res.first.insert(tong);
    }

    for(auto feng:Fengs){
        res.second.insert(feng);
    }
    for(auto hua:Huas){
        res.second.insert(hua);
    }
    return res;
}



std::set<NumBoard*> Player::getWanBoards() const{ 
    std::set<NumBoard*> res;
    for(auto wan:Wans){
        res.insert(wan);
    }
    return res;
}
std::set<NumBoard*> Player::getTiaoBoards() const{ 
    std::set<NumBoard*> res;
    for(auto tiao:Tiaos){
        res.insert(tiao);
    }
    return res;
}
std::set<NumBoard*> Player::getTongBoards() const{ 
    std::set<NumBoard*> res;
    for(auto tong:Tongs){
        res.insert(tong);
    }
    return res;
}

std::set<StrBoard*> Player::getFengBoards() const{ 
    std::set<StrBoard*> res;
    for(auto feng:Fengs){
        res.insert(feng);
    }
    return res;
}
std::set<StrBoard*> Player::getHuaBoards() const{ 
    std::set<StrBoard*> res;
    for(auto hua:Huas){
        res.insert(hua);
    }
    return res;
}
void Player::reset(){
    Wans.clear();
    Tiaos.clear();
    Tongs.clear();
    DelNumBoards.clear();

    Fengs.clear();
    Huas.clear();
    DelStrBoards.clear();
}

void Player::show() const{
    printf("玩家：%-6s:",this->getName().c_str());
    for(auto wan:Wans){
        wan->show();
    }
    for(auto tiao:Tiaos){
        tiao->show();
    }
    for(auto tong:Tongs){
        tong->show();
    }
    for(auto feng:Fengs){
        feng->show();
    }
    for(auto hua:Huas){
        hua->show();
    }

    printf("\n");
}

Player::~Player(){
    for(auto wan:Wans){
        delete wan;
    }
    for(auto tiao:Tiaos){
        delete tiao;
    }
    for(auto tong:Tongs){
        delete tong;
    }
    for(auto num:DelNumBoards){
        delete num;
    }

    for(auto feng:Fengs){
        delete feng;
    }
    for(auto hua:Huas){
        delete hua;
    }
    for(auto str:DelStrBoards){
        delete str;
    }
    
    Wans.clear();
    Tiaos.clear();
    Tongs.clear();
    DelNumBoards.clear();

    Fengs.clear();
    Huas.clear();
    DelStrBoards.clear();

}


#include <iostream>

#include "Board.h"

using namespace std;

BaseBoard::BaseBoard():Kind(BoardKind::unknown){ }
BaseBoard::BaseBoard(BoardKind kind):Kind(kind){ }

BoardKind BaseBoard::getKind() const{ return Kind; }

bool BaseBoard::operator==(const BaseBoard& baseBoard) const{
    return this->getKind() == baseBoard.getKind();
}
bool BaseBoard::operator<(const BaseBoard& baseBoard) const{
    return this->getKind() < baseBoard.getKind();
}

void BaseBoard::show() {
  switch (getKind()) {
  case BoardKind::Feng:
    printf("风 ");
    break;
  case BoardKind::Hua:
    printf("花 ");
    break;
  case BoardKind::Tiao:
    printf("条 ");
    break;
  case BoardKind::Wan:
    printf("万 ");
    break;
  case BoardKind::Tong:
    printf("筒 ");
    break;
  default:
    printf("unknown BaseBoard type ");
    break;
  }
}

NumBoard::NumBoard():BaseBoard(),Num(0){};
NumBoard::NumBoard(BoardKind kind,int num):BaseBoard(kind),Num(num){ }

void NumBoard::show() {
  switch (getKind()) {
  case BoardKind::Tiao:
    printf("%d条 ",getNum());
    break;
  case BoardKind::Wan:
    printf("%d万 ",getNum());
    break;
  case BoardKind::Tong:
    printf("%d筒 ",getNum());
    break;
  default:
    printf("unknown NumBoard type ");
    break;
  }
}

bool NumBoard::operator==(const NumBoard& numBoard) const{
    return getKind() == numBoard.getKind() &&
     getNum() == numBoard.getNum();
}
bool NumBoard::operator<(const NumBoard& numBoard) const{
    if(getKind() == numBoard.getKind()){
      return getNum() < numBoard.getNum();
    }
    return getKind() < numBoard.getKind();
}
bool NumBoard::operator<(const StrBoard& strBoard) const{
    return true;
}

int NumBoard::getNum() const{
    return Num;
}

StrBoard::StrBoard():BaseBoard(),Name(""){}
StrBoard::StrBoard(BoardKind boardkind,std::string name):BaseBoard(boardkind),Name(name){}

void StrBoard::show() {
  printf("%s ",getName().c_str());
}

bool StrBoard::operator==(const StrBoard& strBoard) const{
    return getName() == strBoard.getName() &&
        getKind() == strBoard.getKind();
}
bool StrBoard::operator<(const StrBoard& strBoard) const{
  if (getKind() == strBoard.getKind()) {
    return getName() < strBoard.getName();
  }
  return getKind() < strBoard.getKind();
}
bool StrBoard::operator<(const NumBoard& numBoard) const{
  return false;
}

std::string StrBoard::getName() const{
    return Name;
}




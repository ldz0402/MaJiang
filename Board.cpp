#include <iostream>

#include "Board.h"

using namespace std;

BaseBoard::BaseBoard(BoardKind kind):Kind(kind){ }

BoardKind BaseBoard::getKind() const{ return this->Kind; }

bool BaseBoard::operator==(const BaseBoard& baseBoard) const{
    return this->getKind() == baseBoard.getKind();
}

bool BaseBoard::operator<(const BaseBoard& baseBoard) const{
    return this->getKind() < baseBoard.getKind();
}

void BaseBoard::show() {
  switch (this->getKind()) {
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

NumBoard::NumBoard(BoardKind kind,int num):BaseBoard(kind),Num(num){ }

void NumBoard::show() {
  switch (this->getKind()) {
    case BoardKind::Tiao:
      printf("%d条 ",this->getNum());
      break;
    case BoardKind::Wan:
      printf("%d万 ",this->getNum());
      break;
    case BoardKind::Tong:
      printf("%d筒 ",this->getNum());
      break;
    default:
      printf("unknown NumBoard type ");
      break;
    }
}

bool NumBoard::operator==(const NumBoard& numBoard) const{
    return this->getKind() == numBoard.getKind() && this->getNum() == numBoard.getNum();
}

bool NumBoard::operator<(const NumBoard& numBoard) const{
    if(this->getKind() == numBoard.getKind()){
      return this->getNum() < numBoard.getNum();
    }
    return this->getKind() < numBoard.getKind();
}

bool NumBoard::operator<(const StrBoard& strBoard) const{
    return true;
}

int NumBoard::getNum() const{ return this->Num; }

StrBoard::StrBoard(BoardKind boardkind,std::string name):BaseBoard(boardkind),Name(name){ }

void StrBoard::show() {
  printf("%s ",this->getName().c_str());
}

bool StrBoard::operator==(const StrBoard& strBoard) const{
    return this->getName() == strBoard.getName() && this->getKind() == strBoard.getKind();
}

bool StrBoard::operator<(const StrBoard& strBoard) const{
  if (this->getKind() == strBoard.getKind()) {
    return this->getName() < strBoard.getName();
  }
  return getKind() < strBoard.getKind();
}

bool StrBoard::operator<(const NumBoard& numBoard) const{
  return false;
}

std::string StrBoard::getName() const{ return this->Name; }




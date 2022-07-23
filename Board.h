#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>

enum class BoardKind{
    Unknown = 0,
    Wan,
    Tong,
    Tiao,
    Feng,
    Hua
};

enum class WinKind{
    Unknow = 0,
    Normal,
    ShiSanYao
};

class NumBoard;
class StrBoard;


class BaseBoard{
    public:
        BaseBoard(BoardKind kind);
        virtual void show();
        BoardKind getKind() const;
        virtual bool operator==(const BaseBoard& baseBoard) const;
        virtual bool operator<(const BaseBoard& baseBoard) const;

    private:
        BoardKind Kind;
        
};

class NumBoard:public BaseBoard{
    public:
        NumBoard(BoardKind boardKind,int num);
        virtual void show() override;
        bool operator==(const NumBoard& numBoard) const;
        bool operator<(const NumBoard& numBoard) const;
        bool operator<(const StrBoard& strBoard) const;
        int getNum() const;
    private:
        int Num;

};

class StrBoard:public BaseBoard{
    public:
        StrBoard(BoardKind boardkind,std::string name);
        virtual void show() override;
        bool operator==(const StrBoard& strBoard) const;
        bool operator<(const StrBoard& strBoard) const;
        bool operator<(const NumBoard& numBoard) const;
        std::string getName() const;
    private:
        std::string Name;
};

#endif
#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>

enum BoardKind{
    unknown = 0,
    Wan,
    Tong,
    Tiao,
    Feng,
    Hua
};

enum WinKind{
    null = 0,
    normal,
    ShiSanYao
};

class BaseBoard{
    public:
        BaseBoard();
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
        NumBoard();
        NumBoard(BoardKind boardKind,int num);
        virtual void show() override;
        bool operator==(const NumBoard& numBoard) const;
        bool operator<(const NumBoard& numBoard) const;
        //bool operator<(const StrBoard& strBoard) const;
        int getNum() const;
    private:
        int Num;

};

class StrBoard:public BaseBoard{
    public:
        StrBoard();
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
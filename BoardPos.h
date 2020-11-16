#ifndef BOARDPOS_H
#define BOARDPOS_H

#include <QVariant>

#define BOARD_SIZE 8

struct BoardPos
{
    enum Column { A = 1, B, C, D, E, F, G, H };

    BoardPos()
        : BoardPos(A, 0) {}
    BoardPos(Column a_column, int a_row)
        : column(a_column)
        , row(a_row) {}

    Column column;
    int row;
};

Q_DECLARE_METATYPE(BoardPos)


#endif // BOARDPOS_H

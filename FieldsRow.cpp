#include "FieldsRow.h"

#include <QDebug>

#include "Field.h"

FieldsRow::FieldsRow(ChessBoard *a_chessBoard/* = nullptr*/, int a_row)
    : QObject(a_chessBoard)
    , m_row(a_row)
{
    for (int i = 1; i <= BOARD_SIZE; i++)
    {
        m_fields.append(new Field(a_chessBoard, BoardPos(BoardPos::Column(i), a_row)));
    }
}

Field *FieldsRow::fieldAt(BoardPos::Column a_column)
{
    if (a_column >= m_fields.size() + 1)
    {
        qWarning() << "wrong column " << a_column;
        return nullptr;
    }

    return m_fields.at(a_column - 1);
}

int FieldsRow::row() const
{
    return m_row;
}

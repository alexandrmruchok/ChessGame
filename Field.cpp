#include "Field.h"

#include "ChessBoard.h"

Field::Field(ChessBoard *a_chessBoard, BoardPos a_pos)
    : QObject(a_chessBoard)
    , m_chessBoard(a_chessBoard)
    , m_boardPos(a_pos)
{

}

ChessBoard *Field::chessBoard() const
{
    return m_chessBoard;
}

void Field::setChessBoard(ChessBoard *chessBoard)
{
    m_chessBoard = chessBoard;
}

bool Field::isEmpty() const
{
    return !this->figure();
}

AbstractFigure *Field::figure() const
{
    return m_figure;
}

void Field::setFigure(AbstractFigure *a_figure)
{
    if (m_figure == a_figure)
        return;

    if (!this->isEmpty())
        emit this->figureBeaten(m_figure);
    m_figure = a_figure;
    emit this->figureChanged(a_figure);
}

Field *Field::translatedField( int a_colDiff, int a_rowDiff)
{
    int newColumnNumber = this->columnNumber() + a_colDiff;
    int newRow = this->row() + a_rowDiff;

    if ((newColumnNumber < 1 || newColumnNumber > BOARD_SIZE) ||
        (newRow < 1 || newRow > BOARD_SIZE))
    {
        return nullptr;
    }

    auto newPos = BoardPos(BoardPos::Column(newColumnNumber), newRow);

    return this->chessBoard()->fieldAt(newPos);
}

BoardPos Field::pos() const
{
    return m_boardPos;
}

int Field::columnNumber() const
{
    return this->pos().column;
}

int Field::row() const
{
    return this->pos().row;
}

bool Field::available() const
{
    return m_availableToMove;
}

void Field::setAvailable(bool a_availableToMove)
{
    if (m_availableToMove == a_availableToMove)
        return;

    m_availableToMove = a_availableToMove;
    emit this->availabilityChanged(a_availableToMove);
}

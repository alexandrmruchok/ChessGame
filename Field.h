#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <QObject>

#include "BoardPos.h"
class ChessBoard;
class AbstractFigure;

class Field : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AbstractFigure* figure READ figure WRITE setFigure NOTIFY figureChanged)
    Q_PROPERTY(bool available READ available WRITE setAvailable NOTIFY availabilityChanged)
    Q_PROPERTY(BoardPos pos READ pos CONSTANT)
    Q_PROPERTY(int column READ columnNumber CONSTANT)
    Q_PROPERTY(int row READ row CONSTANT)


public:
    explicit Field(ChessBoard *a_chessBoard, BoardPos a_pos);

    ChessBoard *chessBoard() const;
    void setChessBoard(ChessBoard *chessBoard);

    bool isEmpty() const;
    AbstractFigure *figure() const;
    void setFigure(AbstractFigure *a_figure);

    Field* translatedField(int a_colDiff, int a_rowDiff);

    BoardPos pos() const;

    int columnNumber() const;
    int row() const;

    bool available() const;
    void setAvailable(bool a_availableToMove);

signals:
    void figureChanged(AbstractFigure* m_figure);
    void availabilityChanged(bool a_available);
    void figureBeaten(AbstractFigure* m_figure);

private:
    ChessBoard* m_chessBoard;
    BoardPos m_boardPos;
    AbstractFigure* m_figure = nullptr;
    bool m_availableToMove = false;

};

#endif // BOARDFIELD_H

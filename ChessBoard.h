#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVector>
#include <QVariant>

#include "AbstractFigure.h"


class FieldsRow;
class Field;
struct BoardPos;

class ChessBoard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant model READ createModel CONSTANT)
    Q_PROPERTY(AbstractFigure* selectedFigure READ selectedFigure WRITE setSelectedFigure NOTIFY selectedFigureChanged)
public:

    explicit ChessBoard(QObject *parent = nullptr);

    QVariant createModel() const;

    Field* fieldAt(BoardPos a_boardPos);
    FieldsRow* fieldRowAt(int a_index);
    void arrangeFigures();

    void addFigure(BoardPos a_pos, AbstractFigure* a_figure);

    QList<AbstractFigure*> figures();
    QList<AbstractFigure*> figures(Color a_color);
    AbstractFigure* kingFigure(Color a_color);

    Color currentColor() const;
    void setCurrentColor(const Color &a_currentColor);

    bool fieldCanBeBeatenBy(Field* a_field, Color a_color);
    bool figureCanBeBeaten(const AbstractFigure& a_figure);

    AbstractFigure *selectedFigure() const;
    void setSelectedFigure(AbstractFigure *a_selectedFigure);

    void clearMovableFigures();
    void updateMovableFigures();

    void clearAvailableFields();
    void updateAvailableFields();

    void selectRandomFigure();
    void selectRandomField();

signals:
    Q_INVOKABLE void stalemate();
    Q_INVOKABLE void checkmate(Color a_winner);
    void figureSelected(AbstractFigure* a_figure);
    void selectedFigureChanged(AbstractFigure* a_figure);

private:
    void removeBeatenByColorFields(QList<Field*>& a_fieldsList, Color a_color);
    void removeAllFigures();

    QVector<FieldsRow*> m_fieldsRows;
    QMultiMap<Color, AbstractFigure*> m_figures;
    QList<AbstractFigure*> m_movableFigures;
    QList<Field*> m_availableFields;

    AbstractFigure* m_selectedFigure = nullptr;
    Color m_currentColor = Color::LIGHT;
};



#endif // CHESSBOARD_H

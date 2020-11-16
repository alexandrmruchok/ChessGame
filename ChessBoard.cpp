#include "ChessBoard.h"

#include "FieldsRow.h"
#include <QList>
#include <QDebug>

#include "figures.h"

ChessBoard::ChessBoard(QObject *parent)
    : QObject(parent)
{
    for (int i = BOARD_SIZE; i >= 1; i--)
    {
        auto boardFieldRow = new FieldsRow(this, i);
        m_fieldsRows.append(boardFieldRow);
    }
}

QVariant ChessBoard::createModel() const
{
    qDebug() << "Model created";

    QList<QObject*> objModel;
    for (auto curFieldRow: m_fieldsRows)
        objModel.append(curFieldRow);

    return QVariant::fromValue(objModel);
}

Field *ChessBoard::fieldAt(BoardPos a_boardPos)
{
    auto fieldRow = this->fieldRowAt(a_boardPos.row);
    if (!fieldRow)
        return nullptr;

    return fieldRow->fieldAt(a_boardPos.column);
}

FieldsRow *ChessBoard::fieldRowAt(int a_index)
{
    if (a_index < 1 || a_index >= m_fieldsRows.size() + 1)
    {
        qWarning() << "wrong index " << a_index;
        return nullptr;
    }

    return m_fieldsRows.at(BOARD_SIZE - a_index);
}

void ChessBoard::arrangeFigures()
{
    this->removeAllFigures();
    this->setCurrentColor(Color::LIGHT);

    for (int column = BoardPos::Column::A; column <= BoardPos::Column::H; column ++)
    {
        BoardPos currentPos(BoardPos::Column(column), 2);
        this->addFigure(currentPos, new PawnFigure(Color::LIGHT, this));
        currentPos.row = 7;
        this->addFigure(currentPos, new PawnFigure(Color::DARK, this));
    }

    this->addFigure(BoardPos(BoardPos::Column::A, 1), new RookFigure  (Color::LIGHT, this));
    this->addFigure(BoardPos(BoardPos::Column::B, 1), new KnightFigure(Color::LIGHT, this));
    this->addFigure(BoardPos(BoardPos::Column::C, 1), new BishopFigure(Color::LIGHT, this));
    this->addFigure(BoardPos(BoardPos::Column::D, 1), new QueenFigure (Color::LIGHT, this));
    this->addFigure(BoardPos(BoardPos::Column::F, 1), new BishopFigure(Color::LIGHT, this));
    this->addFigure(BoardPos(BoardPos::Column::G, 1), new KnightFigure(Color::LIGHT, this));
    this->addFigure(BoardPos(BoardPos::Column::H, 1), new RookFigure  (Color::LIGHT, this));
    this->addFigure(BoardPos(BoardPos::Column::E, 1), new KingFigure  (Color::LIGHT, this));


    this->addFigure(BoardPos(BoardPos::Column::A, 8), new RookFigure  (Color::DARK, this));
    this->addFigure(BoardPos(BoardPos::Column::B, 8), new KnightFigure(Color::DARK, this));
    this->addFigure(BoardPos(BoardPos::Column::C, 8), new BishopFigure(Color::DARK, this));
    this->addFigure(BoardPos(BoardPos::Column::D, 8), new QueenFigure (Color::DARK, this));
    this->addFigure(BoardPos(BoardPos::Column::F, 8), new BishopFigure(Color::DARK, this));
    this->addFigure(BoardPos(BoardPos::Column::G, 8), new KnightFigure(Color::DARK, this));
    this->addFigure(BoardPos(BoardPos::Column::H, 8), new RookFigure  (Color::DARK, this));
    this->addFigure(BoardPos(BoardPos::Column::E, 8), new KingFigure  (Color::DARK, this));
}

void ChessBoard::addFigure(BoardPos a_pos, AbstractFigure *a_figure)
{
    if (!a_figure)
    {
        qWarning() << "wrong figure";
        return;
    }

    connect(a_figure, &AbstractFigure::selected, [this, a_figure]{
        this->setSelectedFigure(a_figure);
    });
    connect(a_figure, &AbstractFigure::wasBeaten, [this, a_figure]{
        m_figures.remove(a_figure->color(), a_figure);
        a_figure->deleteLater();
    });


    m_figures.insertMulti(a_figure->color(), a_figure);
    a_figure->move(fieldAt(a_pos));
}

QList<AbstractFigure *> ChessBoard::figures()
{
    return m_figures.values();
}

QList<AbstractFigure *> ChessBoard::figures(Color a_color)
{
    return m_figures.values(a_color);
}

AbstractFigure *ChessBoard::kingFigure(Color a_color)
{
    return m_figures.value(a_color);
}

Color ChessBoard::currentColor() const
{
    return m_currentColor;
}

void ChessBoard::setCurrentColor(const Color &a_currentColor)
{
    m_currentColor = a_currentColor;
}

bool ChessBoard::fieldCanBeBeatenBy(Field* a_field, Color a_color)
{
    for (auto curFigure: this->figures(a_color))
    {
        if (curFigure->canBeat(a_field))
            return true;
    }
    return false;
}

bool ChessBoard::figureCanBeBeaten(const AbstractFigure &a_figure)
{
    auto enemyColor = a_figure.color() == Color::LIGHT ? Color::DARK : Color::LIGHT;
    return this->fieldCanBeBeatenBy(a_figure.field(), enemyColor);
}

AbstractFigure *ChessBoard::selectedFigure() const
{
    return m_selectedFigure;
}

void ChessBoard::setSelectedFigure(AbstractFigure *a_selectedFigure)
{
    if (m_selectedFigure == a_selectedFigure)
        return;

    if (m_selectedFigure)
        m_selectedFigure->deselect();

    m_selectedFigure = a_selectedFigure;
    emit this->selectedFigureChanged(a_selectedFigure);
    if (a_selectedFigure)
        emit this->figureSelected(a_selectedFigure);

    this->clearMovableFigures();
}

void ChessBoard::clearMovableFigures()
{
    for (auto curFigure: m_movableFigures)
    {
        curFigure->setCanBeSelected(false);
    }
    m_movableFigures.clear();
}

void ChessBoard::updateMovableFigures()
{
    this->clearMovableFigures();

    //If king can be beaten can't move another figures (Chack)
    AbstractFigure* king = this->kingFigure(this->currentColor());

    auto availableKingFields = king->availableMovingFields();

    this->removeBeatenByColorFields(availableKingFields, ::opposite(this->currentColor()));
    bool kingCanMove = !availableKingFields.isEmpty();

    if (kingCanMove)
    {
        m_movableFigures.append(king);
        king->setCanBeSelected(true);
    }

    if (this->figureCanBeBeaten(*king))
    {
        ///TODO: Checking coverage beating line
        if (!kingCanMove)
            emit this->checkmate(this->currentColor() == Color::LIGHT ? Color::LIGHT : Color::DARK);

        return;
    }

    auto allFigures = this->figures(this->currentColor());
    allFigures.pop_front(); //King (index = 0) is already checked

    for (auto curFigure: allFigures)
    {
        if (curFigure->hasAvailableMovingFields())
        {
            m_movableFigures.append(curFigure);
            curFigure->setCanBeSelected(true);
        }
    }

    if (m_movableFigures.empty())
        emit this->stalemate();
}

void ChessBoard::clearAvailableFields()
{
    for (auto curField: m_availableFields)
    {
        curField->setAvailable(false);
    }
    m_availableFields.clear();
}

void ChessBoard::updateAvailableFields()
{
    qDebug() << "updating Available Fields";

    this->clearAvailableFields();

    if (!this->selectedFigure())
        return;

    auto fiealdsList = this->selectedFigure()->availableMovingFields();
    if (this->selectedFigure() == this->kingFigure(this->currentColor()))
        this->removeBeatenByColorFields(fiealdsList, ::opposite(this->currentColor()));
    m_availableFields.append(fiealdsList);

    for (auto curField: m_availableFields)
        curField->setAvailable(true);
}

void ChessBoard::selectRandomFigure()
{
    auto figuresCount = m_movableFigures.count();
    if (figuresCount == 0)
        return;

    m_movableFigures.at(qrand() % figuresCount)->select();
}

void ChessBoard::selectRandomField()
{
    if (!this->selectedFigure())
        return;

    auto fieldsCount = m_availableFields.count();
    if (fieldsCount == 0)
        return;

    Field* selectedField = m_availableFields.at(qrand() % fieldsCount);

    this->selectedFigure()->move(selectedField);
}

void ChessBoard::removeBeatenByColorFields(QList<Field *> &a_fieldsList, Color a_color)
{
    //remove beaten fields:
    QMutableListIterator<Field*> it(a_fieldsList);
    while (it.hasNext())
    {
        if (this->fieldCanBeBeatenBy(it.next(), a_color))
            it.remove();
    }
}

void ChessBoard::removeAllFigures()
{
    for (auto currentFigure: m_figures)
    {
        currentFigure->field()->setFigure(nullptr); //will be destroyed
    }
    m_figures.clear();
}

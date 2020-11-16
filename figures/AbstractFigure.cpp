#include "AbstractFigure.h"
#include <QDebug>

AbstractFigure::AbstractFigure(Color a_color, QObject *a_parent)
    : QObject(a_parent)
    , m_color(a_color)
{

}

bool AbstractFigure::isSelected() const
{
    return m_selected;
}

void AbstractFigure::select()
{
    this->setSelected(true);
}

void AbstractFigure::deselect()
{
    this->setSelected(false);
}

void AbstractFigure::setSelected(bool a_selected)
{
    qDebug() << "AbstractFigure::setSelected";
    if (m_selected == a_selected)
        return;

    m_selected = a_selected;
    emit this->selectedChanged(a_selected);
    if (a_selected)
        emit this->selected();
}

void AbstractFigure::setCanBeSelected(bool a_canBeSelected)
{
    if (m_canBeSelected == a_canBeSelected)
        return;

    m_canBeSelected = a_canBeSelected;
    emit this->canBeSelectedChanged(a_canBeSelected);
}

bool AbstractFigure::canBeSelected() const
{
    return m_canBeSelected;
}

bool AbstractFigure::hasAvailableMovingFields()
{
    for (QList<QPair<int,int>> checkingList: this->checkingAvailableFieldsLists())
    {
        if (checkingList.empty())
            continue;

        Field *checkingField = this->field()->translatedField(checkingList.first().first, checkingList.first().second);

        if (!checkingField)
            continue;

        auto fieldFigure = checkingField->figure();
        if (!fieldFigure || fieldFigure->color() != this->color())
            return true;
    }
    return false;
}

QList<Field *> AbstractFigure::availableMovingFields()
{
    QList<Field *> availableFieldsList;
    for (QList<QPair<int,int>> checkingList: this->checkingAvailableFieldsLists())
    {
        for(QPair<int,int> posDiff: checkingList)
        {
            Field *checkingField = this->field()->translatedField(posDiff.first, posDiff.second);

            if (!checkingField)
                break;

            if  (!checkingField->isEmpty())
            {
                if  (checkingField->figure()->color() != this->color())
                    availableFieldsList.append(checkingField);
                break;
            }
            availableFieldsList.append(checkingField);
        }
    }
    return availableFieldsList;
}

bool AbstractFigure::canBeat(Field *a_field)
{
    if (!a_field)
        return false;

    return this->availableMovingFields().contains(a_field);
}

bool AbstractFigure::canMoveTo(const Field &a_field)
{
    Q_UNUSED(a_field)
///TODO

    return false;
}

void AbstractFigure::move(Field *a_destField)
{
    if (this->field())
        this->field()->setFigure(nullptr);

    this->setField(a_destField);

    if (a_destField)
    {
        if (!a_destField->isEmpty())
            emit a_destField->figure()->wasBeaten();

        a_destField->setFigure(this);
    }
}

Field *AbstractFigure::field() const
{
    return m_boardField;
}

void AbstractFigure::setField(Field *a_boardField)
{
    m_boardField = a_boardField;
}

Color AbstractFigure::color() const
{
    return m_color;
}

Color opposite(Color a_color)
{
    return a_color == Color::LIGHT ? Color::DARK : Color::LIGHT;
}

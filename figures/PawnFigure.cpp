#include "PawnFigure.h"

#include "AbstractStyle.h"

PawnFigure::PawnFigure(Color a_color, QObject *a_parent /*= nullptr*/)
    :AbstractFigure(a_color, a_parent)
{}

bool PawnFigure::hasAvailableMovingFields()
{
    int rowDiff = this->color() == Color::LIGHT ? +1 : -1;

    Field* checkingField;

    int maxStep = (this->color() == Color::LIGHT && this->field()->row() == 2) || (this->color() == Color::DARK && this->field()->row() == 7) ? 2 : 1;

    for (int i = 1; i <= maxStep; i++)
    {
        checkingField = this->field()->translatedField(0, rowDiff * i);

        if (!checkingField)
        {
            if (i == 1)
                return false;
            break;
        }

        if (!checkingField->isEmpty())
            break;

        return true;
    }

    ///checking for Beat
    for (int colDiff: {-1, 1})
    {
        checkingField = this->field()->translatedField(colDiff, rowDiff);

        if (!checkingField)
            continue;

        if (!checkingField->isEmpty() && checkingField->figure()->color() != this->color())
            return true;
    }

    return false;
}

QList<Field *> PawnFigure::availableMovingFields()
{
    QList<Field *> availableFields;

    int rowDiff = this->color() == Color::LIGHT ? +1 : -1;

    Field* checkingField;

    int maxStep = (this->color() == Color::LIGHT && this->field()->row() == 2) || (this->color() == Color::DARK && this->field()->row() == 7) ? 2 : 1;

    for (int i = 1; i <= maxStep; i++)
    {
        checkingField = this->field()->translatedField(0, rowDiff * i);

        if (!checkingField)
        {
            if (i == 1)
                return availableFields;
            continue;
        }

        if (checkingField->figure())
            break;

        availableFields.append(checkingField);
    }

    ///checking for Beat
    for (int colDif: {-1, 1})
    {
        checkingField = this->field()->translatedField(colDif, rowDiff);

        if (!checkingField)
            continue;

        auto enemyFigure = checkingField->figure();
        if (enemyFigure && enemyFigure->color() != this->color())
            availableFields.append(checkingField);
    }
    return availableFields;
}

QVariant PawnFigure::image(const AbstractStyle &a_style) const
{
    return this->color() == Color::LIGHT ? a_style.pawnImage_light(): a_style.pawnImage_dark();
}

bool PawnFigure::canBeat(Field *a_field)
{
    if (!a_field)
        return false;

    int a;
    if (a_field->row() == 7)
        a = 2+2;

    int rowDiff = this->color() == Color::LIGHT ? +1 : -1;
    int curColDiff = a_field->columnNumber() - this->field()->columnNumber();

    if ((a_field->row() - this->field()->row()) == rowDiff && (curColDiff == -1 || curColDiff == 1))
        return true;

    return false;
}

#include "KnightFigure.h"

#include "AbstractStyle.h"

KnightFigure::KnightFigure(Color a_color, QObject *a_parent /*= nullptr*/)
    :AbstractFigure(a_color, a_parent)
{}

QVariant KnightFigure::image(const AbstractStyle &a_style) const
{
    return this->color() == Color::LIGHT ? a_style.knightImage_light(): a_style.knightImage_dark();
}

QList<QList<QPair<int, int> > > KnightFigure::checkingAvailableFieldsLists()
{
    return {{{-1, 2}}, {{1, 2}}, {{2, 1}}, {{2, -1}}, {{1, -2}}, {{-1, -2}}, {{-2, -1}}, {{-2, 1}}};
}

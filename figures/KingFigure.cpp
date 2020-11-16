#include "KingFigure.h"

#include "AbstractStyle.h"

KingFigure::KingFigure(Color a_color, QObject *a_parent /*= nullptr*/)
    :AbstractFigure(a_color, a_parent)
{}


QVariant KingFigure::image(const AbstractStyle &a_style) const
{
    return this->color() == Color::LIGHT ? a_style.kingImage_light(): a_style.kingImage_dark();
}


QList<QList<QPair<int, int> > > KingFigure::checkingAvailableFieldsLists()
{
    return {{{-1, -1}}, {{-1, 0}}, {{-1, 1}}, {{0, -1}}, {{0, 0}}, {{0,1}}, {{1, -1}}, {{1, 0}}, {{1, 1}}};
}

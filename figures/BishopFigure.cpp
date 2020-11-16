#include "BishopFigure.h"

#include "AbstractStyle.h"

BishopFigure::BishopFigure(Color a_color, QObject *a_parent /*= nullptr*/)
    :AbstractFigure(a_color, a_parent)
{}


QVariant BishopFigure::image(const AbstractStyle &a_style) const
{
    return this->color() == Color::LIGHT ? a_style.bishopImage_light(): a_style.bishopImage_dark();
}

QList<QList<QPair<int, int> > > BishopFigure::checkingAvailableFieldsLists()
{
    return {
        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
        {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
        {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
        {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}}
    };
}

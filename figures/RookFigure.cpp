#include "RookFigure.h"

#include "AbstractStyle.h"

RookFigure::RookFigure(Color a_color, QObject *a_parent /*= nullptr*/)
    :AbstractFigure(a_color, a_parent)
{}

QVariant RookFigure::image(const AbstractStyle &a_style) const
{
    return this->color() == Color::LIGHT ? a_style.rookImage_light(): a_style.rookImage_dark();
}

QList<QList<QPair<int, int> > > RookFigure::checkingAvailableFieldsLists()
{
    return {
        {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
        {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
        {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
        {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}}
    };

}

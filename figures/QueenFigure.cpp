#include "QueenFigure.h"

#include "AbstractStyle.h"

QueenFigure::QueenFigure(Color a_color, QObject *a_parent /*= nullptr*/)
    :AbstractFigure(a_color, a_parent)
{}

QVariant QueenFigure::image(const AbstractStyle &a_style) const
{
    return this->color() == Color::LIGHT ? a_style.qeenImage_light(): a_style.queenImage_dark();
}

QList<QList<QPair<int, int> > > QueenFigure::checkingAvailableFieldsLists()
{
    return {
        {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
        {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
        {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
        {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},

        {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
        {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
        {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
        {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}}

    };

}

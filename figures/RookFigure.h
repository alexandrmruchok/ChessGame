#ifndef ROOKFIGURE_H
#define ROOKFIGURE_H

#include "AbstractFigure.h"


class RookFigure : public AbstractFigure
{
public:
    RookFigure(Color a_color, QObject *a_parent = nullptr);

    QVariant image(const AbstractStyle& a_style) const;

protected:
    QList<QList<QPair<int, int> > > checkingAvailableFieldsLists();
};

#endif // ROOKFIGURE_H

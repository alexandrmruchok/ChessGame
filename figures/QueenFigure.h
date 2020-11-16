#ifndef QUEENFIGURE_H
#define QUEENFIGURE_H

#include "AbstractFigure.h"


class QueenFigure : public AbstractFigure
{
public:
    QueenFigure(Color a_color, QObject *a_parent = nullptr);

public:

    QVariant image(const AbstractStyle& a_style) const override;

protected:
    QList<QList<QPair<int, int> > > checkingAvailableFieldsLists() override;
};

#endif // QUEENFIGURE_H

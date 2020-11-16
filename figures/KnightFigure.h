#ifndef KNIGHTFIGURE_H
#define KNIGHTFIGURE_H

#include "AbstractFigure.h"


class KnightFigure : public AbstractFigure
{
public:
    KnightFigure(Color a_color, QObject *a_parent = nullptr);

public:


    QVariant image(const AbstractStyle& a_style) const override;

protected:
    QList<QList<QPair<int, int> > > checkingAvailableFieldsLists() override;
};

#endif // KNIGHTFIGURE_H

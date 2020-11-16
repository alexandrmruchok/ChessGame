#ifndef BISHOPFIGURE_H
#define BISHOPFIGURE_H

#include "AbstractFigure.h"


class BishopFigure : public AbstractFigure
{
public:
    BishopFigure(Color a_color, QObject *a_parent = nullptr);

public:

    QVariant image(const AbstractStyle& a_style) const override;

protected:
    QList<QList<QPair<int, int> > > checkingAvailableFieldsLists() override;
};

#endif // BISHOPFIGURE_H

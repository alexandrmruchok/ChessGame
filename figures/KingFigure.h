#ifndef KINGFIGURE_H
#define KINGFIGURE_H

#include "AbstractFigure.h"


class KingFigure : public AbstractFigure
{
public:
    KingFigure(Color a_color, QObject *a_parent = nullptr);


    QVariant image(const AbstractStyle& a_style) const override;

protected:
    QList<QList<QPair<int, int> > > checkingAvailableFieldsLists() override;
};

#endif // KINGFIGURE_H

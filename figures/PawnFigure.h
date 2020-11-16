#ifndef PAWNFIGURE_H
#define PAWNFIGURE_H

#include "AbstractFigure.h"


class PawnFigure : public AbstractFigure
{
public:
    PawnFigure(Color a_color, QObject *a_parent = nullptr);

public:
    bool hasAvailableMovingFields() override;
    QList<Field *> availableMovingFields() override;

    QVariant image(const AbstractStyle& a_style) const override;

    virtual bool canBeat(Field *a_field) override;
};

#endif // PAWNFIGURE_H

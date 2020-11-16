#include "AbstractStyle.h"

#include <QVariant>

#include "AbstractFigure.h"

AbstractStyle::AbstractStyle(QObject *a_parent /*= nullptr*/)
    :QObject(a_parent)
{

}

QVariant AbstractStyle::figureImage(AbstractFigure *a_figure) const
{
    return a_figure->image(*this);
}

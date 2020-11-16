#ifndef STYLEABSTRACT_H
#define STYLEABSTRACT_H

#include <QVariant>

class AbstractFigure;

class AbstractStyle: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant fieldsColor_light READ fieldsColor_light CONSTANT)
    Q_PROPERTY(QVariant fieldsColor_dark READ fieldsColor_dark CONSTANT)
    Q_PROPERTY(QVariant chessBoardBackground READ chessBoardBackground CONSTANT)
    Q_PROPERTY(QVariant fontColor READ fontColor CONSTANT)

public:
    AbstractStyle(QObject* a_parent = nullptr);
    virtual ~AbstractStyle() = default;

    virtual QVariant fieldsColor_light() const = 0;
    virtual QVariant fieldsColor_dark() const = 0;
    virtual QVariant fontColor() const = 0;
    virtual QVariant chessBoardBackground() const = 0;

    virtual QVariant kingImage_light() const = 0;
    virtual QVariant kingImage_dark() const= 0;
    virtual QVariant qeenImage_light() const = 0;
    virtual QVariant queenImage_dark() const = 0;
    virtual QVariant bishopImage_light() const = 0;
    virtual QVariant bishopImage_dark() const = 0;
    virtual QVariant knightImage_light() const = 0;
    virtual QVariant knightImage_dark() const = 0;
    virtual QVariant rookImage_light() const = 0;
    virtual QVariant rookImage_dark() const = 0;
    virtual QVariant pawnImage_light() const = 0;
    virtual QVariant pawnImage_dark() const = 0;

    Q_INVOKABLE virtual QVariant figureImage(AbstractFigure *a_figure) const;
};

Q_DECLARE_METATYPE(AbstractStyle*)

#endif // STYLEABSTRACT_H

#ifndef CLASSICSTYLE_H
#define CLASSICSTYLE_H

#include <QVariant>

#include "AbstractStyle.h"

class ClassicStyle : public AbstractStyle
{

public:
    ClassicStyle(QObject* a_parent = nullptr)
        : AbstractStyle(a_parent) {}

    QVariant fieldsColor_light() const    { return "#F9F9F9";}
    QVariant fieldsColor_dark() const     { return "#676865";}
    QVariant fontColor() const            { return "#CACCC7";}
    QVariant chessBoardBackground() const { return "#4C4C4A";}

    QVariant kingImage_light() const  { return "qrc:/images/white_king.png"  ; }
    QVariant kingImage_dark() const   { return "qrc:/images/black_king.png"  ; }
    QVariant qeenImage_light() const  { return "qrc:/images/white_queen.png" ; }
    QVariant queenImage_dark() const  { return "qrc:/images/black_queen.png" ; }
    QVariant bishopImage_light() const{ return "qrc:/images/white_bishop.png"; }
    QVariant bishopImage_dark() const { return "qrc:/images/black_bishop.png"; }
    QVariant knightImage_light() const{ return "qrc:/images/white_knight.png"; }
    QVariant knightImage_dark() const { return "qrc:/images/black_knight.png"; }
    QVariant rookImage_light() const  { return "qrc:/images/white_rook.png"  ; }
    QVariant rookImage_dark() const   { return "qrc:/images/black_rook.png"  ; }
    QVariant pawnImage_light() const  { return "qrc:/images/white_pawn.png"  ; }
    QVariant pawnImage_dark() const   { return "qrc:/images/black_pawn.png"  ; }
};

#endif // CLASSICSTYLE_H

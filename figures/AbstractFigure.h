#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QObject>

#include "Field.h"
#include <QVariant>

class AbstractStyle;

enum class Color { LIGHT, DARK };


class AbstractFigure : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(bool canBeSelected READ canBeSelected WRITE setCanBeSelected NOTIFY canBeSelectedChanged)
    Q_PROPERTY(Color color READ color CONSTANT)

public:

    explicit AbstractFigure(Color a_color, QObject *a_parent = nullptr);

    bool isSelected() const;
    Q_INVOKABLE void select();
    Q_INVOKABLE void deselect();
    void setSelected(bool a_selected);

    void setCanBeSelected(bool a_canBeSelected = true);
    bool canBeSelected() const;

    virtual bool hasAvailableMovingFields();
    virtual QList<Field*> availableMovingFields();
    virtual QList<Field*> fieldsForBeatCovering(const Field& a_beatFiald){Q_UNUSED(a_beatFiald) return {};/*TODO*/}

    virtual bool canBeat(Field *a_field);
    virtual bool canMoveTo(const Field& a_field);

    Q_INVOKABLE virtual void move(Field* a_destField);

    virtual QVariant image(const AbstractStyle& a_style) const = 0;


    Field *field() const;
    void setField(Field *a_boardField);

    Color color() const;

signals:

    void selected();
    void selectedChanged(bool a_selected);
    void canBeSelectedChanged(bool a_selected);
    void wasBeaten();


protected:
    virtual QList<QList<QPair<int, int>>> checkingAvailableFieldsLists(){return {};}

private:

    Color m_color;

    bool m_selected = false;
    bool m_canBeSelected = false;

    Field* m_boardField = nullptr;
};

Q_DECLARE_METATYPE(AbstractFigure*)

Color opposite(Color a_color);



#endif // CHESSMAN_H

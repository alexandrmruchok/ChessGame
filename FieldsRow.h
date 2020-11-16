#ifndef BOARDFIELDSROW_H
#define BOARDFIELDSROW_H

#include <QObject>
#include <QVector>

#include "ChessBoard.h"
#include "BoardPos.h"

class Field;
class ChessBoard;

class FieldsRow : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Field* A READ a CONSTANT)
    Q_PROPERTY(Field* B READ b CONSTANT)
    Q_PROPERTY(Field* C READ c CONSTANT)
    Q_PROPERTY(Field* D READ d CONSTANT)
    Q_PROPERTY(Field* E READ e CONSTANT)
    Q_PROPERTY(Field* F READ f CONSTANT)
    Q_PROPERTY(Field* G READ g CONSTANT)
    Q_PROPERTY(Field* H READ h CONSTANT)
public:
    explicit FieldsRow(ChessBoard *a_chessBoard, int a_row);

    Field* a() {return m_fields[0];}
    Field* b() {return m_fields[1];}
    Field* c() {return m_fields[2];}
    Field* d() {return m_fields[3];}
    Field* e() {return m_fields[4];}
    Field* f() {return m_fields[5];}
    Field* g() {return m_fields[6];}
    Field* h() {return m_fields[7];}

    Field* fieldAt(BoardPos::Column a_column);


   // field();
    int row() const;

signals:
private:
    QVector<Field*> m_fields;
    int m_row;
};

#endif // BOARDFIELDSROW_H

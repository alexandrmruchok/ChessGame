#ifndef APPLICATION_H
#define APPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ChessBoard.h"
#include "AppStateMachine.h"

#include "AbstractStyle.h"

class Application : public QGuiApplication
{
    Q_OBJECT
    Q_PROPERTY(AbstractStyle* style READ style WRITE setStyle NOTIFY styleChanged)
    Q_PROPERTY(AppStateMachine* stateMachine READ stateMachine CONSTANT)
public:
    Application(int &argc, char **argv);

    void loadQml();
    void init();
    ChessBoard* chessBoard();


public:
    AbstractStyle *style() const;
    void setStyle(AbstractStyle *a_style);

    AppStateMachine *stateMachine() const;

signals:

    void styleChanged(AbstractStyle *a_style);

private:
    void registerQmlTypes();
    void setContextProperties();
    void setupStatesBehavior();

    const QUrl MAIN_QML_URL;

    QQmlApplicationEngine m_engine;
    AppStateMachine* m_stateMachine;
    AbstractStyle* m_style;

    ChessBoard m_chessBoard;

};

#endif // APPLICATION_H

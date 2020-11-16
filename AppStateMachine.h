#ifndef APPSTATEMACHINE_H
#define APPSTATEMACHINE_H

#include "stateChart.h"

class AppStateMachine : public StateMachine
{
    Q_OBJECT
    //Events:
    Q_PROPERTY(QString arranged         MEMBER ARRANGED         CONSTANT)
    Q_PROPERTY(QString figureSelected   MEMBER FIGURE_SELECTED  CONSTANT)
    Q_PROPERTY(QString fieldSelected    MEMBER FIELD_SELECTED   CONSTANT)
    Q_PROPERTY(QString movingChanged    MEMBER MOVING_CHANGED   CONSTANT)
    Q_PROPERTY(QString gameFinished     MEMBER GAME_FINISHED    CONSTANT)
    Q_PROPERTY(QString restarted        MEMBER RESTARTED        CONSTANT)

public:
    AppStateMachine(QObject *a_parent = nullptr);

    //Events:
    const QString ARRANGED = "arranged";
    const QString FIGURE_SELECTED = "figureSelected";
    const QString FIELD_SELECTED = "fieldSelected";
    const QString MOVING_CHANGED = "movingChanged";
    const QString GAME_FINISHED = "gameFinished";
    const QString RESTARTED = "restarted";

    //States:
    const QString FIGURES_ARRANGEMENT = "figuresArrangement";
    const QString GAME = "game";
    const QString FIGURE_SELECTING = "figureSelecting";
    const QString FIELD_SELECTING = "fieldSelecting";
    const QString FIGURE_MOVING = "figureMoving";
    const QString GAME_RESULT = "gameResult";
};

Q_DECLARE_METATYPE(AppStateMachine*)


#endif // APPSTATEMACHINE_H

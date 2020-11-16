#include "AppStateMachine.h"

#include <QDebug>

AppStateMachine::AppStateMachine(QObject *a_parent/* = nullptr*/)
    : StateMachine(a_parent)
{
    for (const QString& curentStateName: this->stateNames(false))
    {
        this->connectToState(curentStateName, [curentStateName](bool a_active) {
            qDebug() << (a_active ? "++++++++++++++++++++++++++" : "-------------------------") << (a_active ? "Entered" : "Exited")<< "the state " << curentStateName << (a_active ? "++++++++++++++++++++++++++" : "-------------------------");
        });
    }
}

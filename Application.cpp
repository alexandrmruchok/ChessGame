#include "Application.h"

#include <QQmlContext>

#include "FieldsRow.h"
#include "Field.h"
#include "AbstractFigure.h"
#include "ClassicStyle.h"
#include <QTime>

Application::Application(int &argc, char **argv)
    : QGuiApplication(argc, argv)
    , MAIN_QML_URL(QStringLiteral("qrc:/main.qml"))
    , m_stateMachine(new AppStateMachine(this))
{
    connect(&m_engine, &QQmlApplicationEngine::objectCreated,
                     this, [this](QObject *obj, const QUrl &objUrl) {
        if (!obj && this->MAIN_QML_URL == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    this->setupStatesBehavior();
    this->stateMachine()->start();

    connect(this->chessBoard(), &ChessBoard::figureSelected, [this]{
        this->stateMachine()->submitEvent(this->stateMachine()->FIGURE_SELECTED);
    });

}

void Application::loadQml()
{
    m_engine.load(MAIN_QML_URL);
}

void Application::init()
{
    qsrand(QTime::currentTime().msecsSinceStartOfDay());

    this->registerQmlTypes();
    this->setContextProperties();

    this->setStyle(new ClassicStyle(this));

}

void Application::registerQmlTypes()
{
    qmlRegisterUncreatableType<FieldsRow>("Chess", 1, 0, "FieldsRow", "Cannot create an instance of FieldsRow");
    qmlRegisterUncreatableType<Field>("Chess", 1, 0, "Field", "Cannot create an instance of Field");
    qmlRegisterUncreatableType<AbstractFigure>("Chess", 1, 0, "AbstractFigure", "Cannot create an instance of AbstractFigure");
    qmlRegisterUncreatableType<AbstractStyle>("Chess", 1, 0, "AbstractStyle", "Cannot create an instance of ClassicStyle");
    qmlRegisterUncreatableType<Application>("Chess", 1, 0, "Application", "Cannot create an instance of Application");
    qmlRegisterUncreatableType<AppStateMachine>("Chess", 1, 0, "AppStateMachine", "Cannot create an instance of AppStateMachine");
}

void Application::setContextProperties()
{
    m_engine.rootContext()->setContextProperty("app", this);
    m_engine.rootContext()->setContextProperty("chessboard", this->chessBoard());
}

void Application::setupStatesBehavior()
{
    ///////////////////  FIGURES_ARRANGEMENT  ///////////////////

    this->stateMachine()->connectToState(this->stateMachine()->FIGURES_ARRANGEMENT, [this](bool a_active)
    {
        if (a_active)
        {
            this->chessBoard()->arrangeFigures();

            this->stateMachine()->submitEvent(this->stateMachine()->ARRANGED);
        }
    });

    ///////////////////  FIGURE_SELECTING  ///////////////////

    this->stateMachine()->connectToState(this->stateMachine()->FIGURE_SELECTING, [this](bool a_active)
    {
        if (a_active)
        {
            this->chessBoard()->updateMovableFigures();

            if (this->chessBoard()->currentColor() == Color::DARK)
            {
                this->chessBoard()->selectRandomFigure();
            }
        }
    });

    ///////////////////  FIELD_SELECTING  ///////////////////

    this->stateMachine()->connectToState(this->stateMachine()->FIELD_SELECTING, [this](bool a_active)
    {
        if (a_active)
        {
            this->chessBoard()->updateAvailableFields();

            if (this->chessBoard()->currentColor() == Color::DARK)
            {
                this->chessBoard()->selectRandomField();
                this->stateMachine()->submitEvent(this->stateMachine()->FIELD_SELECTED);
            }

        }
    });

    ///////////////////  FIGURE_MOVING  ///////////////////

    this->stateMachine()->connectToState(this->stateMachine()->FIGURE_MOVING, [this](bool a_active)
    {
        if (a_active)
        {
            this->chessBoard()->clearAvailableFields();

            this->chessBoard()->setSelectedFigure(nullptr);
        }
    });

    ///////////////////  >>> MOVING_CHANGED >>>  ///////////////////


    this->stateMachine()->connectToEvent(this->stateMachine()->MOVING_CHANGED, [this](const QScxmlEvent &)
    {
        this->chessBoard()->setCurrentColor(::opposite(this->chessBoard()->currentColor()));
    });

    connect(this->chessBoard(), &ChessBoard::checkmate, [this]{
        this->stateMachine()->submitEvent(this->stateMachine()->GAME_FINISHED);
    });
    connect(this->chessBoard(), &ChessBoard::stalemate, [this]{
        this->stateMachine()->submitEvent(this->stateMachine()->GAME_FINISHED);
    });
}

AppStateMachine *Application::stateMachine() const
{
    return m_stateMachine;
}

AbstractStyle *Application::style() const
{
    return m_style;
}

void Application::setStyle(AbstractStyle *a_style)
{
    if (m_style == a_style)
        return;

    m_style = a_style;
    emit this->styleChanged(a_style);
}

ChessBoard *Application::chessBoard()
{
    return &m_chessBoard;
}

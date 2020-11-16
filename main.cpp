#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <Application.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    Application app(argc, argv);

    app.init();
    app.loadQml();

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "generator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.globalObject().setProperty("randomGenerator", engine.newQObject(new Generator));

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "net.h"
#include "myrpc.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
     qmlRegisterType<Net>("com.gen.Net",1,0,"Net");
     qmlRegisterType<MyRpc>("com.gen.MyRpc",1,0,"MyRpc");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

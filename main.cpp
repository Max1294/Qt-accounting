#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tablemodel.h"
#include "function.h"
#include "treeviewmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<TableModel>("TableModel", 1, 0, "DatabaseModel");
    qmlRegisterType<TreeViewModel>("TreeViewModel", 1, 0, "TreeViewModel");
//    qmlRegisterType<TableModel::TreeViewModel>("TreeViewModel", 1, 0, "TreeViewModel");
//    OpenDatabase("TestDB");
    QQmlApplicationEngine engine;
    engine.addImportPath(":/qml");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

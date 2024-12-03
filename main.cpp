#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "AppLauncher.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    AppLauncher appLauncher;
    appLauncher.loadApplications(":/Applications.xml"); // Load XML file
    engine.rootContext()->setContextProperty("AppLauncher", &appLauncher);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("AppLauncher", "Main");

    return app.exec();
}

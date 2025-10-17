#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <menu.h>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QIcon>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Fusion");
    app.setWindowIcon(QIcon("icon/DUCK.jpg"));
    app.setApplicationName("DUCK");
    app.setOrganizationName("El 3esha Company");

    qmlRegisterType<Menu>("ImageEditor", 1, 0, "Menu");

    QQmlApplicationEngine engine;

    Menu menu;
    engine.rootContext()->setContextProperty("menu", &menu);

    engine.loadFromModule("Baby_photoshop_fix", "Main");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

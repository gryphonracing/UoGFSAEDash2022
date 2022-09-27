#include <QApplication>
#include <QQmlApplicationEngine>
#include <fmt/core.h>

#include <MotorController.hpp>

#ifdef QT_DEBUG
#include <RuntimeQml.hpp>
#endif

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MotorController* motor_controller = new MotorController(); // Should be before QQml engine
    QQmlApplicationEngine engine;

    qmlRegisterSingletonInstance<MotorController>(
        "CAN.MotorController", 1, 0, "MotorController", motor_controller);
#ifdef QT_DEBUG
    RuntimeQml* rt = new RuntimeQml(&engine);
    rt->parseQrc(ROOT_SOURCE_PATH "/qml.qrc");
    rt->setAutoReload(true); // Reload automatically on file update

    rt->load(QStringLiteral("qrc:/main.qml"));
#else
    engine.load(QStringLiteral("qrc:/main.qml"));
#endif
    return app.exec();
}

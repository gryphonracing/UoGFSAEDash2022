#include <QApplication>
#include <QQmlApplicationEngine>
#include <fmt/core.h>

#include <AN400ECU.hpp>

#ifdef QT_DEBUG
#include <runtimeqml.hpp>
#endif

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    // The AN400ECU class inpersonates all of the other systems. This allows us to re-use the front
    // end without any changes
    AN400ECU* motor_controller = new AN400ECU(); // Should be before QQml engine
    AN400ECU* energy_meter = new AN400ECU();     // Should be before QQml engine
    AN400ECU* bms = new AN400ECU();              // Should be before QQml engine
    QQmlApplicationEngine engine;

    qmlRegisterSingletonInstance<AN400ECU>(
        "CAN.MotorController", 1, 0, "MotorController", motor_controller);
    qmlRegisterSingletonInstance<AN400ECU>("CAN.EnergyMeter", 1, 0, "EnergyMeter", energy_meter);
    qmlRegisterSingletonInstance<AN400ECU>("CAN.BMS", 1, 0, "BMS", bms);
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

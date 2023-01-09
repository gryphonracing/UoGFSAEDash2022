#pragma once

#include <DBCInterface.hpp>
#include <QObject>

class MotorController : public QObject, public CAN::DBCInterface<MotorController> {
    Q_OBJECT
  public:
    MotorController(QObject* parent = nullptr)
        : QObject(parent), DBCInterface("20220510_Gen5_CAN_DB.dbc") {
        can_signal_dispatch["INV_Motor_Speed"] = &MotorController::newMotorRPM;
        can_signal_dispatch["INV_Motor_Temp"] = &MotorController::newMotorTemp;
        can_signal_dispatch["INV_Coolant_Temp"] = &MotorController::newCoolantTemp;
        can_signal_dispatch["INV_Analog_Input_1"] = &MotorController::new12VVoltage;
        can_signal_dispatch["INV_Analog_Input_2"] = &MotorController::newOilTemp;
    }

  signals:
    void newMotorRPM(float rpm);
    void newMotorTemp(float temp);
    void newCoolantTemp(float temp);
    void new12VVoltage(float voltage);
    void newOilTemp(float temp);

  public:
    static constexpr size_t num_of_filters = 2;
    inline static can_filter filters[num_of_filters] = {
        {
            0x0A0,
            0x7F0 // Grab all messages from 0xA0 to 0xAF
        },
        {
            0x0B0,
            0x7FF // Grab all messages from 0xB0
        }};

    static constexpr uint32_t timeout_ms = 500;
};

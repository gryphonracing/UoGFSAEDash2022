#pragma once

#include <DBCInterface.hpp>
#include <QObject>
#include <algorithm>
#include <fmt/core.h>

class AN400ECU : public QObject, public CAN::DBCInterface<AN400ECU> {
    Q_OBJECT
  public:
    AN400ECU(QObject* parent = nullptr) : QObject(parent), DBCInterface("AN400ECU.dbc") {
        can_signal_dispatch["RPM"] = &AN400ECU::newMotorRPM;
        can_signal_dispatch["Thermistor1_Temp"] = &AN400ECU::newMotorTemp;
        can_signal_dispatch["Coolant_Temp"] = &AN400ECU::newCoolantTemp;
        can_signal_dispatch["Thermistor2_Temp"] = &AN400ECU::newOilTemp;
        can_signal_dispatch["Battery_Voltage"] = &AN400ECU::batteryVoltageToSOC;
        can_signal_dispatch["Air_Temp"] = &AN400ECU::newAccumulatorMaxTemp;
        // can_signal_dispatch["Pack_Current"] = &AN400ECU::newAccumulatorCurrent;
        // can_signal_dispatch["Internal_Temperature"] = &AN400ECU::newBMSTemp;
        // can_signal_dispatch["Current"] = &AN400ECU::newCurrent;
        // can_signal_dispatch["Voltage"] = &AN400ECU::newVoltage;
        // can_signal_dispatch["INV_Analog_Input_1"] = &AN400ECU::new12VVoltage;
        // can_signal_dispatch["Pack_Open_Voltage"] = &AN400ECU::newAccumulatorOpenVoltage;
        // can_signal_dispatch["Pack_Inst_Voltage"] = &AN400ECU::newAccumulatorInstVoltage;
    }

    void batteryVoltageToSOC(float voltage) {
        fmt::print("Battery voltage");
        float empty_battery = 11.f; // 11 Volts becomes 0% Battery
        float full_battery = 15.f;  // 15 Volts becomes 100% Battery
        float clamped_voltages =
            std::clamp(voltage, empty_battery, full_battery); // Now contains values from 11v - 15v
        float calculated_SOC =
            (clamped_voltages - empty_battery) * (100 / (full_battery - empty_battery));
        emit newAccumulatorSOC(calculated_SOC);
    }

  signals:
    // Inpersonates Motor Controller for GRC22
    void newMotorRPM(float rpm);
    void newMotorTemp(float temp);
    void newCoolantTemp(float temp);
    void new12VVoltage(float voltage);
    void newOilTemp(float temp);

    // Inpersonates Energy Meter for GRC22
    void newVoltage(float voltage);
    void newCurrent(float current);

    // Inpersonates BMS for GRC22
    void newBMSTemp(float temp);
    void newAccumulatorMaxTemp(float temp);
    void newAccumulatorCurrent(float current);
    void newAccumulatorInstVoltage(float voltage);
    void newAccumulatorOpenVoltage(float voltage);
    void newAccumulatorSOC(float percent);

  public:
    static constexpr size_t num_of_filters = 5;
    inline static can_filter filters[num_of_filters] = {
        {
            0x0CFFF048,
            0x1FFFF8FF // Grab all messages from 0CFFF048 to 0CFFF748
        },
        {
            0x0CFFF848,
            0x1FFFFCFF // Grab all messages from 0CFFF848 to 0CFFFB48
        },
        {
            0x0CFFFC48,
            0x1FFFFEFF // Grab all messages from 0CFFFC48 to 0CFFFD48
        },
        {
            0x0CFFFE48,
            0x1FFFFFFF // Grab all messages from 0CFFFE48
        },
        {
            0x0CFFD048,
            0x1FFFFFFF // Grab all messages from 0CFFD048
        }};

    static constexpr uint32_t timeout_ms = 500;
};

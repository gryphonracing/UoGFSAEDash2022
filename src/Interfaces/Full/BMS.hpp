#pragma once

#include <QObject>
#include <DBCInterface.hpp>

class BMS : public QObject, public CAN::DBCInterface<BMS> {
    Q_OBJECT
  public:
    BMS(QObject* parent = nullptr) : QObject(parent), DBCInterface("Orion_CANBUS.dbc") {
        can_signal_dispatch["Pack_Open_Voltage"]    = &BMS::newAccumulatorOpenVoltage;
        can_signal_dispatch["Pack_SOC"]             = &BMS::newAccumulatorSOC;
        can_signal_dispatch["Pack_Inst_Voltage"]    = &BMS::newAccumulatorInstVoltage;
        can_signal_dispatch["Pack_Current"]         = &BMS::newAccumulatorCurrent;
        can_signal_dispatch["High_Temperature"]     = &BMS::newAccumulatorMaxTemp;
        can_signal_dispatch["Internal_Temperature"] = &BMS::newBMSTemp;
    }

  signals:
    void newBMSTemp(float temp);
    void newAccumulatorMaxTemp(float temp);
    void newAccumulatorCurrent(float current);
    void newAccumulatorInstVoltage(float voltage);
    void newAccumulatorOpenVoltage(float voltage);
    void newAccumulatorSOC(float percent);

  public:
    static constexpr size_t num_of_filters = 3;
    inline static can_filter filters[num_of_filters] = {
        {
            0x7EB,
            0x7FF // Only grab from our BMS (7EB is the response addr, 7E3 is the BMS addr)
        },
        {
            0x0C0, // Grab 0x0C0 and 0x0C1 for broadcast messages
            0x7FE
        },
        {
            0x0C2, // Grab 0x0C2 for broadcast messages
            0x7FF
        }
    };

    static constexpr uint32_t timeout_ms = 500;
};

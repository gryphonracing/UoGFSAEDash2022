#pragma once

#include <DBCInterface.hpp>
#include <QObject>

class EnergyMeter : public QObject, public CAN::DBCInterface<EnergyMeter> {
    Q_OBJECT
  public:
    EnergyMeter(QObject* parent = nullptr)
        : QObject(parent), DBCInterface("Energy_Meter_CAN_Messages.dbc") {
        can_signal_dispatch["Current"] = &EnergyMeter::newCurrent;
        can_signal_dispatch["Voltage"] = &EnergyMeter::newVoltage;
    }

  signals:
    void newVoltage(float voltage);
    void newCurrent(float current);

  public:
    static constexpr size_t num_of_filters = 2;
    inline static can_filter filters[num_of_filters] = {{
                                                            0x100,
                                                            0x7FF // Grab all messages from 0x100
                                                        },
                                                        {
                                                            0x400,
                                                            0x7FF // Grab all messages from 0x400
                                                        }};

    static constexpr uint32_t timeout_ms = 500;
};
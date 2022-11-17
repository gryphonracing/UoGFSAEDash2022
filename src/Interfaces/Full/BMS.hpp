#pragma once

#include <QObject>
#include <fstream>
#include <unordered_map>

#include <Interface.hpp>
#include <dbcppp/Network.h>

class BMS : public QObject, public CAN::Interface {
    Q_OBJECT
  public:
    BMS(QObject* parent = nullptr) : QObject(parent), dbc_network(dbcppp::INetwork::LoadNetworkFromFile("Orion_CANBUS.dbc")) {
        this->CAN::Interface::startReceiving(
            "can0", BMS::filters, BMS::num_of_filters, BMS::timeout_ms);
        
        for (const dbcppp::IMessage& msg : dbc_network->Messages()) {
            messages.insert(std::make_pair(msg.Id(), msg));
        }
        
        can_signal_dispatch["Pack_Open_Voltage"]    = &newAccumulatorOpenVoltage;
        can_signal_dispatch["Pack_SOC"]             = &newAccumulatorSOC;
        can_signal_dispatch["Pack_Inst_Voltage"]    = &newAccumulatorInstVoltage;
        can_signal_dispatch["Pack_Current"]         = &newAccumulatorCurrent;
        can_signal_dispatch["High_Temperature"]     = &newAccumulatorMaxTemp;
        can_signal_dispatch["Internal_Temperature"] = &newBMSTemp;
    }

    ~BMS() = default;

  signals:
    void newBMSTemp(float temp);
    void newAccumulatorMaxTemp(float temp);
    void newAccumulatorCurrent(float current);
    void newAccumulatorInstVoltage(float voltage);
    void newAccumulatorOpenVoltage(float voltage);
    void newAccumulatorSOC(float percent);

  private:
    // As of now, newFrame and newError should be extremely fast functions before emitting more
    // signals
    void newFrame(const can_frame&) override;
    void newError(const can_frame&) override;
    void newTimeout() override;

  private:
    static dbcppp::INetwork dbc_network;
    static std::unordered_map<uint64_t, const dbcppp::IMessage&> can_messages;
    static std::unordered_map<std::string, void (*)(float)> can_signal_dispatch;

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
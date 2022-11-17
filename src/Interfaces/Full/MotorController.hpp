#pragma once

#include <QObject>
#include <dbcppp/Network.h>

#include <Interface.hpp>

class MotorController : public QObject, public CAN::Interface {
    Q_OBJECT
  public:
    MotorController(QObject* parent = nullptr) : QObject(parent), dbc_network(dbcppp::INetwork::LoadNetworkFromFile("CM200DZ_Motor_Controller.dbc")) {
        this->CAN::Interface::startReceiving("can0",
                                             MotorController::filters,
                                             MotorController::num_of_filters,
                                             MotorController::timeout_ms);
        
        for (const dbcppp::IMessage& msg : dbc_network->Messages()) {
            messages.insert(std::make_pair(msg.Id(), msg));
        }
        
        can_signal_dispatch["Motor_Speed"]         = &newMotorRPM;
        can_signal_dispatch["Motor_Temperature"]   = &newMotorTemp;
        can_signal_dispatch["Coolant_Temperature"] = &newCoolantTemp;
        can_signal_dispatch["12V_Voltage"]         = &new12VVoltage;
        can_signal_dispatch["Oil_Temp"]            = &newOilTemp;
    }
    ~MotorController() = default;

  signals:
    void newMotorRPM(float rpm);
    void newMotorTemp(float temp);
    void newCoolantTemp(float temp);
    void new12VVoltage(float voltage);
    void newOilTemp(float temp);

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
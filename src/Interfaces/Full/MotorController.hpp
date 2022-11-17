#pragma once

#include <QObject>
#include <dbcppp/Network.h>

#include <memory>
#include <Interface.hpp>

class MotorController : public QObject, public CAN::Interface {
    Q_OBJECT
  public:
    MotorController(QObject* parent = nullptr) : QObject(parent)
        , dbc_network(std::move(dbcppp::INetwork::LoadNetworkFromFile("20220510_Gen5_CAN_DB.dbc")[""])) {
        this->CAN::Interface::startReceiving("can0",
                                             MotorController::filters,
                                             MotorController::num_of_filters,
                                             MotorController::timeout_ms);

        for (const dbcppp::IMessage& msg : dbc_network->Messages()) {
            can_messages.insert(std::make_pair(msg.Id(), &msg));
        }
        
        can_signal_dispatch["INV_Motor_Speed"]    = &MotorController::newMotorRPM;
        can_signal_dispatch["INV_Motor_Temp"]     = &MotorController::newMotorTemp;
        can_signal_dispatch["INV_Coolant_Temp"]   = &MotorController::newCoolantTemp;
        can_signal_dispatch["INV_Analog_Input_1"] = &MotorController::new12VVoltage;
        can_signal_dispatch["INV_Analog_Input_2"] = &MotorController::newOilTemp;
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
    std::unique_ptr<dbcppp::INetwork> dbc_network;
    std::unordered_map<uint64_t, const dbcppp::IMessage*> can_messages;
    std::unordered_map<std::string, void (MotorController::*)(float)> can_signal_dispatch;

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
#pragma once

#include <QObject>

#include <Interface.hpp>

class BMS : public QObject, public CAN::Interface {
    Q_OBJECT
  public:
    BMS(QObject* parent = nullptr) : QObject(parent) {
        this->CAN::Interface::startReceiving(
            "can0", BMS::filters, BMS::num_of_filters, BMS::timeout_ms);
    }

    ~BMS() = default;


    float toCelsius(uint8_t byte);
    float toStateOfCharge(uint8_t byte);
    float toCurrent(uint8_t low_byte, uint8_t high_byte);
    float toVoltage(uint8_t low_byte, uint8_t high_byte);

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
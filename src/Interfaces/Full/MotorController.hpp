#pragma once

#include <QObject>

#include <Interface.hpp>

class MotorController : public QObject, public CAN::Interface {
    Q_OBJECT
  public:
    MotorController(QObject* parent = nullptr) : QObject(parent) {
        this->CAN::Interface::startReceiving("can0",
                                             MotorController::filters,
                                             MotorController::num_of_filters,
                                             MotorController::timeout_ms);
    }
    ~MotorController() = default;

    float toCelsius(uint8_t low_byte, uint8_t high_byte);
    float toLowVoltage(uint8_t low_byte, uint8_t high_byte);
    float toNm(uint8_t low_byte, uint8_t high_byte);
    float toHighVoltage(uint8_t low_byte, uint8_t high_byte);
    float toAmps(uint8_t low_byte, uint8_t high_byte);
    float toDegrees(uint8_t low_byte, uint8_t high_byte);
    int16_t toRPM(uint8_t low_byte, uint8_t high_byte);
    bool toBool(uint8_t byte);
    float toHz(uint8_t low_byte, uint8_t high_byte);
    float tokW(uint8_t low_byte, uint8_t high_byte);
    float toWebers(uint8_t low_byte, uint8_t high_byte);

    // either 100 or 10000 scale
    float toProportionalGain100(uint8_t low_byte, uint8_t high_byte);
    float toProportionalGain10000(uint8_t low_byte, uint8_t high_byte);
    float toIntegralGain(uint8_t low_byte, uint8_t high_byte);
    float toDerivativeGain(uint8_t low_byte, uint8_t high_byte);
    float toLowpassFilterGain(uint8_t low_byte, uint8_t high_byte);
    uint16_t toCount(uint8_t low_byte, uint8_t high_byte);
    float toPSI(uint8_t low_byte, uint8_t high_byte);

  signals:
    void newMotorRPM(int16_t rpm);
    void newMotorTemp(int16_t temp);
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
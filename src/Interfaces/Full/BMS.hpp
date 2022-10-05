#pragma once

#include <QObject>

#include <Interface.hpp>

class BMS : public QObject, public CAN::Interface {
    Q_OBJECT
  public:
    BMS(QObject* parent = nullptr) : QObject(parent) {
        this->CAN::Interface::startReceiving(
            "can0", BMS::filters, BMS::timeout_ms); // Get everything
    }

    ~BMS() = default;

  signals:
    void newVoltage(float voltage);
    void newBatteryPercent(float percent);

  private:
    // As of now, newFrame and newError should be extremely fast functions before emitting more
    // signals
    void newFrame(const can_frame&) override;
    void newError(const can_frame&) override;
    void newTimeout() override;

  private:
    static constexpr std::array<can_filter, 1> filters{{
        0x000007EB,
        0xFFFFFFFF // Only grab from our BMS (7EB is the response addr, 7E3 is the BMS addr)
    }};

    static constexpr uint32_t timeout_ms = 500;
};
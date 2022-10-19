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
    static constexpr size_t num_of_filters = 2;
    inline static can_filter filters[num_of_filters] = {
        {
            0x7EB,
            0x7FF // Only grab from our BMS (7EB is the response addr, 7E3 is the BMS addr)
        },
        {
            0x0C0, // Grab 0x0C0 and 0x0C1 for broadcast messages
            0x7FE
        }
    };

    static constexpr uint32_t timeout_ms = 500;
};
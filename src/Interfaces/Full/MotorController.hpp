#pragma once

#include <QObject>

#include <Interface.hpp>

class MotorController : public Interface, public QObject {
    Q_OBJECT
  public:
    MotorController(QObject* parent) : QObject(parent){};
    ~MotorController() = default;

    void startReceiving();

  signals:
    // As of now, newFrame and newError should be extremely fast functions before emitting more
    // signals
    void newFrame(const can_frame&) override;
    void newError(const can_frame&) override;
    void newTimeout() override;

  private:
    static constexpr std::array<can_filter> filters = {
        {
            0x0A0,
            0xFF0 // Grab all messages from 0xA0 to 0xAF
        },
        {
            0x0B0,
            0xFFF // Grab all messages from 0xB0
        }};
};
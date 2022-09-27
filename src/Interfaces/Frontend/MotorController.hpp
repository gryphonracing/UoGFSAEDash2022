#pragma once

#include <QObject>
#include <thread>

#include <FakeInterface.hpp>

class MotorController : public QObject, public CAN::FakeInterface {
    Q_OBJECT
  public:
    MotorController(QObject* parent = nullptr) : QObject(parent) {
        this->CAN::FakeInterface::startReceiving();
    }
    ~MotorController() = default;

  signals:
    void newRPM(int16_t rpm);
    void newCoolantTemp(float temp);
    void newOilTemp(float temp);

  private:
    void generateValues();
};
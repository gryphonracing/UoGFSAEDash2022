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
    void newRPM(uint32_t rpm);
    void newCoolantTemp(int32_t temp);
    void newOilTemp(int32_t temp);

  private:
    void generateValues();
};
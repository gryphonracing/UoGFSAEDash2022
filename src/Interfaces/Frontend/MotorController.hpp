#pragma once

#include <QObject>
#include <thread>

#include <FakeInterface.hpp>

class MotorController : public FakeInterface, public QObject {
    Q_OBJECT
  public:
    MotorController(QObject* parent) : QObject(parent) {}
    ~MotorController() = default;

signals:
    void newRPM(uint32_t rpm);
    void newCoolantTemp(int32_t temp);
    void newOilTemp(int32_t temp);

  private:
    void generateValues() override;
};
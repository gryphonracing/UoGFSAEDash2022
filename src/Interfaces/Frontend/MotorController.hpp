#pragma once

#include <QObject>

#include <FakeInterface.hpp>

class MotorGearClass {
    Q_GADGET
  public:
    explicit MotorGear(){};

    enum Value { Null, Drive, Park };
    Q_ENUM(Value)
};

typedef MotorGearClass::Value MotorGear;

class MotorController : public QObject, public CAN::FakeInterface {
    Q_OBJECT
  public:
    MotorController(QObject* parent = nullptr) : QObject(parent) {
        this->CAN::FakeInterface::startReceiving();
    }
    ~MotorController() = default;

  signals:
    void newCoolantTemp(float temp);
    void newOilTemp(float temp);
    void newMotorTemp(float temp);
    void newMotorRPM(int16_t rpm);
    void newMotorGear(MotorGear gear);
    void new12VVoltage(float voltage);

  private:
    void generateValues();
};
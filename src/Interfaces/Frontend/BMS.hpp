#pragma once

#include <QObject>

#include <FakeInterface.hpp>

class BMS : public QObject, public CAN::FakeInterface {
    Q_OBJECT
  public:
    BMS(QObject* parent = nullptr) : QObject(parent) {
        this->CAN::FakeInterface::startReceiving();
    }
    ~BMS() = default;

  signals:
    void newVoltage(float voltage);
    void newBatteryPercent(float percent);

  private:
    void generateValues();
};
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
    void newBMSTemp(float temp);
    void newAccumulatorMaxTemp(float temp);
    void newAccumulatorCurrent(float current);
    void newAccumulatorInstVoltage(float voltage);
    void newAccumulatorOpenVoltage(float voltage);
    void newAccumulatorSOC(float percent);

  private:
    void generateValues();
};
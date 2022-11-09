import QtQuick
import QtQuick.Controls
import CAN.MotorController
import CAN.BMS

ApplicationWindow {
    visible: true
    width: 800
    height: 480
    title: "GRC Dash"
    maximumHeight: height
    maximumWidth: width
    flags: Qt.Window // | Qt.FramelessWindowHint add when final project is reached.

    minimumHeight: height
    minimumWidth: width
    Column {
        Text {
            id: rpm_text_text
            font.pointSize: 20
            text: ""
        }

        Text {
            id: coolant_temp_text
            font.pointSize: 20
            text: ""
        }

        Text {
            id: oil_temp_text
            font.pointSize: 20
            text: ""
        }

        Text {
            id: battery_voltage_text
            font.pointSize: 20
            text: ""
        }

        Text {
            id: bmsTemp
            font.pointSize: 20
            text: ""
        }
        Text {
            id: accumulatorCurrent
            font.pointSize: 20
            text: ""
        }
        Text {
            id: accumulatorMaxTemp
            font.pointSize: 20
            text: ""
        }
        Text {
            id: accumulatorInstVoltage
            font.pointSize: 20
            text: ""
        }
        Text {
            id: accumulatorOpenVoltage
            font.pointSize: 20
            text: ""
        }

        Text {
            id: accumulatorSOC
            font.pointSize: 20
            text: ""
        }
    }

    Connections {
        target: MotorController
        function onNewRPM(rpm) {
            rpm_text_text.text = `RPM: ${rpm}`
        }
        function onNewCoolantTemp(coolant_temp) {
            coolant_temp_text.text = `Coolant Temp: ${coolant_temp.toFixed(1)}`
        }
        function onNewOilTemp(oil_temp) {
            oil_temp_text.text = `Oil Temp: ${oil_temp.toFixed(1)}`
        }
    }

    Connections {
        target: BMS
        function onNewBMSTemp(temp) {
            bmsTemp.text = `BMS Temp: ${temp.toFixed(1)}`
        }
        function onNewAccumulatorMaxTemp(temp) {
            accumulatorMaxTemp.text = `Accumulator Max Temp: ${temp.toFixed(1)}`
        }
        function onNewAccumulatorCurrent(current) {
            accumulatorCurrent.text = `Accumulator Current: ${current.toFixed(1)}`
        }
        function onNewAccumulatorInstVoltage(voltage) {
            accumulatorInstVoltage.text = `Accumulator Inst Voltage: ${voltage.toFixed(1)}`
        }
        function onNewAccumulatorOpenVoltage(voltage) {            
            accumulatorOpenVoltage.text = `Accumulator Open Voltage: ${voltage.toFixed(1)}`
        }
        function onNewAccumulatorSOC(percent) {
            accumulatorSOC.text = `Accumulator %: ${percent.toFixed(1)}`
        }
    }
}
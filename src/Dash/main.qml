import QtQuick
import QtQuick.Controls
import CAN.MotorController
import CAN.BMS

ApplicationWindow {
    visible: true
    width: 400
    height: 200
    title: "GRC Dash"
    maximumHeight: 200
    maximumWidth: 400
    flags: Qt.Window // | Qt.FramelessWindowHint add when final project is reached.

    minimumHeight: 200
    minimumWidth: 400
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
            id: battery_percent_text
            font.pointSize: 20
            text: ""
        }
    }

    Connections {
        target: MotorController
        function onNewMotorRPM(rpm) {
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
        function newBMSTemp(temp) {
            console.log("BMS temp: ", temp);
        }
        function newAccumulatorMaxTemp(temp) {
            console.log("Accumulator temp: ", temp);
        }
        function newAccumulatorCurrent(current) {
            console.log("Accumulator Current: ", temp);
        }
        function newAccumulatorInstVoltage(voltage) {
            battery_voltage_text.text = `Accumulator Voltage: ${voltage.toFixed(1)}`
        }
        function newAccumulatorOpenVoltage(voltage) {
            console.log("Accumulator Voltage: ", voltage);
        }
        function newAccumulatorSOC(percent) {
            battery_percent_text.text = `Accumulator %: ${percent.toFixed(1)}`
        }
    }
}
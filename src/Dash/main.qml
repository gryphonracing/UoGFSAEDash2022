import QtQuick
import QtQuick.Controls
import CAN.MotorController
import CAN.BMS

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "GRC Dash"
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
        function onNewVoltage(voltage) {
            battery_voltage_text.text = `Battery Voltage: ${voltage.toFixed(1)}`
        }
        function onNewBatteryPercent(percent) {
            battery_percent_text.text = `Battery %: ${percent.toFixed(1)}`
        }
    }
}
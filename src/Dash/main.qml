import QtQuick
import QtQuick.Controls
import CAN.MotorController

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: "GRC Dash"
    Rectangle {
        anchors.fill: parent
        color: "Green"
    }
    Connections {
        target: MotorController
        onNewRPM: (rpm) => {
            console.log("RPM:", rpm)
        }
        onNewCoolantTemp: (coolant_temp) => {
            console.log("Coolant Temp:", coolant_temp.toFixed(1))
        }
        onNewOilTemp: (oil_temp) => {
            console.log("Oil Temp", oil_temp.toFixed(1))
        }
    }
}
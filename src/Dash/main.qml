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

    MotorController.onNewRPM: (rpm) => {
        console.log(rpm);
    }
}
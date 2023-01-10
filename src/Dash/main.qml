import QtQuick
import QtQuick.Controls

ApplicationWindow {
  id: application_window
  visible: true
  width: 800
  height: width * 10/16
  title: "GRC Dash"
  color: "white"
  maximumHeight: height
  maximumWidth: width
  minimumHeight: height
  minimumWidth: width
  flags: Qt.Window // | Qt.FramelessWindowHint add when final project is reached.


  Loader {
    source: "Drive.qml"
    anchors.fill: parent
  }
}
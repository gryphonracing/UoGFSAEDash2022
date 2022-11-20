import QtQuick
import QtQuick.Controls
import CAN.MotorController
import CAN.BMS

ApplicationWindow {
  id: application_window
  visible: true
  width: 800
  height: 480
  color: background_color
  title: "GRC Dash"

  property var border_width: 5

  property var background_color: String("#000000")
  property var box_color: String("#080808")
  property var text_color: String("#FFFFFF")

  Rectangle {
    id: main
    width: parent.width - border_width
    height: parent.height - border_width
    anchors {
      centerIn: parent
    }

    // BATTERY PERCENT
    Rectangle {
      id: battery_percent
      width: parent.width / 5
      height: parent.height / 3
      anchors {
        top: main.top
        left: main.left
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: battery_percent_text
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }

    // OIL TEMP
    Rectangle {
      id: oil_temp
      width: parent.width / 5
      height: parent.height / 3
      anchors {
        top: battery_percent.bottom
        left: main.left
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: oil_temp_text
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }

    // COOLANT TEMP
    Rectangle {
      id: coolant_temp
      width: parent.width / 5
      height: parent.height / 3
      anchors {
        top: oil_temp.bottom
        left: main.left
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: coolant_temp_text
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }

    // BATTERY BAR
    Rectangle {
      id: battery_bar
      width: 3 * parent.width / 5
      height: parent.height / 4
      anchors {
        top: main.top
        left: battery_percent.right
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: battery_voltage_text
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }

    // SPEEDOMETER
    Rectangle {
      id: speedometer
      width: 3 * parent.width / 5
      height: 3 * parent.height / 4
      anchors {
        top: battery_bar.bottom
        left: battery_percent.right
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: rpm_text
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }

    // GEAR MODE
    Rectangle {
      id: gear_mode
      width: parent.width / 5
      height: parent.height / 3
      anchors {
        top: main.top
        left: battery_bar.right
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: gear_mode_text
        text: "gear_mode"
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }

    // ACCUMULATOR TEMP
    Rectangle {
      id: accumulator_temp
      width: parent.width / 5
      height: parent.height / 3
      anchors {
        top: gear_mode.bottom
        left: battery_bar.right
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: accumulator_temp_text
        text: "accumulator_temp"
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }

    // MOTOR TEMP
    Rectangle {
      id: motor_temp
      width: parent.width / 5
      height: parent.height / 3
      anchors {
        top: accumulator_temp.bottom
        left: battery_bar.right
      }
      border {
        width: border_width
        color: background_color
      }
      color: box_color

      Text {
        id: motor_temp_text
        text: "motor_temp"
        anchors {
          centerIn: parent
        }
        color: text_color
      }
    }
  }

  Connections {
    target: MotorController
    function onNewRPM(rpm)
    {
      rpm_text.text = `RPM: ${rpm}`
    }
    function onNewCoolantTemp(coolant_temp)
    {
      coolant_temp_text.text = `Coolant Temp: ${coolant_temp.toFixed(1)}`
    }
    function onNewOilTemp(oil_temp)
    {
      oil_temp_text.text = `Oil Temp: ${oil_temp.toFixed(1)}`
    }
  }

  Connections {
    target: BMS
    function onNewVoltage(voltage)
    {
      battery_voltage_text.text = `Battery Voltage: ${voltage.toFixed(1)}`
    }
    function onNewBatteryPercent(percent)
    {
      battery_percent_text.text = `Battery %: ${percent.toFixed(1)}`
    }
  }
}
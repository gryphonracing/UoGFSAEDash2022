import QtQuick
import QtQuick.Controls
import CAN.MotorController
import CAN.BMS

ApplicationWindow {
  id: application_window
  visible: true
  width: 800
  height: width * 10 / 16
  title: "GRC Dash"

  Rectangle {
    id: main
    width: parent.width
    height: parent.height
    anchors{
      fill: parent
    }
    color: "blue"

    //Div contains the speedometer, battery% and gear
    Rectangle {
      id: speed_div
      color: "black"
      width: parent.height
      height: parent.height
      anchors{
        top: parent.top
        bottom: parent.bottom
        left: parent.left
      }

      //Speedometer needle
      Dial {
        id: control
        height: parent.height*.95
        width:height
        anchors{
          centerIn: speedometer_image
        }
        y:20
        background: Rectangle {
          x: control.width / 2 - width / 2
          y: control.height / 2 - height / 2
          width: Math.max(64, Math.min(control.width, control.height))
          height: width
          color: "transparent"
          radius: width / 2
          border.color: "transparent"
        }
        handle: Rectangle {
          x: control.background.x + control.background.width / 2 - width / 2
          y: control.background.y + control.background.height / 2 - height / 2
          width: parent.width/80 + control.value*10
          height: parent.width/10 + control.value*100
          radius: parent.width/100
          antialiasing: true
          color: "red"
          transform: [
            Translate {
              y: -Math.min(control.background.width, control.background.height) * 0.45 + control.handle.height / 2
            },
            Rotation {
              angle: control.angle
              origin.x: control.handle.width / 2
              origin.y: control.handle.height / 2
            }
          ]
        }
      }

      //Speedometer
      Image {
        id: speedometer_image
        source: "/images/Speedometer"
        height:parent.height*.95
        width: height
        anchors{
          horizontalCenter: speed_div.horizontalCenter
          margins:20
        }
      }

      //Speedometer text display
      Text {
        id: rpm_text_text
        font.pointSize: main.height/5
        opacity: 0.9
        font.bold: true
        font.family: "serif"
        color:"white"
        text: ""
        anchors{
          verticalCenter:parent.verticalCenter
          horizontalCenter: parent.horizontalCenter
        }
      }

      // //Battery image
      // Image {
      //   id: battery_image
      //   source: "images/Battery"
      //   anchors{
      //     bottom:parent.bottom
      //     left: parent.left
      //     right: parent.horizontalCenter
      //     top:speedometer_image.bottom
      //     topMargin: -.10*parent.height
      //     margins: 10
      //     rightMargin: 40
      //   }
      // }
      Rectangle {
        color: "white"
        height:main.height/5
        radius:height/10
        anchors{
          bottom: parent.bottom
          left:parent.left
          right:parent.horizontalCenter
          margins:10
        }

        Rectangle {
          color: "black"
          radius:height/12
          anchors{
            top: parent.top
            bottom: parent.bottom
            left:parent.left
            right:parent.right
            margins:5
          }

          Rectangle {
            id: battery_bar
            color: "green"
            radius:height/14
            width: 20
            anchors{
              top: parent.top
              bottom: parent.bottom
              left:parent.left
              margins:5
            }
          }

          Image{
            source: "images/BatterySymbol"
            height: 20
            anchors{
              bottom: parent.bottom
              left: parent.left
            }
          }
        }


      }

      //Battery reading
      Rectangle{
        color: "orange"
        anchors{
          fill: battery_image
          leftMargin: 17
          rightMargin: 35
          topMargin: 13
          bottomMargin: 13
        }
        radius: 10
      }
    }

    /**
    Text {
      id: gear_mode_text_text
      font.pointSize: 20
      text: "Gear Mode:"
    }
    */

    //Div contains all temperature related info
    Rectangle {
      id: temps
      anchors {
        top: parent.top
        right: parent.right
        left: speed_div.right
        margins: 10
      }
      color: "blue"
      width: 10
      height: parent.height-20

      Rectangle {
        id: motor_temp_div
        anchors {
          top: parent.top
          left: parent.left
          right: parent.right
          margins: 10
        }
        height: (parent.height-60)/5
        color: "yellow"

        Text {
          id: motor_temp_text_text
          font.pointSize: 20
          text: "Motor Temp: NUM°"
          anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }

      Rectangle {
        id: acumm_max_temp
        anchors {
          top: motor_temp_div.bottom
          left: parent.left
          right: parent.right
          margins: 10
        }
        height: (parent.height-60)/5
        color: "yellow"

        Text {
          id: max_accum_temp_text_text
          font.pointSize: 15
          text: "Acumm Max Temp: NUM°"
          anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }

      Rectangle {
        id: oil_temp_div
        anchors {
          top: acumm_max_temp.bottom
          right: parent.right
          left: parent.left
          margins: 10
        }
        height: (parent.height-60)/5
        color: "yellow"

        Text {
          id: oil_temp_text
          font.pointSize: 20
          text: ""
          anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }

      Rectangle {
        id: coolant_temp_div
        anchors {
          top: oil_temp_div.bottom
          right: parent.right
          left: parent.left
          margins: 10
        }
        height: (parent.height-60)/5
        color: "yellow"

        Text {
          id: coolant_temp_text
          font.pointSize: 20
          text: ""
          anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }

      Rectangle {
        id: battery_percent_div
        anchors {
          top: coolant_temp_div.bottom
          right: parent.right
          left: parent.left
          bottom: parent.bottom
          margins: 10
        }
        height: (parent.height-60)/5
        color: "yellow"

        Text {
          id: battery_percent_text
          font.pointSize: 20
          text: ""
          anchors{
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }
    }
  }

  Connections {
    target: MotorController
    function onNewRPM(rpm)
    {
      var speed = 160+rpm%160                    //Speed in km/h is calculated here
      var maxSpeed = 160
      var minSpeedometerNeedle = 0.072
      var maxSpeedometerNeedle = 0.928
      var changePerKMHR = (maxSpeedometerNeedle-minSpeedometerNeedle)/maxSpeed

      rpm_text_text.text = `${speed}`                                //Text display of speed
      control.value = minSpeedometerNeedle + speed*changePerKMHR     //Needle angle control
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
    function onNewBatteryPercent(percent)
    {
      battery_percent_text.text = `Battery: ${percent.toFixed(1)}%`
      battery_bar.width = 210/100*percent

      if (percent >= (200/3))
      {
        battery_bar.color = "green"
      }
      else if (percent >= 100/3)
      {
        battery_bar.color = "yellow"
      }
      else
      {
        battery_bar.color = "red"
      }
    }
  }
}
import QtQuick
import QtQuick.Controls
import CAN.MotorController
import CAN.BMS

ApplicationWindow {
  id: application_window
    visible: true
    width: 800
    height: 480
    title: "GRC Dash"
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    flags: Qt.Window // | Qt.FramelessWindowHint add when final project is reached.


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

      //Battery
      Rectangle {
        color: "white"
        height:main.height/5
        radius:height/10
        anchors{
          bottom: parent.bottom
          left:parent.left
          right:parent.right
          margins:20
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
            anchors{
              top: parent.top
              bottom: parent.bottom
              left:parent.left
              margins:5
            }
          }

          Image{
            source: "images/BatterySymbol"
            width: 20
            height: 2*width
            anchors{
              bottom: parent.bottom
              left: parent.left
              margins:10
            }
          }
        }


      }
    }

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
    function onNewMotorRPM(rpm)
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
    function onNewMotorTemp(temp) {
    }
    function onNew12VVoltage(voltage) {
    }
  }

  Connections {
    target: BMS
    function onNewAccumulatorSOC(percent)
    {
      battery_percent_text.text = `Battery: ${percent.toFixed(1)}%`
      battery_bar.width = (battery_bar.parent.width-10)/100*percent

      if (percent >= (100/3))
      {
        battery_bar.color = "green"
      }
      else
      {
        battery_bar.color = "red"
      }
    }
        function onNewBMSTemp(temp) {
        }
        function onNewAccumulatorMaxTemp(temp) {
        }
        function onNewAccumulatorCurrent(current) {
        }
        function onNewAccumulatorInstVoltage(voltage) {
        }
        function onNewAccumulatorOpenVoltage(voltage) {            
        }
  }
}
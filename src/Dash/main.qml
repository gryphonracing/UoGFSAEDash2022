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

    //Oil and Coolant
    Rectangle{
      id:oilAndCoolantDiv
      width: parent.width/16*4.5
      height: parent.height
      anchors{
        left: parent.left
        top: battery.bottom
        bottom: parent.bottom
      }
      color: "white"

      //Oil Temp Div
      Rectangle{
        anchors{
          top:parent.top
          bottom: parent.verticalCenter
          left: parent.left
          right: parent.right
        }
        color: "white"

        //Oil Temp Text
        Text{
          id: oilTempText
          font.pointSize: main.height/20
          text:"Oil Temp"
          color: "black"
          font.bold: true
          anchors{
            bottom: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
        //Oil Temp Value
        Text {
          id: oilTempValue
          font.pointSize: main.height/10
          text: ""
          color: "black"
          font.bold: true
          anchors{
            top: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }

      //Coolant Temp Div
      Rectangle{
        color: "white"
        anchors{
          top: parent.verticalCenter
          bottom:parent.bottom
          left: parent.left
          right: parent.right
        }

        //Coolant Temp Text
        Text{
          id: coolantTempText
          font.pointSize: main.height/25
          text:"Coolant Temp"
          color: "black"
          font.bold: true
          anchors{
            bottom: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
        //Coolant Temp Value
        Text {
          id: coolantTempValue
          font.pointSize: main.height/10
          text: ""
          color: "black"
          font.bold: true
          anchors{
            top: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }
    }

    //Accum and Motor
    Rectangle{
      id:accumAndMotorDiv
      width: parent.width/16*4.5
      height: parent.height
      anchors{
        right: parent.right
        top: battery.bottom
        bottom: parent.bottom
      }
      color: "yellow"

      //Accum Temp Div
      Rectangle{
        anchors{
          top:parent.top
          bottom: parent.verticalCenter
          right: parent.right
          left: parent.left
        }


        //accum Temp Text
        Text{
          id: accumTempText
          font.pointSize: main.height/25
          text:"Coolant Temp"
          color: "black"
          font.bold: true
          anchors{
            bottom: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
        //accum Temp Value
        Text {
          id: accumTempValue
          font.pointSize: main.height/10
          text: ""
          color: "black"
          font.bold: true
          anchors{
            top: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }


      }

      //Motor Temp Div
      Rectangle{
        anchors{
          top: parent.verticalCenter
          bottom:parent.bottom
          right: parent.right
          left: parent.left
        }

        //Motor Temp Text
        Text{
          id: motorTempText
          font.pointSize: main.height/25
          text:"Coolant Temp"
          color: "black"
          font.bold: true
          anchors{
            bottom: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
        //Motor Temp Value
        Text {
          id: motorTempValue
          font.pointSize: main.height/10
          text: ""
          color: "black"
          font.bold: true
          anchors{
            top: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
          }
        }
      }
    }

    //Speed
    Rectangle{
      id: speedDiv
      width: parent.width/16*8
      height: parent.height
      anchors{
        top: battery.bottom
        bottom: parent.bottom
        right: accumAndMotorDiv.left
        left: oilAndCoolantDiv.right
      }
      color: "white"


      Text {
        id: speedValue
        font.pointSize: main.height/4
        opacity: 0.9
        font.bold: true
        color:"black"
        text: ""
        anchors{
          verticalCenter:parent.verticalCenter
          horizontalCenter: parent.horizontalCenter
        }
      }

      Text {
        text: "kmph"
        font.bold: true
        color:"black"
        font.pointSize: main.height/15
        anchors{
          top:speedValue.bottom
          horizontalCenter: speedValue.horizontalCenter
          topMargin: - main.height/15
        }
      }

    }

    //Logo
    Image{
      id: logo
      source:"images/Logo"
      height:width*0.3
      width:parent.width
      anchors{
        verticalCenter: battery.verticalCenter
        left: battery.right
        right: parent.right
        margins: 10
      }
    }

    //Battery
    Rectangle {
      id: battery
      color: battery_bar.color
      height:main.height/5
      radius:height/10
      width: main.width*10/16
      anchors{
        top: parent.top
        left:parent.left
        margins:10
      }

      //Battery inside border
      Rectangle {
        color: "white"
        radius:height/12
        anchors{
          top: parent.top
          bottom: parent.bottom
          left:parent.left
          right:parent.right
          margins:5
        }

        //Responsive battery display (changes width & color based on battery percentage)
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

        //Battery icon
        Image{
          id: batteryIcon
          source: "images/BatterySymbol"
          width: main.height/25
          height: 2*width
          anchors{
            bottom: parent.bottom
            left: parent.left
            margins:10
          }
        }

        //Battery text
        Text {
          id: battery_percent_text
          font.pointSize: main.height/25
          color: "black"
          font.bold: true
          text: ""
          anchors{
            verticalCenter: batteryIcon.verticalCenter
            left: batteryIcon.right
            margins: 10
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

      speedValue.text = `${speed}`                                //Text display of speed
    }
    function onNewCoolantTemp(coolant_temp)
    {
      coolantTempValue.text = `${coolant_temp.toFixed(1)}`
    }
    function onNewOilTemp(oil_temp)
    {
      oilTempValue.text = `${oil_temp.toFixed(1)}`
    }
    function onNewMotorTemp(temp)
    {
      motorTempValue.text = `${temp.toFixed(1)}`
    }
    function onNew12VVoltage(voltage)
    {
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
    function onNewBMSTemp(temp)
    {
    }
    function onNewAccumulatorMaxTemp(temp)
    {
      accumTempValue.text = `${temp.toFixed(1)}`
    }
    function onNewAccumulatorCurrent(current)
    {
    }
    function onNewAccumulatorInstVoltage(voltage)
    {
    }
    function onNewAccumulatorOpenVoltage(voltage)
    {
    }
  }
}
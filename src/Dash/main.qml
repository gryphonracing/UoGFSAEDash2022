import QtQuick
import QtQuick.Controls
import CAN.MotorController
import CAN.BMS
import CAN.EnergyMeter

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


  Rectangle {
    id: main
    width: parent.width
    height: parent.height
    anchors{
      fill: parent
      margins: main.height/30
    }
    color: "white"

    //Oil and Coolant
    Rectangle{
      id:oilAndCoolantDiv
      width: parent.width/16*5
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
          font.pointSize: main.height/8
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
          font.pointSize: main.height/20
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
          font.pointSize: main.height/8
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
      width: parent.width/16*5
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
          font.pointSize: main.height/20
          text:"Accum Temp"
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
          font.pointSize: main.height/8
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
          font.pointSize: main.height/20
          text:"Motor Temp"
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
          font.pointSize: main.height/8
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
      width: parent.width/16*6
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
        font.pointSize: main.height/3.5
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
    function onNewMotorRPM(motor_rpm)
    {
        console.log(motor_rpm)
      const gear_ratio = 3.48/1; // 3.48:1 gear ratio
      const wheel_circumfrence = 1.2767; // 16" OD of wheel -> ~1.28 meter circumfrence
      let axle_rpm = motor_rpm / gear_ratio; // axle rotations per minute
      let wheel_mpm = wheel_circumfrence * axle_rpm // Wheel speed in meters per second
      let wheel_mph = wheel_mpm * 60; // Meters per hour
      let wheel_kmph = wheel_mph / 1000; // km per hour
      speedValue.text = `${wheel_kmph.toFixed(0)}` //Text display of speed
    }
    function onNewCoolantTemp(coolant_temp)
    {
      //Getting positive values within the right range
      
      coolantTempValue.text = `${coolant_temp.toFixed(1)}`

      //Color coding value ranges
      if (coolant_temp < 90)
      {
        coolantTempValue.color="blue"
      }
      else if(coolant_temp > 120)
      {
        coolantTempValue.color="red"
      }
      else {
        coolantTempValue.color="green"
      }
    }
    function onNewOilTemp(oil_temp)
    {

      oilTempValue.text = `${oil_temp.toFixed(1)}`

      //Color coding value ranges
      if (oil_temp < 90)
      {
        oilTempValue.color="blue"
      }
      else if(oil_temp > 120)
      {
        oilTempValue.color="red"
      }
      else {
        oilTempValue.color="green"
      }

    }
    function onNewMotorTemp(temp)
    {
      //Getting positive values within the right range

      motorTempValue.text = `${temp.toFixed(1)}`

      //Color coding value ranges
      if (temp < 90)
      {
        motorTempValue.color="blue"
      }
      else if(temp > 120)
      {
        motorTempValue.color="red"
      }
      else {
        motorTempValue.color="green"
      }

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

      //Color coding value ranges
      if (temp < 90)
      {
        accumTempValue.color="blue"
      }
      else if(temp > 120)
      {
        accumTempValue.color="red"
      }
      else {
        accumTempValue.color="green"
      }
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
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
      anchors{
          fill: parent
      }
      color: "black"

     
      Rectangle {
        id: speed_div
        color: "blue"
        height: width
        anchors{
          top: parent.top
          bottom: parent.bottom
          left: parent.left
          right: temps.left
          margins: 10
        }

        Canvas {
          width: parent.width
          height: parent.height
          onPaint: {
            var context = getContext("2d");
            context.reset();
            var x = parent.width/2-1
            var y = parent.height/2+49
            var radius = width/2-40
            context.arc(x, y, radius, 2.61799, -.9);
            context.strokeStyle = "red";
            context.lineWidth = 25;
            context.stroke();
          }
        }
        Dial {
          
        }
        Image {
          source: "SpeedometerSemiCircle.png"
          height:parent.height
          width: parent.width
        }
        Text {
          id: rpm_text_text
          font.pointSize: 20
          text: ""
          anchors{
            centerIn: parent  
          }
        }  
      }
        
      Text {
        id: gear_mode_text_text
        font.pointSize: 20
        text: "Gear Mode:"
      }
        
      

      Rectangle {
        id: temps
        anchors {
          top: parent.top
          right: parent.right
          margins: 10
        }
        color: "blue"
        height: parent.height-20
        width: (parent.width*7/16)-15
      
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
        function onNewRPM(rpm) {
            rpm_text_text.text = `RPM/Speed: ${rpm}`
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
        function onNewBatteryPercent(percent) {
            battery_percent_text.text = `Battery: ${percent.toFixed(1)}%`
        }
    }
}
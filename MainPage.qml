import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.1
import QtQuick.Dialogs 1.1
import CustomControls 1.0

Item {

    id: mainPage


    GridView{
        id: gaugeGridView
        anchors.fill: parent
        model: gaugeList
        cellHeight: parent.height
        cellWidth: parent.width /3
        delegate: Rectangle{
            width: gaugeGridView.cellWidth
            height: gaugeGridView.cellHeight
            color: "#666666"
            border.color: "#000000"
            border.width: 2

            Text {

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 10
                anchors.topMargin: 10
                font.pointSize: 13
                color: "#ffffff"
                text: name
            }

            RadialBar{
                id: pressureGauge
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 1.4
                height: parent.height
                penStyle: Qt.RoundCap
                progressColor: "#333333"
                foregroundColor: "#333333"
                dialWidth: 12
                minValue: 0
                maxValue: 100
                value: theValue
                suffixText: "°C"
                textFont {
                    family: "Helvetica"
                    italic: false
                    pointSize: 18
                }
                textColor: "cyan"
                state: theState
                states:[

                    State{
                        name: "enabled"
                        PropertyChanges {
                            target: pressureGauge;
                            progressColor:"#5AFF29"
                            textColor: "#5AFF29"
                        }
                        PropertyChanges {
                            target: button;
                            enabled: true
                        }
                    },
                    State{
                        name: "disabled"
                        PropertyChanges {
                            target: pressureGauge;
                            progressColor: "#333333"
                            textColor: "#333333"
                            value: -100
                        }
                        PropertyChanges {
                            target: button;
                            enabled: false
                        }
                    }
                ]

                onValueChanged:
                {
                    pressureGauge.update()
                }
            }
            MouseArea{
                id: button
                anchors.fill: parent

                onClicked: {
                    console.log("Clicked")

                    mainStackView.push(Qt.resolvedUrl("GaugePage.qml"), {schannel : chID})
                }
            }
        }

    }

    ListModel{
        id: gaugeList
        ListElement{
            name: "CH1"
            chID: 0
            theValue: -50
            theState: "enabled"

        }
        ListElement{
            name: "CH2"
            chID: 1
            theValue: -70.2
            theState: "enabled"

        }
        ListElement{
            name: "CH3"
            chID: 2
            theValue: -50.1
            theState: "disabled"

        }
    }

    Timer
    {
        id: checkGaugeEnableTimer
        interval: 1000
        triggeredOnStart: true
        repeat: true
        running: true

        onTriggered:
        {

            for(var i = 0; i < 3; i++)
            {
                // check gauge enable status
                if(flipperSetting.isthisChannelEnable(i+1))
                {
                    gaugeList.get(i).theState = "enabled";

                }
                else
                {
                    gaugeList.get(i).theState = "disabled"
                }
            }

            // check AutoStart

        }
    }

    Timer
    {
        id: initShitTimer
        interval: 100
        repeat: false
        running: true
        onTriggered:
        {
            for(var i = 0; i < 3; i++)
            {
                theGuiInterface.requestUpdateGauge(i)
                theGuiInterface.requestUpdateChart(i,3000);
            }
        }
    }

    Timer
    {
        id:  checkNewDataTimer
        interval: 20000
        triggeredOnStart: true
        repeat: true
        running: theGuiInterface.isRecording
        onTriggered: {
            for(var i = 0; i < 3; i++)
            {
                if(theGuiInterface.isRecording)
                {
                    // get new Data if gauge enable
                    if(flipperSetting.isthisChannelEnable(i+1))
                    {

                        gaugeList.get(i).theValue = theGuiInterface.getlastgaugeValue(i)
                    }
                }

            }
        }
    }

}

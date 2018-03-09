import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.1
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Material 2.1
import MouseEventSpy 1.0

ApplicationWindow {
    id: stationPage
    visible: true
    width: 800
    height: 480
    title: qsTr("Flipper DewPoint Monitoring")

    Connections
    {
        target: MouseEventSpy
        onMouseEventDetected:
        {
            lockScreenTimer.restart()
//            console.log("event detected")
        }

    }

    header: ToolBar{
        id:theToolBar
        width: parent.width
        height: {

            if(mainStackView.currentItem.objectName != "loginPage")
            {
                50
            }
            else
                0
        }
        opacity:{

            if(mainStackView.currentItem.objectName != "loginPage")
            {
                1
            }
            else
                0
        }


        Rectangle {
            color: "transparent"
            anchors.fill: parent
        }

        Text {
            id: textClock
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 15
            anchors.top: parent.top
            font.bold: true
            font.pixelSize: 20
            color: "#666666"
        }
        Timer
        {

            id: clockTimer
            interval: 30000
            repeat: true
            triggeredOnStart: true
            running: true
            onTriggered: {
                textClock.text = new Date().toDateString() +" - " + new Date().toLocaleTimeString("H:mm")
            }

        }

        RowLayout
        {
            anchors.fill: parent
            Rectangle {
                id: backButton
                width: opacity ? 50 : 0
                anchors.left: parent.left
                anchors.leftMargin: 20
                opacity: mainStackView.depth > 2 ? 1 : 0
                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                height: 50
                radius: 4
                color: backmouse.pressed ? "#222" : "transparent"
                Behavior on opacity { NumberAnimation{} }
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/back.png"

                }
                MouseArea {
                    id: backmouse
                    enabled: mainStackView.depth > 2 ? true : false
                    anchors.fill: parent
                    anchors.margins: -10
                    onClicked: mainStackView.pop()
                }
            }
            Rectangle{
                id: serverStatusIcon
                width: 50
                height: 50
                anchors.left: parent.left
                anchors.leftMargin: 100
                opacity: mainStackView.depth >= 1 ? 1:0
                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                color: "transparent"
                Image {
                    id: serverStatusIconImage
                    source: {
                        if(theGuiInterface.isServerOnline)
                        {
                            "images/serverOnline.png"
                        }
                        else
                        {
                            "images/serverOffline.png"
                        }
                    }

                    scale: 0.9
                }
            }

            Rectangle{
                id: flipperStatusIcon
                width: 50
                height: 50
                anchors.left: parent.left
                anchors.leftMargin: 150
                opacity: mainStackView.depth >= 1 ? 1:0
                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                color: "transparent"
                Image {
                    id: flipperStatusIconImage
                    source:{
                        if(theGuiInterface.isFlipperOnline)
                        {
                            "images/flipperOnline.png"
                        }
                        else
                        {
                            "images/flipperOffline.png"
                        }
                    }

                    scale: 0.9
                }
            }


            Rectangle{
                id: recordButton
                width: opacity ? 50 : 0
                anchors.left: parent.left
                anchors.leftMargin: 200
                opacity: mainStackView.depth >= 1 ? 1 : 0
                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                height: 50
                radius: 4
                color: recordMouse.pressed ? "#222" : "transparent"
                Image {
                    id: recordImage
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/record.png"
                    scale: 0.9


                }
                MouseArea {
                    id: recordMouse
                    enabled:  mainStackView.depth >= 1 ? 1 : 0
                    anchors.fill: parent
                    anchors.margins: -10
                    onClicked:
                    {

                        if (theGuiInterface.isRecording === false)
                        {
                            theGuiInterface.isRecording = true
                            recordImage.source = "images/record-active.png"
                            flashingAnimattion.start()
                            theGuiInterface.setFlipperEnableChannel(flipperSetting.getChannelEnable())
                            theGuiInterface.setFLipperTCPAddress(flipperSetting.getFlipperIp(), flipperSetting.getFlipperPort(), flipperSetting.getSVAddress())
                            theGuiInterface.startRecording()

                            return
                        }
                        else
                        {
                            theGuiInterface.isRecording = false
                            theGuiInterface.stopRecording()
                            recordImage.source = "images/record.png"
                            flashingAnimattion.stop()
                            recordImage.opacity = 1;
                        }
                    }
                }

                SequentialAnimation {
                    id: flashingAnimattion
                    loops: Animation.Infinite
                    running: false
                    NumberAnimation{
                        target: recordImage
                        properties: "opacity"
                        from: 0
                        to: 1
                        easing.type:Easing.OutExpo
                        duration: 500
                    }
                    NumberAnimation
                    {
                        target: recordImage
                        properties: "opacity"
                        from: 1
                        to: 0
                        easing.type: Easing.OutBounce
                        duration: 500
                    }
                }

            }

            Rectangle {
                id: settingButton
                width: opacity ? 50 : 0
                anchors.right: parent.right
                anchors.rightMargin: 70
                opacity:
                {
                    //                     mainStackView.depth >= 1 ? 1 : 0
                    if(mainStackView.depth >= 1 && mainStackView.currentItem.objectName != "SettingPage")
                    {
                        1
                    }
                    else
                        0
                }

                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                height: 50
                radius: 4
                color: settingMouse.pressed ? "#222" : "transparent"

                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/setting.png"
                    scale: 0.9

                }
                MouseArea {
                    id: settingMouse
                    enabled:  mainStackView.depth >= 1 ? 1 : 0
                    anchors.fill: parent
                    anchors.margins: -10
                    onClicked: {
                        mainStackView.push(Qt.resolvedUrl("SettingPage.qml"))
                    }

                }
            }

            Rectangle {
                id: lockButton
                width: opacity ? 50 : 0
                anchors.right: parent.right
                anchors.rightMargin: 20
                opacity: mainStackView.depth >= 1 ? 1 : 0
                anchors.verticalCenter: parent.verticalCenter
                antialiasing: true
                height: 50
                radius: 4
                color: lockMouse.pressed ? "#222" : "transparent"
                Behavior on opacity { NumberAnimation{} }
                Image {
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/lock.png"
                    scale: 0.9

                }
                MouseArea {
                    id: lockMouse
                    enabled:  mainStackView.depth >= 1 ? 1 : 0
                    anchors.fill: parent
                    anchors.margins: -10
                    onClicked: {
                        mainStackView.push(Qt.resolvedUrl("LogInPage.qml"))
                    }
                }
            }
        }
    }

    StackView{
        id: mainStackView
        anchors.fill: parent

        focus:true
        initialItem: LogInPage
        {
            id: mainPage
        }

        pushEnter: Transition {
            OpacityAnimator {
                target: mainStackView;
                from: 0.8;
                to: 1;
                duration: 500
                running: true
            }
        }
        pushExit: Transition {

        }



        popEnter: Transition {
            OpacityAnimator {
                target: mainStackView;
                from: 0.8;
                to: 1;
                duration: 500
                running: true
            }
        }

        popExit: Transition {

        }
    }


    Timer
    {
        id: checkAutoStartTimer
        interval: 500
        triggeredOnStart: true
        repeat: false
        running: true

        onTriggered:
        {

            if(flipperSetting.isAutoStart())
            {
                if(!theGuiInterface.isRecording)
                {
                    theGuiInterface.isRecording = true
                    recordImage.source = "images/record-active.png"
                    flashingAnimattion.start()
                    theGuiInterface.setFlipperEnableChannel(flipperSetting.getChannelEnable())
                    theGuiInterface.setFLipperTCPAddress(flipperSetting.getFlipperIp(), flipperSetting.getFlipperPort(), flipperSetting.getSVAddress())
                    theGuiInterface.startRecording()
                }
            }
            // check AutoStart

        }
    }

    Timer
    {
        id: lockScreenTimer
        interval: 300000
        triggeredOnStart: false
        repeat: true
        running: true
        onTriggered:
        {
            if(mainStackView.currentItem.objectName != "loginPage")
            {
                mainStackView.push(Qt.resolvedUrl("LogInPage.qml"))
            }
        }
    }


}


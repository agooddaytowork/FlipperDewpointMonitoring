import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import CustomControls 1.0
import QtQuick.VirtualKeyboard 2.1
import QtQuick.Window 2.2


Item
{

    objectName: "SettingPage"
    Flickable
    {
        id: flickable
        anchors.fill: parent
        contentHeight:pane.height
        flickableDirection:  Flickable.VerticalFlick
        ScrollBar.vertical: ScrollBar { }
        property int initialY: 0
        Pane{
            id: pane
            width: flickable.width
            height: flickable.height*2.7

            Column{
                id: column
                anchors.fill: parent
                spacing: 10

                Rectangle
                {
                    width: parent.width
                    height: 180
                    radius: 10
                    color: "#ffffff"
                    border.color: "black"
                    border.width: 2

                    GridLayout
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        rows:3
                        columns: 2
                        columnSpacing: 10
                        rowSpacing: 10

                        Text {

                            text: qsTr("Depot Name:")
                        }

                        TextField
                        {
                            id:  depotNameTextField
                            text: flipperSetting.getDepotName();

                            onActiveFocusChanged: {
                                if(activeFocus)
                                {
                                    var posWithinFlickable = mapToItem(column, 0, height / 2);
                                    flickable.contentY = (posWithinFlickable.y - flickable.height / 2) +100;
                                }
                            }

                            onTextChanged:
                            {
                                flipperSetting.updateFlipperSetting("DeviceName", depotNameTextField.text)
                            }
                        }


                        Text {

                            text: qsTr("Device MAC: ")
                        }
                        Text {
                            id: macAddressText
                            text: flipperSetting.getEth0MacAddress()
                        }

                        Button
                        {
                            id: changePWButton
                            text: "Change Password"

                            onClicked:
                            {
                                changePasswordDialog.open()
                            }

                            Dialog{
                                id: changePasswordDialog
                                x: (flickable.width - changePasswordDialog.width) /2
                                y:(flickable.height - changePasswordDialog.height) /2 -200
                                z:1
                                height: 240
                                parent: flickable
                                modal: false
                                closePolicy: Dialog.CloseOnEscape
                                Column
                                {
                                    spacing: 20
                                    anchors.fill: parent

                                    TextField
                                    {
                                        id: currentPasswordTextField
                                        echoMode:  TextInput.Password
                                        inputMethodHints:  Qt.ImhDigitsOnly
                                        placeholderText: "Enter Current Password"
                                    }

                                    Row
                                    {
                                        spacing: 20

                                        TextField{
                                            id: newPasswordTextField
                                            echoMode: TextInput.Password
                                            inputMethodHints:  Qt.ImhDigitsOnly
                                            placeholderText: "Enter New password"


                                        }

                                        TextField{
                                            id: confirmNewPassWordTextField
                                            echoMode: TextInput.Password
                                            inputMethodHints:  Qt.ImhDigitsOnly
                                            placeholderText: "ConfirmNewPassword"
                                        }


                                    }

                                    Row
                                    {
                                        spacing: 20

                                        Button
                                        {
                                            id: ackChangePasswordButton
                                            text: "OK"

                                            onClicked:
                                            {
                                                if(!currentPasswordTextField.text || !newPasswordTextField.text || !confirmNewPassWordTextField.text)
                                                {
                                                    changePasswordDialogStatusLabel.text = "Status: Please enter data to all fields"
                                                }
                                                else
                                                {
                                                    if(currentPasswordTextField.text !== flipperSetting.getLockScreenPassword())
                                                    {
                                                        changePasswordDialogStatusLabel.text = "Status: Current Password is not correct"
                                                    }
                                                    else
                                                    {
                                                        if(newPasswordTextField.text == confirmNewPassWordTextField.text)
                                                        {
                                                            // do something here

                                                            flipperSetting.updateFlipperSetting("lockScreenPassword", newPasswordTextField.text)

                                                            newPasswordTextField.text = ""
                                                            confirmNewPassWordTextField.text = ""
                                                            currentPasswordTextField.text = ""
                                                            changePasswordDialogStatusLabel.text = "Status: LockScreen Password is changed, Click Close return"

                                                        }
                                                        else
                                                        {
                                                            changePasswordDialogStatusLabel.text = "Status: Passwords do not match, please enter again"
                                                        }
                                                    }
                                                }


                                            }
                                        }
                                        Button
                                        {
                                            id: closeChangePassWordDialogButton
                                            text: "Close"
                                            onClicked:
                                            {
                                                changePasswordDialog.close()
                                            }
                                        }
                                    }


                                    Label
                                    {   id: changePasswordDialogStatusLabel
                                        text: "Status"
                                    }
                                }


                            }
                        }
                        CheckBox
                        {
                            id: autoStartCheckbox
                            text: "AutoStart"
                            checked:  flipperSetting.isAutoStart()
                            onCheckedChanged: {
                                flipperSetting.updateFlipperSetting("autoStart", autoStartCheckbox.checked)
                            }
                        }
                        Button
                        {
                            id: exitButton
                            text: "Exit Application"
                            onClicked:
                            {
                                Qt.quit()
                            }
                        }



                    }
                }

                Rectangle
                {
                    width: parent.width
                    height: 140
                    radius: 10
                    color: "#ffffff"
                    border.color: "black"
                    border.width: 2

                    // General settings go here
                    GridLayout{

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        rows: 4
                        columns: 4
                        columnSpacing: 10
                        rowSpacing: 10


                        Text {

                            text: qsTr("Flipper Address:")

                        }

                        TextField
                        {
                            id:  svAddressTextField
                            implicitWidth: 60
                            inputMethodHints:  Qt.ImhDigitsOnly
                            text: flipperSetting.getSVAddress()
                            enabled: !theGuiInterface.isRecording
                            onActiveFocusChanged: {
                                if(activeFocus)
                                {
                                    var posWithinFlickable = mapToItem(column, 0, height / 2);
                                    flickable.contentY = (posWithinFlickable.y - flickable.height / 2) +100;
                                }
                            }

                            onTextChanged:
                            {
                                flipperSetting.updateFlipperSetting("FlipperServerAddress", Number(svAddressTextField.text))
                            }
                        }

                        Text {

                            text: qsTr("Flipper IP:")
                        }
                        TextField
                        {
                            id:  ipTextField
                            inputMethodHints:  Qt.ImhDigitsOnly
                            text: flipperSetting.getFlipperIp()
                            enabled: !theGuiInterface.isRecording
                            onTextChanged:
                            {
                                flipperSetting.updateFlipperSetting("FlipperIP", ipTextField.text)
                            }

                        }
                        Text {

                            text: qsTr("Flipper Port:")

                        }
                        TextField
                        {
                            id:  portTextField
                            implicitWidth: 60
                            inputMethodHints:  Qt.ImhDigitsOnly

                            onActiveFocusChanged: {
                                if(activeFocus)
                                {
                                    var posWithinFlickable = mapToItem(column, 0, height / 2);
                                    flickable.contentY = (posWithinFlickable.y - flickable.height / 2) +100;
                                }
                            }
                            text: flipperSetting.getFlipperPort()
                            enabled: !theGuiInterface.isRecording
                            onTextChanged:
                            {
                                flipperSetting.updateFlipperSetting("FlipperPort",  Number(portTextField.text))
                            }
                        }
                    }
                }

                // Setup for stand alone mode
                Rectangle
                {
                    width: parent.width
                    height: 240
                    radius: 10
                    color: "#ffffff"
                    border.color: "black"
                    border.width: 2

                    GridLayout{
                        rows: 3
                        columns: 2
                        columnSpacing: 10
                        rowSpacing: 10

                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter


                        Text {

                            text: qsTr("Stand Alone Mode")

                        }

                        Row{
                            CheckBox
                            {
                                id: standAloneModeActiveCheckbox
                                text: "Activate"
                                checked: flipperSetting.isStandAloneMode()
                                onCheckedChanged: {
                                    flipperSetting.updateFlipperSetting("standAloneMode",  standAloneModeActiveCheckbox.checked)
                                }
                            }


                        }




                        TextField
                        {
                            id: emailTextField
                            placeholderText: "Email address"
                            inputMethodHints: Qt.ImhEmailCharactersOnly
                            onActiveFocusChanged: {
                                if(activeFocus)
                                {
                                    var posWithinFlickable = mapToItem(column, 0, height / 2);
                                    flickable.contentY = (posWithinFlickable.y - flickable.height / 2) +100;
                                }
                            }
                            text: flipperSetting.getNotificationMailAddress()
                            onTextChanged:
                            {
                                flipperSetting.updateFlipperSetting("NotificationMailAddress",  emailTextField.text)
                            }
                        }
                        TextField{
                            id: emailPassword
                            placeholderText: "Email password"
                            echoMode: TextInput.Password
                            onActiveFocusChanged: {
                                if(activeFocus)
                                {
                                    var posWithinFlickable = mapToItem(column, 0, height / 2);
                                    flickable.contentY = (posWithinFlickable.y - flickable.height / 2) +100;
                                }
                            }

                            text: flipperSetting.getNotificationMailAddress()
                            onTextChanged:
                            {
                                flipperSetting.updateFlipperSetting("NotificationMailPassword",  emailPassword.text)

                            }
                        }

                        CheckBox{
                            text: "Alert Notification"

                            checked: flipperSetting.isSendingAlertNotification()
                            onCheckedChanged: {
                                flipperSetting.updateFlipperSetting("sendAlertNotification", checked )
                            }
                        }

                        CheckBox{
                            text: "Daily Notification"
                            checked:  flipperSetting.isSendingDailyNotification()
                            onCheckedChanged: {

                                flipperSetting.updateFlipperSetting("sendDailyNotification", checked)
                            }
                        }

                        Row{
                            spacing: 10
                            ComboBox{
                                id: dayComboBox
                                model: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
                            }
                            ComboBox{
                                id: hour
                                model: 25
                            }
                        }

                        ComboBox{
                            id: minute
                            model: 61
                        }
                    }
                }

                // Setup for Server mode go here
                Rectangle
                {
                    width: parent.width
                    height: 120
                    radius: 10
                    color: "#ffffff"
                    border.color: "black"
                    border.width: 2
                    GridLayout{
                        rows: 2
                        columns: 5
                        columnSpacing: 10
                        rowSpacing: 10
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                        Text {

                            text: qsTr("Server Mode")
                        }

                        CheckBox
                        {
                            id: activeServerModeCheckBox
                            text: "Active"
                            checked: flipperSetting.isServerMode()
                            onCheckedChanged: {
                                flipperSetting.updateFlipperSetting("serverMode", checked)
                            }
                        }

                        TextField
                        {
                            id: serverLinkTextField
                            placeholderText: "Server link"
                            onActiveFocusChanged: {
                                if(activeFocus)
                                {
                                    var posWithinFlickable = mapToItem(column, 0, height / 2);
                                    flickable.contentY = (posWithinFlickable.y - flickable.height / 2) +100;
                                }
                            }

                            onTextChanged:
                            {

                            }
                        }
                        Button
                        {
                            id: testSVConnectionButton
                            text: "Test"
                        }
                    }
                }

                // Channel Setup go here

                GridLayout
                {
                    rows: 3
                    columns: 3
                    columnSpacing: 10
                    rowSpacing: 10


                    Repeater{
                        model: 3
                        Rectangle{
                            enabled: !theGuiInterface.isRecording
                            width: 250
                            height: 200
                            color: "#ffffff"
                            radius: 10
                            border.width: 2
                            border.color: "black"

                            Text {

                                text: qsTr("CH ") + (index + 1)
                                anchors.top: parent.top
                                anchors.left: parent.left
                                anchors.topMargin: 10
                                anchors.leftMargin: 10
                            }

                            ComboBox
                            {
                                anchors.top: parent.top
                                anchors.horizontalCenter:  parent.horizontalCenter
                                anchors.topMargin: 70
                                anchors.leftMargin: 25
                                model: [10,100,1000]
                                currentIndex: Math.round((Math.log(flipperSetting.getDecimalPoint(index +1))/Math.log(10)))-1

                                onHighlightedIndexChanged:
                                {


                                    flipperSetting.setDecimailPoint(index+1, parseInt(currentText))
                                }
                            }

                            TextField{
                                id: specTextField
                                anchors.top: parent.top
                                anchors.topMargin: 120
                                anchors.horizontalCenter:  parent.horizontalCenter

                                inputMethodHints:  Qt.ImhFormattedNumbersOnly
                                onActiveFocusChanged: {
                                    if(activeFocus)
                                    {
                                        var posWithinFlickable = mapToItem(pane, 0, height / 2);
                                        flickable.contentY = (posWithinFlickable.y - flickable.height / 2) +100;
                                    }
                                }
                                text: flipperSetting.getChannelOOSpec(index +1)


                                onTextChanged:
                                {

                                    flipperSetting.updateOOSpec(index +1, specTextField.text)

                                }
                            }

                            Switch
                            {
                                id: channelEnableSwitch
                                anchors.top: parent.top
                                anchors.topMargin: 5
                                anchors.right: parent.right
                                anchors.rightMargin: 20
                                checked: flipperSetting.isthisChannelEnable(index +1)

                                onCheckedChanged: {
                                    flipperSetting.setChannelEnable(index +1 , checked)
                                }
                            }
                        }
                    }
                }
            }

        }
//        Gradient {
//            id: channelOffGradient
//            GradientStop {
//                position: 0.0
//                SequentialAnimation on color {
//                    loops: Animation.Infinite
//                    ColorAnimation { from: "#14148c"; to: "#0E1533"; duration: 5000 }
//                    ColorAnimation { from: "#0E1533"; to: "#14148c"; duration: 5000 }
//                }
//            }
//            GradientStop {
//                position: 2.0
//                SequentialAnimation on color {
//                    loops: Animation.Infinite
//                    ColorAnimation { from: "#14aaff"; to: "#437284"; duration: 5000 }
//                    ColorAnimation { from: "#437284"; to: "#14aaff"; duration: 5000 }
//                }
//            }
//        }


//        Gradient {
//            id: channelOnGradient
//            GradientStop {
//                position: 1.0
//                SequentialAnimation on color {
//                    loops: Animation.Infinite
//                    ColorAnimation { from: "#4ba84c"; to: "#16dd18"; duration: 5000 }
//                    ColorAnimation { from: "#16dd18"; to: "#4ba84c"; duration: 5000 }

//                }
//            }

//            GradientStop {
//                position: 0.0
//                SequentialAnimation on color {
//                    loops: Animation.Infinite
//                    ColorAnimation { from: "#62a060"; to: "#2ea32a"; duration: 5000 }
//                    ColorAnimation { from: "#2ea32a"; to: "#62a060"; duration: 5000 }

//                }
//            }
//        }

        // KEYBOARD SECTIONS

    }
    InputPanel {
        id: inputPanel
        parent: ApplicationWindow.overlay
        z: 2
        y: Qt.inputMethod.visible ? (parent.height - inputPanel.height ) : parent.height
        anchors.left: parent.left
        anchors.right: parent.right
        visible: Qt.inputMethod.visible
    }
}



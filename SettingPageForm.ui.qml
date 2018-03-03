import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import QtQuick.Controls 2.2

Item {
    id: settingPage
    width: 800
    height: 480

    GridLayout {
        id: gridLayout
        anchors.fill: parent
        rows: 4
        columns: 4
    }
}

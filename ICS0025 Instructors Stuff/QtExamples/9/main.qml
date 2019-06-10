import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Button {
        id: exitButton
        text: "Exit"
        width: 80
        height: 25
        anchors.centerIn: parent
        onClicked: { Qt.quit(); }
    }
    Button {
        id: startButton
        text: "Start"
        width: 80
        height: 25
        anchors.bottom: exitButton.top
        anchors.left: exitButton.left
        anchors.bottomMargin: 20
    }
}

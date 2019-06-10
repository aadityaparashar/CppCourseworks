import QtQuick 2.4
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400
    property alias exitButton: exitButton
    property alias computeButton: computeButton
    property alias fieldResult: fieldResult
    property alias fieldUpper: fieldUpper
    property alias fieldLower: fieldLower

    ColumnLayout {
        id: formLayout
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.fill: parent

        GroupBox {
            id: dataGroup
            width: 200
            height: 200
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            title: qsTr("Data")

            GridLayout {
                id: dataLayout
                columnSpacing: 1
                anchors.rightMargin: 30
                anchors.leftMargin: 30
                anchors.fill: parent
                flow: GridLayout.LeftToRight
                rows: 3
                columns: 2

                Label {
                    id: labelLower
                    text: qsTr("Lower:")
                }

                TextField {
                    id: fieldLower
                    text: qsTr("0")
                }

                Label {
                    id: labelUpper
                    text: qsTr("Upper:")
                }

                TextField {
                    id: fieldUpper
                    text: qsTr("1000")
                }

                Label {
                    id: labelResult
                    text: qsTr("Result:")
                }

                TextField {
                    id: fieldResult
                    text: qsTr("")
                }
            }

        }

        GroupBox {
            id: operationsGroup
            width: 200
            height: 200
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            title: qsTr("Operations")

            GridLayout {
                id: operationsLayout
                columnSpacing: 20
                anchors.rightMargin: 60
                anchors.leftMargin: 60
                anchors.fill: parent
                rows: 1
                columns: 2

                Button {
                    id: computeButton
                    text: qsTr("Compute")
                }

                Button {
                    id: exitButton
                    text: qsTr("Exit")
                }
            }
        }

    }
}






/*##^## Designer {
    D{i:3;anchors_height:162;anchors_width:360;anchors_x:-12;anchors_y:-15}D{i:11;anchors_height:100;anchors_width:100}
}
 ##^##*/

import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Item {
    id: element
    width: 500
    height: 500
    property alias resultField: resultField
    property alias addButtom: addButtom
    property alias multiplyButton: multiplyButton
    property alias fieldX2: fieldX2
    property alias fieldX1: fieldX1
    property alias resetButton: resetButton
    property alias exitButton: exitButton

    ColumnLayout {
        id: formLayout
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.fill: parent

        GroupBox {
            id: initialData
            width: 200
            height: 69
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            title: qsTr("Initial data")

            GridLayout {
                id: initialDataLayout
                x: 30
                y: 0
                columns: 4
                anchors.rightMargin: 30
                anchors.leftMargin: 30
                anchors.fill: parent

                Label {
                    id: labelX1
                    text: qsTr("X1")
                }

                TextField {
                    id: fieldX1
                    text: qsTr("0")
                }

                Label {
                    id: labelX2
                    text: qsTr("X2")
                }

                TextField {
                    id: fieldX2
                    text: qsTr("0")

                }
            }




        }

        GroupBox {
            id: results
            width: 200
            height: 59
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            title: qsTr("Results")

            RowLayout {
                id: resultsLayout
                anchors.rightMargin: 80
                anchors.leftMargin: 80
                anchors.fill: parent
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                TextField {
                    id: resultField
                    text: qsTr("0")
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }
            }
        }

        GroupBox {
            id: operations
            width: 200
            height: 181
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            title: qsTr("Operations")

            GridLayout {
                id: operationsLayout
                anchors.left: parent.left
                anchors.leftMargin: 60
                anchors.rightMargin: 60
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                rows: 2
                columns: 2

                Button {
                    id: addButtom
                    text: qsTr("+")
                }

                Button {
                    id: multiplyButton
                    text: qsTr("*")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                }

                Button {
                    id: resetButton
                    text: qsTr("Reset")
                }

                Button {
                    id: exitButton
                    text: qsTr("Exit")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                }
            }
        }

    }

}

















































/*##^## Designer {
    D{i:9;anchors_height:100;anchors_width:100;anchors_x:"-12";anchors_y:"-37"}D{i:12;anchors_height:100;anchors_width:100;anchors_x:"-12";anchors_y:18}
}
 ##^##*/
